#include "material.hpp"

namespace kusengine::render
{

Material::Material(Type t) : m_type(t)
{
}

Material::Type
Material::getType() const noexcept
{
    return m_type;
}
} // namespace kusengine::render
