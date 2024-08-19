// #include <atomic>
// #include <stdlib.h>
// #include <string>
// #include <unordered_map>

// #include "core/command.hpp"
// #include "core/command_handler.hpp"
// #include "core/variable_storage.hpp"

// #include "fixture.hpp"

// namespace kustest
// {

// class UTestVariable : public Fixture
// {
// public:
//     static std::optional<int> testToString(core::Command& a_command,
//                                            const std::string& a_variable,
//                                            const std::string& a_value) noexcept
//     {
//         (void)a_variable;

//         a_command.setResultBufferSize(500);
//         COMMAND_RETURN_MSG(a_command);
//         return std::stoi(a_value);
//     }

//     static void addVariable(
//         const std::vector<const char*>& a_name,
//         std::unordered_map<std::string, int>& a_var_dict) noexcept
//     {
//         core::VariableInfoArray var;
//         for (auto& i : a_name)
//         {
//             var.emplace_back(i, testToString);
//         }

//         auto offset = core::VariableStorage::addVariableInfo(var);
//         for (auto& i : a_name)
//         {
//             a_var_dict[i] = offset++;
//         }
//     }

//     static void output(const char* ptr, void* cntx) noexcept
//     {
//         EXPECT_NE(ptr, nullptr);
//         std::atomic<int>& cnt = *static_cast<std::atomic<int>*>(cntx);
//         ++cnt;
//     }
// };

// TEST_F(UTestVariable, simpl_set_get)
// {
//     const char var_name[] = "test";
//     std::unordered_map<std::string, int> var_dict;
//     addVariable({var_name}, var_dict);

//     const int new_val = -10;
//     core::VariableStorage::set(var_dict[var_name], new_val);
//     auto received_val = core::VariableStorage::get(var_dict[var_name]);

//     EXPECT_EQ(received_val, new_val);
// }

// TEST_F(UTestVariable, use_set_command)
// {
//     std::unordered_map<std::string, int> var_dict;
//     addVariable({"1"}, var_dict);
//     addVariable({"2", "6"}, var_dict);
//     addVariable({"0", "4"}, var_dict);
//     addVariable({"5", "3"}, var_dict);
//     addVariable({"9", "7", "8"}, var_dict);

//     std::atomic<int> command_output_count = 0;
//     uint32_t seed                         = 712525234;
//     std::unordered_map<std::string, int> values;
//     for (auto& i : var_dict)
//     {
//         int num         = rand_r(&seed);
//         values[i.first] = num;
//         core::Command comm("var_set " + i.first + "=" + std::to_string(num),
//                            output, &command_output_count);
//         core::CommandHandler::pushCommand(std::move(comm));
//         core::CommandHandler::handlCommand();
//     }

//     for (auto& i : var_dict)
//     {
//         auto received_val = core::VariableStorage::get(i.second);
//         EXPECT_EQ(received_val, values[i.first])
//             << "Name: " << i.first << " Offset: " << i.second;
//     }
//     EXPECT_EQ(command_output_count, var_dict.size());
// }

// } // namespace kustest
