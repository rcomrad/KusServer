#ifndef INSTANCE_DATA_HPP
#define INSTANCE_DATA_HPP

#include "glm/mat4x4.hpp"

namespace kusengine::render
{

enum class InstanceDataType
{
    MATRIX4
};

template <typename InstanceData_t>
InstanceDataType
getInstanceDataType();

struct InstanceDataMatrix
{
    glm::mat4 model_matrix;
};

extern template InstanceDataType
getInstanceDataType<InstanceDataMatrix>();

} // namespace kusengine::render

#endif // INSTANCE_DATA_HPP
