#pragma once

// #include <string>
// #include <vector>
#include <map>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>

// #include "gpu/font/font.hpp"
// #include "gpu/sprite/draw_task.hpp"
// #include "gpu/sprite/sprite_view.hpp"
// #include "gpu/utils/typedef.hpp"

// #include "drawable.hpp"
// #include "textable.hpp"
#include "gpu/sprite/draw_task.hpp"

// #include "object .hpp"

namespace gpu
{
class GPUManager;
}

namespace gpu::font
{
class FontStorage; // TODO: make it like sprites - not getter? but array from
                   // gpumanager
};

namespace game::obj
{

class BaseObject;
struct ObjectInfo;

class ObjectManager
{
public:
    ObjectManager(gpu::GPUManager const& a_gpu_manager_ref);
    ~ObjectManager();

    uint64_t addObject(std::string const& a_name); // TODO: return handler
    void removeObject(uint64_t const a_id);

    std::vector<gpu::sprite::DrawTask> generateDrawTasks(
        const gpu::font::FontStorage& a_font_storage) const;

private:
    // we don't need to draw all objects (don't store not drawable)
    // TODO: separate based on Drawable/Textable/etc
    std::map<int, std::unordered_set<std::unique_ptr<BaseObject>>> m_obj;

    std::unordered_map<std::string, ObjectInfo> m_object_infos;
};

} // namespace game::obj
