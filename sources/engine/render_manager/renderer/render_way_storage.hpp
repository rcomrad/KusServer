#ifndef RENDER_WAY_STORAGE_HPP
#define RENDER_WAY_STORAGE_HPP

#include <string>
#include <unordered_map>

#include "render_way.hpp"
#include "render_way_types.hpp"

namespace kusengine
{
namespace render
{
class RenderWayStorage
{
public:

    RenderWayStorage() = default;

    void create(const vk::Extent2D& extent, vk::Format format);

    const RenderWay* const getRenderWay(RenderWayTypes type) const;

private:
    RenderWay getUniversalRenderWay(const vk::Extent2D& extent, vk::Format format);

    std::unordered_map<RenderWayTypes, RenderWay> m_pipelines;
};
}; // namespace render
}; // namespace kusengine

#endif // RENDER_WAY_STORAGE_HPP
