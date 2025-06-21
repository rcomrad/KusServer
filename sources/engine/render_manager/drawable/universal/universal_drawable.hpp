#ifndef UNIVERSAL_DRAWABLE_HPP
#define UNIVERSAL_DRAWABLE_HPP

#include "engine/render_manager/drawable/basic_drawable.hpp"
#include "engine/render_manager/dynamics_data/universal/universal_mbddi.hpp"
#include "engine/render_manager/model/model_storage.hpp"

namespace kusengine
{
namespace render
{

class UniversalDrawable : public BasicDrawable<UniversalVertex, UniversalMBDDI>
{
public:
    virtual ~UniversalDrawable() = default;
    // namespace kusengine
    UniversalDrawable() = default;

protected:
};

}; // namespace render
}; // namespace kusengine

#endif // UNIVERSAL_DRAWABLE_HPP
