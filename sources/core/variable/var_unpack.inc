// clang-format off

// #define ENUM_STR_ARRAY_NAME Names##ENUM_NAME

// #define ENUM_STR_ARRAY_NAME(name) name##Names
// #define ENUM_STR_ARRAY_NAME _ENUM_STR_ARRAY_NAME(ENUM_NAME)
// #define _ENUM_STR_ARRAY_NAME(enumName) Names ## enumName

#define VARIABLE_EXPAND(enum_name) enum_name,
    enum class ENUM_NAME
    {
        NUN,
        #include VAR_FILE
        MAX
    };
#undef VARIABLE_EXPAND

// #define VARIABLE_EXPAND(enum_name) {#enum_name, ENUM_NAME::enum_name},
#define VARIABLE_EXPAND(enum_name) #enum_name,
    static inline const char* VariableStrValues [int(ENUM_NAME::MAX) - 1] = 
    { 
        #include VAR_FILE
    };
#undef VARIABLE_EXPAND

#undef ENUM_STR_ARRAY_NAME

#undef ENUM_NAME
#undef VAR_FILE

// clang-format on
