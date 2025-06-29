#include "slicer.hpp"

#include "kernel/utility/datastructs/ascii_box.hpp"

namespace
{

template <typename Res>
Res
util::Slicer::copyImpl(std::string_view a_str, const char* a_delimiters)
{
    Res result;
    ASCIIBox delimiters(a_delimiters);
    delimiters.set(static_cast<int8_t>(0));

    int indx = 0;
    int last = 0;
    while (true)
    {
        char cur = a_str[indx++];
        if (delimiters.get(cur))
        {
            if (last != indx)
            {
                result.emplace_back(last, indx);
                ++indx;
                last = indx;
            }
        }

        if (!cur)
        {
            break;
        }
    }

    return result;
}

}; // namespace

std::vector<std::string>
util::Slicer::copy(std::string_view a_str, const char* a_delimiters)
{
    return copyImpl<std::vector<std::string>>(a_str, a_delimiters);
}

std::vector<std::string_view>
util::Slicer::copy(std::string_view a_str,
                   const char* a_delimiters,
                   const char* a_erase)
{
    std::vector<std::string_view> result;
    ASCIIBox delimiters(a_delimiters);
    delimiters.set(static_cast<int8_t>(0));
    ASCIIBox erasors(a_erase);

    int indx = 0;
    while (true)
    {
        char cur = a_str[indx++];
        if (!erasors.get(cur))
        {
            if (delimiters.get(cur))
            {
                if (indx + 1 != a_str.size())
                {
                    result.emplace_back();
                }
            }
            else
            {
                result.back().push_back(cur);
            }
        }

        if (!cur)
        {
            break;
        }
    }

    return result;
}

std::vector<std::string_view>
util::Slicer::change(std::string_view a_str, const char* a_delimiters)
{
    return copyImpl<std::vector<std::string_view>>(a_str, a_delimiters);
}

std::vector<std::string_view>
util::Slicer::change(std::string_view a_str,
                     const char* a_delimiters,
                     const char* a_erase)
{
    std::vector<std::string_view> result;
    ASCIIBox delimiters(a_delimiters);
    delimiters.set(static_cast<int8_t>(0));
    ASCIIBox erasors(a_erase);

    int indx = 0;
    int to   = 0;
    int last = 0;
    while (true)
    {
        char cur = a_str[indx++];
        if (!erasors.get(cur))
        {
            if (delimiters.get(cur))
            {
                if (last != to)
                {
                    result.emplace_back(last, to);
                    ++to;
                    last = to;
                }
            }
            else
            {
                a_str[to++] = cur;
            }
        }

        if (!cur)
        {
            break;
        }
    }

    return result;
}
