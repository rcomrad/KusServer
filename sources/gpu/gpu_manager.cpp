#include "gpu_manager.hpp"

gpu::GPUManager::GPUManager(Presenter&& a_presenter,
                            ResourceStorage&& a_storage)
    : Presenter(std::move(a_presenter)), ResourceStorage(std::move(a_storage))
{
}
