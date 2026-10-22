
#pragma once

#include "kernel/framework/logger/basic/include_me.hpp"

#include <concepts>
#include <type_traits>
#include <utility>

#include "gpu/utils/vk_converter.hpp"

// DeleterT& const d,
namespace gpu
{

template <typename BaseClassT, typename DeleterT, typename Context>
concept VulkanMoveMonitorDeleter =
    std::is_empty_v<DeleterT> && std::default_initializable<DeleterT> &&
    requires(BaseClassT& h, Context& ctx) {
        { DeleterT::operator()(ctx, h) } noexcept -> std::same_as<void>;
    };

template <typename BaseClassT, typename DeleterT, typename ContextT>
    requires VulkanMoveMonitorDeleter<BaseClassT, DeleterT, ContextT>
class VulkanUniqueWrapper : public BaseClassT
{
    static_assert(sizeof(BaseClassT) <= 8);

public:
    VK_CONVERTER(BaseClassT);
    HOLY_TRINITY_NO_COPY(VulkanUniqueWrapper);

    VulkanUniqueWrapper(BaseClassT a_handle, ContextT a_context)
        : BaseClassT(a_handle), m_context(a_context)
    {
    }

    ~VulkanUniqueWrapper() noexcept
    {
        if (toBase())
        {
            DeleterT::operator()(m_context, toBase());
        }
    }

    VulkanUniqueWrapper(VulkanUniqueWrapper&& a_other) noexcept
        : VulkanUniqueWrapper(BaseClassT{}, a_other.m_context)
    {
        *this = std::move(a_other);
    }

    VulkanUniqueWrapper& operator=(VulkanUniqueWrapper&& a_other) noexcept
    {
        if (this == &a_other)
        {
            LOG_ERROR("Move itself");
            return *this;
        }

        toBase() = std::exchange(a_other.toBase(), BaseClassT());

        return *this;
    }

    inline ContextT& getContext()
    {
        return m_context;
    }

    inline ContextT const& getContext() const
    {
        return m_context;
    }

private:
    // using MemberT =
    //     std::conditional_t<!std::is_base_of_v<StoredContext, ContextT>,
    //                        ContextT&,
    //    ContextT>;
    // MemberT m_context;
    ContextT m_context;
};

// TODO: add define for shorter forwar declaration
// DECL(gpu::logic, Device)

namespace logic
{
class Device;
}

template <typename BaseClassT, typename DeleterT>
using UniqueWrapperWithDevice =
    VulkanUniqueWrapper<BaseClassT, DeleterT, logic::Device&>;

#define DECLARE_UNIQUE_WRAPPER_HELPERS(class_name)               \
    struct class_name##Deleter                                   \
    {                                                            \
        static void operator()(logic::Device& a_device,          \
                               vk::class_name& a_this) noexcept; \
    };                                                           \
                                                                 \
    using class_name##Base =                                     \
        UniqueWrapperWithDevice<vk::class_name, class_name##Deleter>;
} // namespace gpu
