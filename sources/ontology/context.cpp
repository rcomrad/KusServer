#include "context.hpp"

onto::Context::Context() : Context(Type::NONE)
{
}

onto::Context::Context(char simbol)
{
    Type type;
    switch (simbol)
    {
        case '<':
        case '>':
            type = Type::ANGLE_BRA;
            break;
        case '(':
        case ')':
            type = Type::BRASE;
            break;
        case ',':
            type = Type::DEVIDE;
            break;
        case '.':
            type = Type::CALL;
            break;
        case '#':
            type = Type::PREPROCESSOR;
            break;
        case '+':
            type = Type::PLUS;
            break;
        case '-':
            type = Type::MINUS;
            break;
        case '=':
            type = Type::ASSIGN;
            break;
    }
    *this = Context(type);
    this->word.push_back(simbol); // for debug
}

onto::Context::Context(Type a_type) : type(a_type), ptr(nullptr)
{
}

onto::Context::Context(Node* a_ptr, const std::string& a_word)
    : ptr(a_ptr), word(a_word)
{
    if (ptr)
    {
        type = static_cast<Type>(a_ptr->getKind());
    }
    else
    {
        type = Type::WORD;
    }
}

onto::Context::operator int() const noexcept
{
    return static_cast<int>(type);
}

onto::Context::operator char() const noexcept
{
    char result;
    switch (type)
    {
        case Type::DELETED:
            result = 'd';
            break;
        case Type::EXPRESSION:
            result = 'e';
            break;
        case Type::FUNCTION:
            result = 'f';
            break;
        case Type::COMMUNICATION:
            result = 'c';
            break;
        case Type::OPERATOR:
            result = 'o';
            break;
        case Type::TYPE:
            result = 't';
            break;
        case Type::VARIABLE:
            result = 'v';
            break;
        case Type::WORD:
            result = 'w';
            break;
        case Type::NUMERICAL:
            result = 'n';
            break;
        case Type::PREPROCESSOR:
            result = 'p';
            break;
        case Type::PLUS:
        case Type::MINUS:
            result = 'm';
            break;
        case Type::BRASE:
        case Type::DEVIDE:
        case Type::CALL:
        case Type::ASSIGN:
        case Type::ANGLE_BRA:
            result = word.front();
            break;
    }
    return result;
}
