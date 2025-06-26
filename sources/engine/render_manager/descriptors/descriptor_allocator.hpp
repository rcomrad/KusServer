#ifndef DESCRIPTOR_ALLOCATOR_HPP
#define DESCRIPTOR_ALLOCATOR_HPP

#include "descriptor_pool.hpp"
#include "descriptor_set_layout.hpp"

namespace kusengine::render
{
class DescriptorAllocator
{
public:
    void init(const std::vector<DescriptorBindingData>& bindings);

    const vk::DescriptorSetLayout& layout() const& noexcept;

    void allocate(vk::UniqueDescriptorSet& set) const;

    void allocate(vk::DescriptorSet& set) const;

private:
    DescriptorSetLayout m_layout;
    DescriptorPool m_pool;
};
} // namespace kusengine::render

#endif // DESCRIPTOR_ALLOCATOR_HPP
