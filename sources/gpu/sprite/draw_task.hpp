#pragma once

#include <vulkan/vulkan.hpp>

#include <vector>

#include "gpu/utils/typedef.hpp"

#include "sprite_view.hpp"

namespace gpu
{

namespace command
{
class BaseCommand;
}

namespace sprite
{

class SpriteStorage;

class DrawTask
{
public:
    DrawTask(int a_sprite_id,
             const type::Coordinates& a_position,
             int a_animation_id = 0);

    void execute(const SpriteStorage& a_storage,
                 vk::PipelineLayout a_pipeline_layout,
                 command::BaseCommand& a_cmd,
                 type::CoordinateSize a_windows_size);

private:
    int m_sprite_id;
    int m_animation_id;
    type::Coordinates m_position;
};

using DrawTaskArray = std::vector<sprite::DrawTask>;

} // namespace sprite

} // namespace gpu
