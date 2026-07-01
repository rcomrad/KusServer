#pragma once

#include "gpu/command/base_command.hpp"
#include "gpu/pipeline/graphic_pipeline.hpp"

#include "sprite.hpp"
#include "sprite_push_data.hpp"

namespace gpu::sprite
{

class SpriteView
{
public:
    SpriteView(Sprite& a_texture, float a_offset_x, float a_offset_y);

    void draw(vk::PipelineLayout a_pipeline_layout,
              command::BaseCommand& a_cmd);

private:
    float m_offset_x;
    float m_offset_y;

    sprite::Sprite& m_sprite;
};

using SpriteViewArray = std::vector<sprite::SpriteView>;

} // namespace gpu::sprite
