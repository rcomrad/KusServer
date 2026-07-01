#include <stdexcept>

namespace gpu::utils
{

class ResizeException : public std::runtime_error
{
public:
    ResizeException();
};

} // namespace gpu::utils
