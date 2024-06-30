#pragma once

#include "struct_storage.hpp"

namespace data
{

#define DATABASE_STRUCT_SUBDEF(Name, ...)   \
    struct Name                             \
    {                                       \
        int id;                             \
        __VA_ARGS__;                        \
        static const struct_id_t struct_id; \
    }; // namespace data

#ifndef DATABASE_STRUCTURE_CPP_FILE
#    define DATABASE_STRUCT(...) DATABASE_STRUCT_SUBDEF(__VA_ARGS__)
#else
#    define DATABASE_STRUCT(Name, ...)            \
        DATABASE_STRUCT_SUBDEF(Name, __VA_ARGS__) \
        const struct_id_t Name::struct_id =       \
            StructStorage::registrateStruct(#Name, "int id;" #__VA_ARGS__);
#endif

// clang-format off

DATABASE_STRUCT
(
    AnswerBase,
    int         userID;
    int     questionID;
    char     time[100];
    char  verdict[100];
    float       weight;
    char    value[100];
)

// clang-format on
}; // namespace data
