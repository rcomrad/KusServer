#ifndef TEXTURE_ZONE_HPP
#define TEXTURE_ZONE_HPP

#include "glm/vec2.hpp"

#include "texture.hpp"

namespace kusengine::render
{

struct TextureZone
{
    glm::vec2 m_offset;
    glm::vec2 m_scale;

    Texture* m_texture;
};

} // namespace kusengine::render

#endif // TEXTURE_ZONE_HPP
