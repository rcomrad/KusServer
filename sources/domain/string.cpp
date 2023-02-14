#include "string.hpp"

//--------------------------------------------------------------------------------

#include <iostream>
#include <string.h>

//--------------------------------------------------------------------------------

std::string
toLowerCyrillic(const std::string& let)
{
    return std::string(toLowerCyrillic(let.c_str()), 2);
}

dom::CharArray::CharArray() noexcept
    : mSize(0), mCapacity(0), mData(std::make_unique<char[]>(1))
{
    mData[0] = '\0';
}

//--------------------------------------------------------------------------------

dom::CharArray::CharArray(const CharArrayTable& aStr, char aDelimiter) noexcept
    : mSize(0), mCapacity(0)
{
    size_t size = 0;
    if (aDelimiter != '\0') size += aStr.size() - 1;
    for (const auto& str : aStr)
        size += str.getSize();
    reserve(size);

    char del[] = {aDelimiter, 0};
    for (const auto& str : aStr)
    {
        add(str);
        if (aDelimiter != '\0') add(del);
    }
}

//--------------------------------------------------------------------------------

dom::CharArray::CharArray(const void* aStr) noexcept
    : CharArray(((char*)(aStr)))
{
}

//--------------------------------------------------------------------------------

dom::CharArray::CharArray(const unsigned char* aStr) noexcept
    : CharArray((char*)(aStr))
{
}

//--------------------------------------------------------------------------------

dom::CharArray&
dom::CharArray::operator=(const void* aStr) noexcept
{
    *this = CharArray(aStr);
    return *this;
}

//--------------------------------------------------------------------------------

dom::CharArray&
dom::CharArray::operator=(const unsigned char* aStr) noexcept
{
    *this = CharArray(aStr);
    return *this;
}

//--------------------------------------------------------------------------------

void
dom::CharArray::reserve(size_t aSize) noexcept
{
    if (++aSize < 16) aSize = 16;
    if (mCapacity == 0) mCapacity = 1;

    if (aSize > mCapacity)
    {
        while (aSize > mCapacity)
            mCapacity *= 2;
        auto temp = std::make_unique<char[]>(mCapacity);
        if (mData != nullptr) mSize = copyArray(temp, mData, 0);
        mData = std::move(temp);
    }
}

//--------------------------------------------------------------------------------

dom::CharArray::operator char*() noexcept
{
    return mData.get();
}

//--------------------------------------------------------------------------------

dom::CharArray::operator const char*() const noexcept
{
    return mData.get();
}

//--------------------------------------------------------------------------------

std::string
dom::CharArray::getString() const noexcept
{
    std::string result(mData.get());
    return result;
}

//--------------------------------------------------------------------------------

std::ostream&
dom::operator<<(std::ostream& os, const dom::CharArray& aStr) noexcept
{
    for (size_t i = 0; aStr.mData[i]; ++i)
        os << aStr.mData[i];
    return os;
}

//--------------------------------------------------------------------------------

bool
dom::CharArray::isEmpty() const noexcept
{
    return mSize == 0;
}

//--------------------------------------------------------------------------------

size_t
dom::CharArray::getSize() const noexcept
{
    return mSize;
}

//--------------------------------------------------------------------------------

std::optional<std::string>
dom::CharArray::backSubStr(char aDelimiter) const noexcept
{
    std::optional<std::string> result;

    size_t pos = mSize - 1;
    while (pos > 0 && mData[pos--] != aDelimiter)
        ;

    if (pos > 0)
    {
        std::string temp;
        temp.reserve(mSize - pos - 2);
        for (size_t i = pos + 2; i < mSize; ++i)
            temp.push_back(mData[i]);
        result = temp;
    }

    return result;
}

//--------------------------------------------------------------------------------

dom::CharArray
dom::CharArray::getCopy() const noexcept
{
    dom::CharArray result;
    result.add(mData.get());
    return result;
}

//--------------------------------------------------------------------------------

char&
dom::CharArray::operator[](size_t aNum) noexcept
{
    return mData[aNum];
}

//--------------------------------------------------------------------------------

size_t
dom::CharArray::getSize(const char* str) const noexcept
{
    return strlen(str);
}

//--------------------------------------------------------------------------------

size_t
dom::CharArray::getSize(const std::string& str) const noexcept
{
    return str.size();
}

//--------------------------------------------------------------------------------

size_t
dom::CharArray::getSize(const dom::CharArray& str) const noexcept
{
    return str.mSize;
}

//--------------------------------------------------------------------------------
