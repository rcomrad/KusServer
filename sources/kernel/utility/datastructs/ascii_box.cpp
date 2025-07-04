#include "ascii_box.hpp"

#include "kernel/framework/logger/include_me.hpp"

util::ASCIIBox::ASCIIBox()
{
    data[0] = data[1] = 0;
}

util::ASCIIBox::ASCIIBox(const char* str) : ASCIIBox()
{
    set(str);
}
util::ASCIIBox::ASCIIBox(std::string_view str) : ASCIIBox()
{
    set(str.data());
}

util::ASCIIBox::ASCIIBox(const std::string& str) : ASCIIBox()
{
    set(str.c_str());
}

void
util::ASCIIBox::set(const char* str)
{
    while (*str)
    {
        set(static_cast<int8_t>(*str));
        ++str;
    }
}

void
util::ASCIIBox::set(int8_t num)
{
    if (num >= 0 && num < 64)
    {
        data[0] |= 1ULL << num;
    }
    else if (num >= 64 && num < 128)
    {
        data[1] |= 1ULL << (num - 64);
    }
    else
    {
        LOG_ERROR("ASCIIBox: num is out of range");
    }
}

bool
util::ASCIIBox::get(int8_t num)
{
    if (num >= 0 && num < 64)
    {
        return data[0] & (1ULL << num);
    }
    else if (num >= 64 && num < 128)
    {
        return data[1] & (1ULL << (num - 64));
    }
    LOG_ERROR("ASCIIBox: num is out of range");
    return false;
}
