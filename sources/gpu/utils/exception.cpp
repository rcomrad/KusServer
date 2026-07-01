#include "exception.hpp"

gpu::utils::ResizeException::ResizeException()
    : std::runtime_error("Window has been resized!")
{
}
