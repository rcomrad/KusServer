#ifndef IDRAWABLE_HPP
#define IDRAWABLE_HPP
#include <vulkan/vulkan.hpp>

#include <memory>

#include "engine/render_manager/model/model.hpp"
#include "engine/render_manager/renderer/render_system.hpp"

namespace kusengine::render
{

class DrawableSystem;

class IDrawable
{
public:
    virtual ~IDrawable() = default;

    IDrawable() = default;

    IDrawable(const std::unique_ptr<Model>& model);

    void pushToDrawableSystem(DrawableSystem& drawable_system);

    void linkUpdModelData(const std::vector<size_t>& inds,
                          size_t cur_i,
                          std::vector<char>& link_data,
                          int data_size_byte);

private:
    std::unique_ptr<Model> m_model;
};

} // namespace kusengine::render

#endif // IDRAWABLE_HPP
