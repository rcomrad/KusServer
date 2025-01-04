#pragma once

#include "nodes/node.hpp"

namespace onto
{
struct Context
{
#define NODE_MACROS(large, default, small) large,
    enum class Type
    {
        NONE,
#include "nodes/node.ini"
        NODE,
        WORD,
        NUMERICAL,
        BRASE,        // ( )
        DEVIDE,       // ,
        CALL,         // .
        ASSIGN,       // =
        PREPROCESSOR, // #
        PLUS,         // #
        MINUS,        // #
        ANGLE_BRA,    // < >
        MAX
    };

    Context();
    Context(char simbol);
    Context(Type a_type);
    Context(Node* a_ptr, const std::string& a_word);

    operator int() const noexcept;
    operator char() const noexcept;

    Type type;
    Node* ptr;
    std::string word;
};
} // namespace onto
