#pragma once

// #include <string>
// #include <vector>
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

namespace game::obj
{

class BaseObject;
class ObjectInfo;

class ObjectManager
{
public:
    void addObject(const std::string& a_name, const ObjectInfo& a_info);
    void removeObject(const std::string& a_name);

    std::vector<gpu::sprite::DrawTask> generateDrawTasks(
        const gpu::font::FontStorage& a_font_storage) const;

private:
    std::unordered_map<std::string, std::unique_ptr<BaseObject>> m_objects;
    std::unordered_map<int, std::unordered_set<Drawable*>> m_draw_obj;
    std::unordered_map<int, std::unordered_set<Textable*>> m_text_obj;
};

} // namespace game::obj
