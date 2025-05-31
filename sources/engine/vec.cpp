#include "vec.hpp"

namespace kusengine
{
bool
operator==(const MyVec2& left, const MyVec2& right)
{
    return left.x == right.x && left.y == right.y;
}

bool
operator==(const MyVec3& left, const MyVec3& right)
{
    return left.x == right.x && left.y == right.y && left.z == right.z;
}

}; // namespace kusengine
