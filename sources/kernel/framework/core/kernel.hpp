#pragma once

//--------------------------------------------------------------------------------

#include "base.hpp"

//--------------------------------------------------------------------------------

namespace core
{

class Kernel : public Base
{
    Kernel() = default;

    friend union util::LifecycleManager<Kernel>;

public:
    Kernel(const Kernel&) noexcept             = delete;
    Kernel& operator=(const Kernel&) noexcept  = delete;
    Kernel(Kernel&& other) noexcept            = delete;
    Kernel& operator=(Kernel&& other) noexcept = delete;

    static void create();
    static void destroy() noexcept;

    static Kernel& getInstance() noexcept;

private:
    static util::LifecycleManager<Kernel> m_self_ptr;
};

} // namespace core

#define KERNEL core::Kernel::getInstance()

//--------------------------------------------------------------------------------
