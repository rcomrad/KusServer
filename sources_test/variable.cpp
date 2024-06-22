#include <stdlib.h>
#include <string>
#include <unordered_map>

#include "core/command.hpp"
#include "core/command_handler.hpp"
#include "core/variable_storage.hpp"

#include "fixture.hpp"

namespace kustest
{

class UTestVariable : public Fixture
{
public:
    static int testToString(const std::string& a_str) noexcept
    {
        return std::stoi(a_str);
    }

    static void addVariable(
        const std::vector<std::string>& a_name,
        std::unordered_map<std::string, int>& a_var_dict) noexcept
    {
        core::VariableSettings var;
        for (auto& i : a_name)
        {
            var.emplace_back(i, testToString);
        }

        auto offset = core::VariableStorage::addSettings(var);
        for (auto& i : a_name)
        {
            a_var_dict[i] = offset++;
        }
    }
};

TEST_F(UTestVariable, simpl_set_get)
{
    const std::string var_name = "test";
    std::unordered_map<std::string, int> var_dict;
    addVariable({var_name}, var_dict);

    const int new_val = -10;
    core::VariableStorage::set(var_dict[var_name], new_val);
    auto received_val = core::VariableStorage::get(var_dict[var_name]);

    EXPECT_EQ(received_val, new_val);
}

TEST_F(UTestVariable, use_set_command)
{
    std::unordered_map<std::string, int> var_dict;
    addVariable({"1"}, var_dict);
    addVariable({"2", "6"}, var_dict);
    addVariable({"0", "4"}, var_dict);
    addVariable({"5", "3"}, var_dict);
    addVariable({"9", "7", "8"}, var_dict);

    uint32_t seed = 712525234;
    std::unordered_map<std::string, int> values;
    for (auto& i : var_dict)
    {
        int num         = rand_r(&seed);
        values[i.first] = num;
        core::Command comm("set " + i.first + "=" + std::to_string(num));
        core::CommandHandler::pushCommand(std::move(comm));
        core::CommandHandler::handlCommand();
    }

    for (auto& i : var_dict)
    {
        auto received_val = core::VariableStorage::get(i.second);
        EXPECT_EQ(received_val, values[i.first])
            << "Name: " << i.first << " Offset: " << i.second;
    }
}

} // namespace kustest
