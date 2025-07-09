#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include <string>

namespace kusengine::render
{
class Material
{
public:
    Material(Type t);

    enum class Type
    {
        DEFAULT
    };

private:
    Type m_type;

    std::string pipeline_name;
};
} // namespace kusengine::render

#endif // MATERIAL_HPP
