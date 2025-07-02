#include "uniform_buffer_object.hpp"

namespace kusengine
{
namespace render
{
bool
operator==(const UBO& left, const UBO& right)
{
    return left.camera_matrix == right.camera_matrix;
}
}; // namespace render
}; // namespace kusengine
