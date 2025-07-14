#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include <string>

namespace kusengine::render
{
class Material
{
public:
    enum class Type
    {
        TEXTURE
    };
    Material(Type t);

    Type getType() const noexcept;

private:
    Type m_type;

    std::string pipeline_name;
};
} // namespace kusengine::render

#endif // MATERIAL_HPP
