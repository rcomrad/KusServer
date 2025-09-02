#include "instance_data.hpp"

namespace kusengine::render
{
template <>
InstanceDataType
getInstanceDataType<InstanceDataMatrix>()
{
    return InstanceDataType::MATRIX4;
};
}