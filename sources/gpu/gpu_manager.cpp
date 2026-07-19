#include "gpu_manager.hpp"

gpu::GPUManager::GPUManager(Presenter&& a_presenter, Storage&& a_storage)
    : Presenter(std::move(a_presenter)), Storage(std::move(a_storage))
{
}
