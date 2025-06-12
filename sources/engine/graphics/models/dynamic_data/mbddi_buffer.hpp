#ifndef MBDDII_BUFFER_HPP
#define MBDDII_BUFFER_HPP

#include "glm/mat3x3.hpp"
#include "glm/vec3.hpp"

namespace kusengine
{

struct MBDD // use 4, not 3, because shader alligning
{
    MBDD();
    glm::vec4 color;
    glm::mat4 model;
};

class MBDDIBuffer
{
public:
    virtual ~MBDDIBuffer();

    MBDDIBuffer();

    MBDDIBuffer(const MBDDIBuffer& other);
    MBDDIBuffer(MBDDIBuffer&& other) noexcept;

    MBDDIBuffer& operator=(const MBDDIBuffer& other);
    MBDDIBuffer& operator=(MBDDIBuffer&& other) noexcept;

    void linkData(MBDD* data);

protected:
    bool is_link;

    MBDD* m_data;
};
}; // namespace kusengine

#endif // MBDDII_BUFFER_HPP
