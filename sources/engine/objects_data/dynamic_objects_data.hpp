#ifndef DYNAMIC_OBJECTS_DATA_HPP
#define DYNAMIC_OBJECTS_DATA_HPP

#include <glm/glm.hpp>

namespace kusengine
{

struct DynamicObjectData
{
    glm::vec3 color;
    float padding1;
    glm::vec2 position;
    float padding2[2];
};

struct DynamicObjectsData
{
    std::vector<DynamicObjectData> m_dynamic_objects_data;
};
}; // namespace kusengine

#endif // DYNAMIC_OBJECTS_DATA_HPP
