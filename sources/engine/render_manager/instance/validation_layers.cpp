#include "validation_layers.hpp"

namespace kusengine
{
namespace render{
void
ValidationLayers::create()
{
    m_layers.push_back("VK_LAYER_KHRONOS_validation");
}

uint32_t
ValidationLayers::count()
{
    return m_layers.size();
}

const char**
ValidationLayers::data()
{
    return m_layers.data();
}

const char*
ValidationLayers::getSupportObjectNameImpl(
    const vk::ExtensionProperties& extension_prop)
{
    return extension_prop.extensionName;
}

const char*
ValidationLayers::getSupportObjectNameImpl(
    const vk::LayerProperties& layer_prop)
{
    return layer_prop.layerName;
}

bool
ValidationLayers::supported(std::vector<const char*> extensions)
{
    return checkSupport<vk::ExtensionProperties>(
               extensions, vk::enumerateInstanceExtensionProperties()) &&
           checkSupport<vk::LayerProperties>(
               m_layers, vk::enumerateInstanceLayerProperties());
}
}; // namespace render
}; // namespace kusengine
