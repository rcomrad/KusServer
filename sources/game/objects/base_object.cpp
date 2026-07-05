// #include "base_object.hpp"

// game::GameObject::GameObject(gpu::sprite::Sprite& a_sprite,
//                              int a_pos_x,
//                              int a_pos_y)
//     : m_sprite(a_sprite), m_pos_x(a_pos_x), m_pos_y(a_pos_y)
// {
// }

// #include <iostream>
// void
// game::GameObject::update(uint32_t a_win_height, uint32_t a_win_width)
// {

//     m_norm_pos_y = static_cast<float>(m_pos_x) / a_win_width;
//     m_norm_pos_x = static_cast<float>(m_pos_y) / a_win_height;

//     std::cout << "W: " << a_win_width << " " << m_pos_x << " " << m_norm_pos_x
//               << std::endl;
//     std::cout << "H: " << a_win_height << " " << m_pos_y << " " << m_norm_pos_y
//               << std::endl;
// }

// gpu::sprite::SpriteView
// game::GameObject::getPresentation() const
// {
//     return gpu::sprite::SpriteView(m_sprite, m_norm_pos_x, m_norm_pos_y);
// }
