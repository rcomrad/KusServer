#pragma once

#include <vulkan/vulkan.hpp>

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

// class Sprite;
class SpriteStorage;

class DrawTask
{
public:
    DrawTask(SpriteView a_sprite_view,
             type::NDC a_offset,
             int a_animation_id = 0);

    // void collapse(const SpriteStorage& a_storage);
    // void execute(vk::PipelineLayout a_pipeline_layout,
    //           command::BaseCommand& a_cmd);
    // void selectAnimation(int a_anim_num);

    void execute(const SpriteStorage& a_storage,
                 vk::PipelineLayout a_pipeline_layout,
                 command::BaseCommand& a_cmd);

private:
    int m_sprite_id;
    // sprite::Sprite* m_sprite;

    type::NDC m_offset;

    int m_animation_id;
    // type::AnimationFrame m_animation_frame;
};

using DrawTaskArray = std::vector<sprite::DrawTask>;

} // namespace sprite

} // namespace gpu
