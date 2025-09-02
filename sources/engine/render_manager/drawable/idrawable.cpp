#include "idrawable.hpp"

#include "drawable_system.hpp"
namespace kusengine::render
{

IDrawable::IDrawable(const std::unique_ptr<Model>& model)
{
    m_model = model->clone();
}

void
IDrawable::pushToDrawableSystem(DrawableSystem& drawable_system)
{
    drawable_system.addModel(m_model);
}

void
IDrawable::linkUpdModelData(const std::vector<size_t>& inds,
                            size_t cur_i,
                            std::vector<char>& link_data,
                            int data_size_byte)
{
    m_model->linkUpdData(inds, cur_i, link_data, data_size_byte);
}

}; // namespace kusengine::render
