#include "base_object.hpp"

#include "coordinatable.hpp"
#include "drawable.hpp"
#include "hitable.hpp"
#include "textable.hpp"

game::obj::Object::BaseObject(const int a_type, const int a_level)
    : m_type(a_type), m_level(a_level)
{
}

game::obj::Coordinatable&
game::obj::Object::asCoordinatable()
{
    return dynamic_cast<Coordinatable&>(*this);
}

game::obj::Drawable&
game::obj::Object::asDrawable()
{
    return dynamic_cast<Drawable&>(*this);
}

game::obj::Hitable&
game::obj::Object::asHitable()
{
    return dynamic_cast<Hitable&>(*this);
}

game::obj::Textable&
game::obj::Object::asTextable()
{
    return dynamic_cast<Textable&>(*this);
}

bool
game::obj::Object::is(const int a_type) const
{
    return m_type | a_type == a_type;
}

bool
game::obj::Object::is(const Type a_type) const
{
    return m_type | static_cast<int>(a_type);
}

bool
game::obj::Object::isCoordinatable() const
{
    return m_type | static_cast<int>(Type::COORDINATABLE);
}

bool
game::obj::Object::isDrawable() const
{
    return m_type | static_cast<int>(Type::DRAWABLE);
}

bool
game::obj::Object::isHitable() const
{
    return m_type | static_cast<int>(Type::HITABLE);
}

bool
game::obj::Object::isTextable() const
{
    return m_type | static_cast<int>(Type::TEXTABLE);
}

int
game::obj::Object::getLevel() const
{
    return m_level;
}
