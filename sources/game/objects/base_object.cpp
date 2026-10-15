#include "base_object.hpp"

#include "coordinatable.hpp"
#include "drawable.hpp"
#include "hitable.hpp"
#include "textable.hpp"

game::obj::BaseObject::BaseObject(const int a_type,
                                  std::optional<int> const& a_level)
    : m_type(a_type), m_level(a_level.value_or(0))
{
}

game::obj::Coordinatable&
game::obj::BaseObject::asCoordinatable()
{
    return dynamic_cast<Coordinatable&>(*this);
}

game::obj::Drawable&
game::obj::BaseObject::asDrawable()
{
    return dynamic_cast<Drawable&>(*this);
}

game::obj::Hitable&
game::obj::BaseObject::asHitable()
{
    return dynamic_cast<Hitable&>(*this);
}

game::obj::Textable&
game::obj::BaseObject::asTextable()
{
    return dynamic_cast<Textable&>(*this);
}

bool
game::obj::BaseObject::is(const int a_type) const
{
    return m_type | a_type == a_type;
}

bool
game::obj::BaseObject::is(const Type a_type) const
{
    return m_type | static_cast<int>(a_type);
}

bool
game::obj::BaseObject::isCoordinatable() const
{
    return m_type | static_cast<int>(Type::COORDINATABLE);
}

bool
game::obj::BaseObject::isDrawable() const
{
    return m_type | static_cast<int>(Type::DRAWABLE);
}

bool
game::obj::BaseObject::isHitable() const
{
    return m_type | static_cast<int>(Type::HITABLE);
}

bool
game::obj::BaseObject::isTextable() const
{
    return m_type | static_cast<int>(Type::TEXTABLE);
}

int
game::obj::BaseObject::getLevel() const
{
    return m_level;
}
