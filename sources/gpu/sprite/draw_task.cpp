#include "draw_task.hpp"

#include "gpu/command/base_command.hpp"

#include "sprite.hpp"
#include "sprite_push_data.hpp"
#include "sprite_storage.hpp"

gpu::sprite::DrawTask::DrawTask(int a_sprite_id,
                                const type::Coordinates& a_position,
                                int a_animation_id)
    : m_sprite_id(a_sprite_id),
      m_animation_id(a_animation_id),

      m_position(a_position)
{
}

void
gpu::sprite::DrawTask::execute(const SpriteStorage& a_storage,
                               vk::PipelineLayout a_pipeline_layout,
                               command::BaseCommand& a_cmd,
                               type::CoordinateSize a_windows_size)
{
    const auto& sprite = a_storage.getSprite(m_sprite_id);

    SpritePushData push;
    sprite.draw(a_pipeline_layout, a_cmd, push, m_animation_id);

    auto ndc          = m_position / a_windows_size;
    push.coord_offset = {m_offset.x, m_offset.y};

    a_cmd.pushConstants(a_pipeline_layout,
                        vk::ShaderStageFlagBits::eVertex |
                            vk::ShaderStageFlagBits::eFragment,
                        0, sizeof(SpritePushData), &push);

    a_cmd.draw(6, 1, 0, 0);
}
