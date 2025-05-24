#pragma once

#include <thread>

#include "kernel/framework/core/kernel.hpp"
#include "kernel/utility/synchronization/sleep.hpp"

#include "definitions.hpp"
#include "tester_sync.hpp"

namespace kustest
{

//------------------------------------------------------------------------------

class BaseModuleClass : public core::Module
{
public:
    using core::Module::Module;
};

//------------------------------------------------------------------------------

template <template <typename> typename TestType>
class SyncModuleTester : public SyncTester<TestType<BaseModuleClass>>
{
private:
    using Base = SyncTester<TestType<BaseModuleClass>>;

public:
    using Base::Base;
};

template <template <typename> typename TestType>
class SyncExternalKillTester
    : public ExternalKill<SyncTester, TestType<BaseModuleClass>>
{
private:
    using Base = ExternalKill<SyncTester, TestType<BaseModuleClass>>;

public:
    using Base::Base;
};

} // namespace kustest
