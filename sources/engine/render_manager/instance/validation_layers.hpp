#ifndef VALIDATION_LAYERS_HPP
#define VALIDATION_LAYERS_HPP

#include <vulkan/vulkan.hpp>

#include <vector>

namespace kusengine
{
namespace render{
class ValidationLayers
{
public:
    ValidationLayers() = default;

    void create();

    bool supported(std::vector<const char*> extensions);

    uint32_t count();

    const char** data();

private:
    template <typename T>
    bool checkSupport(const std::vector<const char*>& objects,
                      const std::vector<T>& supported_objects);

    template <typename T>
    const char* getSupportObjectName(const T& obj);

    const char* getSupportObjectNameImpl(
        const vk::ExtensionProperties& extension_prop);

    const char* getSupportObjectNameImpl(const vk::LayerProperties& layer_prop);

    std::vector<const char*> m_layers;
};

template <typename T>
const char*
ValidationLayers::getSupportObjectName(const T& obj)
{
    return getSupportObjectNameImpl(obj);
}

template <typename T>
bool
ValidationLayers::checkSupport(const std::vector<const char*>& objects,
                               const std::vector<T>& supported_objects)
{
    bool found;

    for (const char* object : objects)
    {
        found = false;
        for (const T& supported_object : supported_objects)
        {
            if (strcmp(object, getSupportObjectName(supported_object)) == 0)
            {
                found = true;
                break;
            }
        }
        if (!found)
        {
            return false;
        }
    }
    return true;
}
}; // namespace render
}; // namespace kusengine
#endif // VALIDATION_LAYERS_HPP
