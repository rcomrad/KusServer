#ifndef MODEL_DYNAMICS_DATA_HPP
#define MODEL_DYNAMICS_DATA_HPP

#include <vector>

#include "engine/vec.hpp"

namespace kusengine
{

struct ObjectDynamicsData
{
    ObjectDynamicsData() = default;
    ObjectDynamicsData(const MyVec3& col, const MyVec2& pos);
    MyVec3 color;
    float padding1;
    MyVec2 position;
    float padding2[2];
};

}; // namespace kusengine

#endif // MODEL_DYNAMICS_DATA_HPP
