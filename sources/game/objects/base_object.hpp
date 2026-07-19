#pragma once

#include "object_type.hpp"

namespace game::obj
{

class Coordinatable;
class Drawable;
class Hitable;
class Textable;

class BaseObject
{
public:
    BaseObject(const int a_type, const int a_level);
    virtual ~BaseObject() = default;

    Coordinatable& asCoordinatable();
    Drawable& asDrawable();
    Hitable& asHitable();
    Textable& asTextable();

    bool is(const int a_type) const;
    bool is(const Type a_type) const;

    bool isCoordinatable() const;
    bool isDrawable() const;
    bool isHitable() const;
    bool isTextable() const;

    int getLevel() const;

private:
    const int m_type;
    int m_level;
};

} // namespace game::obj
