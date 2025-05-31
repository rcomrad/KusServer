#ifndef VEC_HPP
#define VEC_HPP

namespace kusengine
{
struct MyVec2
{
    float x;
    float y;
};

struct MyVec3
{
    float x;
    float y;
    float z;
};
bool
operator==(const MyVec2& left, const MyVec2& right);

bool
operator==(const MyVec3& left, const MyVec3& right);
}; // namespace kusengine

#endif // VEC_HPP
