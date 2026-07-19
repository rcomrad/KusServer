#include "presenter.hpp"
#include "storage.hpp"

namespace gpu
{

class GPUManager : public Presenter, public Storage
{
public:
    GPUManager(Presenter&& a_presenter, Storage&& a_storage);
};

} // namespace gpu
