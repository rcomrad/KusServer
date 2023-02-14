#include "any.hpp"

dom::Any::~Any()
{
    release();
}

void
dom::Any::fromInt(const int& val) noexcept
{
    release();
    value   = new int(val);
    deleter = [&](void*) { delete (int*)value; };
    mType   = Type::INT;
}

void
dom::Any::fromBool(const bool& val) noexcept
{
    release();
    value   = new bool(val);
    deleter = [&](void*) { delete (bool*)value; };
    mType   = Type::BOOL;
}

int&
dom::Any::getInt() noexcept
{
    return *(int*)value;
}

bool&
dom::Any::getBool() noexcept
{
    return *(bool*)value;
}

std::string&
dom::Any::getString() noexcept
{
    return *(std::string*)value;
}

void
dom::Any::release() noexcept
{
    if (value != nullptr) deleter(value);
}

dom::Any::Type
dom::Any::getType() const noexcept
{
    return mType;
}
