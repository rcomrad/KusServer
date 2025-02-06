#pragma once

#include <thread>

#include "kernel/framework/module/kernel.hpp"
#include "kernel/utility/synchronization/yield.hpp"

#include "definitions.hpp"
#include "tester_sync.hpp"

namespace kustest
{

//------------------------------------------------------------------------------

class BaseModuleClass : public core::Module
{
public:
    using core::Module::Module;

    bool isActive()
    {
        return getState() >= MState::ALIVE;
    }
};

//------------------------------------------------------------------------------

template <template <typename> typename TestType>
class SyncModuleTester : public SyncTester<TestType<BaseModuleClass>>
{
};

template <template <typename> typename TestType>
class SyncExternalKillTester
    : public ExternalKill<SyncTester, TestType<BaseModuleClass>>
{
};

} // namespace kustest
