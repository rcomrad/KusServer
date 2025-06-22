#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <string>
#include <string_view>

#include "engine/render_manager/renderer/render_way_type.hpp"

namespace kusengine
{
namespace render
{
class RenderInfo
{
public:
    RenderInfo() = default;

    void setRenderWayType(RenderWayType rwt);

    void setName(std::string_view name);

    std::string_view getName() const noexcept;

    RenderWayType getenderWayType() const noexcept;

private:
    std::string m_name;

    RenderWayType m_render_way_type;
};
}; // namespace render
}; // namespace kusengine

#endif // RENDERER_HPP
