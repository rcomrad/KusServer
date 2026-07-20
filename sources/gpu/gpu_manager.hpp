#pragma once

#include "presenter.hpp"
#include "resource_storage.hpp"

namespace gpu
{

class GPUManager : public Presenter, public ResourceStorage
{
public:
    GPUManager(Presenter&& a_presenter, ResourceStorage&& a_storage);
};

} // namespace gpu
