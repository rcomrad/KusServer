#include "object_manager.hpp"

#include "gpu/font/font_storage.hpp"
#include "gpu/gpu_manager.hpp"

#include "base_object.hpp"
#include "drawable.hpp"
#include "object_builder.hpp"
#include "object_info.hpp"
#include "object_type.hpp"
#include "textable.hpp"

game::obj::ObjectManager::ObjectManager(
    gpu::GPUManager const& a_gpu_manager_ref)
{
    // #define OBJECT_DIR "objects"
    // KERNEL.addDataShortcut(OBJECT_DIR, OBJECT_DIR);

    auto map_path  = KERNEL.getShortcut(DATA_DIR, "objects.txt");
    m_object_infos = KERNEL.readStructMap<obj::ObjectInfo>(map_path);

    // std::vector<std::string> names;
    for (auto& [name, info] : m_object_infos)
    {
        if (info.texture.has_value())
        {
            info.sprite_view.emplace(
                a_gpu_manager_ref.generateSpriteView(info.texture.value()));
            // names.emplace_back(info.texture.value());
        }
    }

    // auto sprite_map = a_gpu_manager_ref.generateSpriteView(names);
    // for (auto& [name, obj_info] : m_object_infos)
    // {
    //     if (info.texture.has_value())
    //     {
    //         info.sprite_view = sprite_map[info.texture.value()];
    //     }
    // }
}

game::obj::ObjectManager::~ObjectManager() = default;

uint64_t
game::obj::ObjectManager::addObject(std::string const& a_name)
{
    auto const it = m_object_infos.find(a_name);
    if (m_object_infos.end() == it)
    {
        THROW("No such object info '%s'", a_name);
    }

    auto obj_ptr = createObject(it->second);
    auto id      = reinterpret_cast<uint64_t>(obj_ptr.get());
    m_obj[obj_ptr->getLevel()].emplace(std::move(obj_ptr));
    return id;
}

void
game::obj::ObjectManager::removeObject(uint64_t const a_id)
{
    // TODO: with using handler instead of uint46_t
    // auto const ptr   = reinterpret_cast<BaseObject const*>(a_id);
    // auto const level = ptr->getLevel();

    // const auto it_container = m_obj.find(level);
    // if (m_obj.end() == it_container)
    // {
    //     THROW("No such level %d('%ull')", level, a_id);
    // }

    // const auto it_obj = it_container->second.find(ptr);
    // if (m_objects.end() == it_obj)
    // {
    //     THROW("Can't remove non-existent object'%ull'", a_id);
    // }
    // it_container->second.erase(it_obj);
}

std::vector<gpu::sprite::DrawTask>
game::obj::ObjectManager::generateDrawTasks(
    const gpu::font::FontStorage& a_font_storage) const
{
    std::vector<gpu::sprite::DrawTask> result;
    // result.reserve(m_objects.size());

    for (auto const& [level, storage] : m_obj)
    {
        for (auto const& obj_ptr : storage)
        {
            if (obj_ptr->isDrawable())
            {
                // TODO: make template functions for const/noncost dcast for
                // ptr/ref/smartptr to ref
                auto const& drawable =
                    *dynamic_cast<Drawable const*>(obj_ptr.get());
                result.emplace_back(drawable.getObjectPresentation());
            }
        }
        for (auto const& obj_ptr : storage)
        {
            if (obj_ptr->isTextable())
            {
                auto const& textable =
                    *dynamic_cast<Textable const*>(obj_ptr.get());
                textable.addTextPresentation(a_font_storage, result);
            }
        }
    }

    return result;
}
