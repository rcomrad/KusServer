#ifndef CAMERA_MANAGER_HPP
#define CAMERA_MANAGER_HPP

#include <memory>
#include <string>
#include <unordered_map>

#include "basic_camera.hpp"
#include "camera_2d.hpp"
#include "camera_3d.hpp"

namespace kusengine::render
{
class CameraManager
{
public:
    void setup(uint32_t width, uint32_t height);

    std::unique_ptr<BasicCamera>& switchTo(const std::string& key);

    void addCamera(const std::string& name,
                   std::unique_ptr<BasicCamera>&& new_camera);

    std::unique_ptr<BasicCamera>& getCurrentCamera() &;

private:
    std::string m_current_camera_key;

    std::unordered_map<std::string, std::unique_ptr<BasicCamera>> m_cameras;
};
}; // namespace kusengine::render

#endif // CAMERA_MANAGER_HPP
