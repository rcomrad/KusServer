#ifndef BASIC_SCENE_HPP
#define BASIC_SCENE_HPP
#include <memory>
#include <string>
#include <tuple>
#include <vector>

#include "engine/render_manager/drawable/drawable_system_usings.hpp"
#include "engine/render_manager/drawable/drawable_usings.hpp"
#include "engine/render_manager/renderer/renderer.hpp"

namespace kusengine
{
namespace render
{
template <typename DrawableT>
struct ScenePart
{
    RenderInfo<DrawableT> render_info;
    std::vector<std::unique_ptr<DrawableT>> drawables_p1_uv1;
};

template <typename DrawableT>
using ScenePartVector = std::vector<ScenePart<DrawableT>>;

class BasicScene
{
public:
    BasicScene();

    template <typename... DrawableSystemStorageT>
    void registerThis(DrawableSystemStorageT&... ds_storage);

    // const RenderInfo& getRenderInfo() const noexcept;

    void setSceneName(std::string_view new_scene_name);

private:
    std::string m_scene_name;

    std::tuple<ScenePartVector<Drawable_P1UV1_TRS>> m_scenes;
};

template <typename... DrawableSystemStorageT>
void
BasicScene::registerThis(DrawableSystemStorageT&... ds_storage)
{
    auto register_lambda =
        [&scenes = m_scenes, &scene_name = m_scene_name](auto& storage)
    {
        using SystemType =
            typename std::decay_t<decltype(storage)>::DrawableSystemType;
        using DrawableType = typename SystemType::DrawableType;

        auto& s_p_v = std::get<ScenePartVector<DrawableType>>(scenes);

        for (int i = 0; i < s_p_v.size(); i++)
        {
            auto& s_p = s_p_v[i];

            s_p.render_info.setName(scene_name + "_" + std::to_string(i));

            storage.add(s_p.render_info.getName().data(),
                        s_p.drawables_p1_uv1.begin(),
                        s_p.drawables_p1_uv1.end());
        }
    };

    (register_lambda(ds_storage), ...);
}

}; // namespace render
}; // namespace kusengine

#endif // BASIC_SCENE_HPP
