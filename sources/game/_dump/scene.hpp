#pragma once

#include "objects/drawable.hpp"
#include "objects/textable.hpp"

namespace game
{

class Scene
{
public:
    Scene();

    void update(gpu::type::Coordinates a_coord);
    void resize(const gpu::type::CoordinateSize& a_win_size);

    void pushPresentation(gpu::sprite::DrawTaskArray& a_draw_tasks) const;

private:
    std::vector<Drawable> m_drawabels;
    std::vector<Textable> m_textabels;
    std::vector<Textable> m_textabels;
};

} // namespace game
