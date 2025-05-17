// #include "command_handler.hpp"

// namespace kustest
// {

// class CommandVariable : public CommandHandler
// {
// public:
//     VarMap getDefaultVarsMap() const noexcept
//     {
//         return VarMap{
//             {"reader_buffer", 1},
//             {"reader_cin",    1},
//             {"reader_file",   0},
//             {"reader_speed",  0},
//             {"running_flag",  1},
//             {"token_status",  0},
//         };
//     }
// };

// TEST_F(CommandVariable, smoke)
// {
//     auto default_vars = getDefaultVarsMap();
//     auto vars         = getVariableMap();
//     EXPECT_EQ(default_vars, vars);
// }

// } // namespace kustest
