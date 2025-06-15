#include "block.hpp"

#include <iostream>

#include "engine/graphics/drawable/rectangle_shape.hpp"
#include "templates/template_storage.hpp"

namespace kusengine
{

Block::Block(std::shared_ptr<const BlockTemplate> bl_temp,
             const BlockCreateArgs& args)
    : GameObject(RectangleShape()), m_block_template(bl_temp)
{
    m_current_hp = args.current_hp;

    setPosition(args.position);
    setSize(args.size);
    m_shape->loadTexture(args.texture_name);
}

void
Block::logic()
{
}

}; // namespace kusengine
