// #define VARIABLE_EXPAND(name, func) name,

// enum class ENUM_NAME
// {
// #include VAR_FILE
// };

// #undef VARIABLE_EXPAND
// #define VARIABLE_EXPAND(enum_name, func) \
//     {std::Parser::normalize(#enum_name, str::Parser::Type::LOWER), func},

// static inline auto
// getVariableHandlerRouter(void)
// {
//     return core::VariableInfoArray{
// #include VAR_FILE
//     };
// }

// #undef ENUM_NAME
// #undef VAR_FILE
// #undef VARIABLE_EXPAND
