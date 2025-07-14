#include "slicer.hpp"

#include "kernel/utility/datastructs/ascii_box.hpp"

std::vector<std::string>
util::Slicer::copy(std::string_view a_str, std::string_view a_delimiters)
{
    // TODO: parametrize copy, not call with empty a_erase
    return copy(a_str, a_delimiters, "");
}

// TODO: substr faster?
std::vector<std::string>
util::Slicer::copy(std::string_view a_str,
                   std::string_view a_delimiters,
                   std::string_view a_erase)
{
    std::vector<std::string> result{""};
    ASCIIBox delimiters(a_delimiters);
    ASCIIBox erasors(a_erase);

    for (auto c : a_str)
    {
        if (erasors.get(c))
        {
            continue;
        }

        if (delimiters.get(c))
        {
            if (!result.back().empty())
            {
                result.emplace_back();
            }
            continue;
        }

        result.back().push_back(c);
    }

    if (result.back().empty())
    {
        result.pop_back();
    }

    return result;
}

std::vector<std::string_view>
util::Slicer::change(std::string_view a_str, std::string_view a_delimiters)
{
    // TODO: parametrize change, not call with empty a_erase
    return change(a_str, a_delimiters, "");
}

std::vector<std::string_view>
util::Slicer::change(std::string_view a_str,
                     std::string_view a_delimiters,
                     std::string_view a_erase)
{
    std::vector<std::string_view> result;
    ASCIIBox delimiters(a_delimiters);
    ASCIIBox erasors(a_erase);

    auto str_ptr = const_cast<char*>(a_str.data());

    int write = 0;
    int last  = 0;
    for (int i = 0; i < a_str.size(); ++i)
    {
        if (erasors.get(a_str[i]))
        {
            continue;
        }

        if (delimiters.get(a_str[i]))
        {
            if (write - last > 0)
            {
                result.emplace_back(
                    std::string_view(a_str).substr(last, write - last));
                last = write;
            }
            continue;
        }

        str_ptr[write++] = a_str[i];
    }

    if (write - last > 0)
    {
        result.emplace_back(std::string_view(a_str).substr(last, write - last));
    }

    return result;
}
