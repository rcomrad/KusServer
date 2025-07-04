#pragma once

//--------------------------------------------------------------------------------

#include <unordered_set>
#include <vector>

#include "kernel/utility/type/concepts.hpp"

//--------------------------------------------------------------------------------

namespace util
{

class Unique
{
    // TODO: checks and edge cases
public:
    template <typename T, typename... Args>
    static auto combine(T&& a_first_arg, Args&&... args)
    {
        struct Res
        {
            operator std::vector<std::string>()
            {
                return std::vector<std::string>{a_data.begin(), a_data.end()};
            }

            operator std::unordered_set<std::string>()
            {
                return std::move(a_data);
            }

            // TODO: not only string
            std::unordered_set<std::string> a_data;
        };
        Res result;

        (add(result.a_data, args), ...);

        return result;
    }

private:
    template <typename Res, Container T>
    static auto add(Res& a_res, T&& a_container)
    {
        for (auto& i : a_container)
        {
            a_res.insert(i);
        }
    }
};

} // namespace util

//--------------------------------------------------------------------------------
