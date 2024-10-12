#include "slicer.hpp"

#include "utility/datastructs/ascii_box.hpp"

std::vector<std::string_view>
util::Slicer::process(StringCaster a_str,
                      const char* a_delimiters,
                      const char* a_erase) noexcept
{
    return baseProcess(a_str, a_str, a_delimiters, a_erase);
}

std::vector<std::string_view>
util::Slicer::safeProcess(StringCaster a_from_str,
                          StringCaster a_to_str,
                          const char* a_delimiters,
                          const char* a_erase) noexcept
{
    return baseProcess(a_from_str, a_to_str, a_delimiters, a_erase);
}

std::vector<std::string_view>
util::Slicer::baseProcess(StringCaster a_from_str,
                          StringCaster a_to_str,
                          const char* a_delimiters,
                          const char* a_erase) noexcept
{
    auto* from_str = a_from_str.obtain();
    auto* to_str   = a_to_str.obtain(a_from_str);

    std::vector<std::string_view> result;
    ASCIIBox delimiters(a_delimiters);
    delimiters.set(static_cast<int8_t>(0));
    ASCIIBox erasors(a_erase);

    char* left = to_str;
    while (true)
    {
        auto from_cur = *from_str;
        auto& to_cur  = *to_str;

        if (!erasors.get(from_cur))
        {
            if (delimiters.get(from_cur))
            {
                to_cur = 0;
                if (left != to_str)
                {
                    result.emplace_back(left, to_str);
                    ++to_str;
                    left = to_str;
                }
            }
            else
            {
                to_cur = from_cur;
                ++to_str;
            }
        }

        if (from_cur)
        {
            ++from_str;
        }
        else
        {
            break;
        }
    }

    return result;
}
