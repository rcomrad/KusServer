#pragma once

//--------------------------------------------------------------------------------

#include <set>
#include <vector>

#include "core/command/command_data.hpp"

#include "utility/common/holy_trinity.hpp"

//--------------------------------------------------------------------------------

namespace core
{

struct CommandSets
{
    HOLY_TRINITY_NO_OBJECT(CommandSets);

#define COMPARATOR(name)                                           \
    struct name                                                    \
    {                                                              \
        bool operator()(const CommandData& first,                  \
                        const CommandData& second) const noexcept; \
    };
    COMPARATOR(BaseComparator);
    COMPARATOR(ArgsComparator);
    COMPARATOR(VarsComparator);
#undef COMPARATOR

    static const std::string_view& getKey(
        const std::string_view& a_key) noexcept
    {
        return a_key;
    }

    static const std::string_view& getKey(
        const std::pair<const std::string_view, std::string_view>&
            a_key) noexcept
    {
        return a_key.first;
    }

    template <typename T1, typename T2>
    static bool commandCompare(const CommandData& first,
                               const CommandData& second,
                               const T1& first_storage,
                               const T2& second_storage) noexcept
    {
        bool result = false;
        if (first.value != second.value)
        {
            result = first.value < second.value;
        }
        else if (first_storage.size() != second_storage.size())
        {
            result = first_storage.size() < second_storage.size();
        }
        else
        {
            for (auto it1 = first_storage.begin(), it2 = second_storage.begin();
                 it1 != first_storage.end() && it2 != second_storage.end();
                 ++it1, ++it2)
            {
                if (getKey(*it1) != getKey(*it2))
                {
                    result = *it1 < *it2;
                }
            }
        }
        return result;
    }
};

using CommandBaseSet = std::set<CommandData, CommandSets::BaseComparator>;
using CommandArgSet  = std::set<CommandData, CommandSets::ArgsComparator>;
using CommandWarsSet = std::set<CommandData, CommandSets::VarsComparator>;
using CommandUniqSet = std::vector<CommandData>;

// enum class StateType
// {
//     COMMAND,
//     COMMAND_ARGS,
//     COMMAND_VARS,
//     UNIQUE
// };

} // namespace core

//--------------------------------------------------------------------------------
