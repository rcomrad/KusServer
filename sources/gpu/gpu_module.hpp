#pragma once

#include "kernel/utility/type/declaration/lifecycle_manager.hpp"

#include "gpu_manager.hpp"

namespace gpu
{

class GPUModule : public core::ThreadModule
{
public:
    GPUModule();

    GPUManager& getGPUManager();

protected:
    void threadInitialize() override;
    bool threadLoopBody() override;
    void threadTerminate() override;

private:
    utils::LifecycleManager<GPUManager> m_manager;
};

} // namespace gpu
