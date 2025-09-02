#include "camera_manager.hpp"

#include "camera_2d.hpp"
#include "camera_3d.hpp"

namespace kusengine::render
{

void
CameraManager::setup(uint32_t width, uint32_t height)
{
    addCamera("camera_2d", std::make_unique<Camera2D>(width, height));
    addCamera("camera_3d", std::make_unique<Camera3D>(width, height));

    m_current_camera_key = "camera_2d";
}

std::unique_ptr<BasicCamera>&
CameraManager::switchTo(const std::string& key)
{
    auto it = m_cameras.find(key);
    if (it == m_cameras.end())
    {
        throw std::exception(
            (key + " does not exist in camera_manager\n").data());
    }
    m_current_camera_key = it->first;
    return it->second;
}

void
CameraManager::addCamera(const std::string& name,
                         std::unique_ptr<BasicCamera>&& new_camera)
{
    new_camera->recalculate();
    if (m_cameras.find(name) != m_cameras.end())
    {
        throw std::exception(
            (name + " is already exist in camera_manager\n").data());
    }
    m_cameras[name] = std::move(new_camera);
}

std::unique_ptr<BasicCamera>&
CameraManager::getCurrentCamera() &
{
    return m_cameras.at(m_current_camera_key);
}

}; // namespace kusengine::render
