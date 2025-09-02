#ifndef UBO_STORAGE_RESOURCE_STORAGE_HPP
#define UBO_STORAGE_RESOURCE_STORAGE_HPP

#include "resource_storage.hpp"

namespace kusengine::render
{
class UboStorageResorceStorage final : public ResourceStorage
{
public:
    UboStorageResorceStorage(
        const kusengine::render::DescriptorManager& desc_manager);

    void updateBuffers(const updBuffersDataArgs& m_data) override;

private:
    void writeDescriptorSet() const noexcept override;

    StorageBuffer m_storage_buffer;
    UniformBuffer m_uniform_buffer;
};
} // namespace kusengine::render

#endif // UBO_STORAGE_RESOURCE_STORAGE_HPP
