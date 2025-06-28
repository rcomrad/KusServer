#include "uniform_buffer_object.hpp"

namespace kusengine
{
namespace render
{
bool
operator==(const UBO& left, const UBO& right)
{
    return left.projection == right.projection;
}
}; // namespace render
}; // namespace kusengine
