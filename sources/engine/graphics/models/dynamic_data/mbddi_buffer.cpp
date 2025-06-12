#include "mbddi_buffer.hpp"

#include <algorithm>
namespace kusengine
{

MBDD::MBDD() : color(1.f, 1.f, 1.f, 1.f), model(1.f)
{
}

MBDDIBuffer::MBDDIBuffer() : is_link(false)
{
    m_data = new MBDD();
}

MBDDIBuffer::~MBDDIBuffer()
{
    if (is_link == false) delete m_data;
}

MBDDIBuffer::MBDDIBuffer(const MBDDIBuffer& other)
{
    *this = other;
}

MBDDIBuffer::MBDDIBuffer(MBDDIBuffer&& other) noexcept
{
    *this = std::move(other);
}

MBDDIBuffer&
MBDDIBuffer::operator=(const MBDDIBuffer& other)
{
    MBDD* temp = new MBDD();
    *temp      = *other.m_data;

    // -- Kolb line -- //
    if (is_link == false) delete m_data;
    std::swap(temp, m_data);
    is_link = false;

    return *this;
}

MBDDIBuffer&
MBDDIBuffer::operator=(MBDDIBuffer&& other) noexcept
{
    if (is_link == false) delete m_data;
    m_data       = other.m_data;
    other.m_data = nullptr;
    is_link      = other.is_link;

    return *this;
}

void
MBDDIBuffer::linkData(MBDD* data)
{
    if (data != m_data)
    {
        MBDD temp = *m_data;

        // -- Kolb line -- //

        if (is_link == false) delete m_data;
        std::swap(*data, temp);

        m_data  = data;
        is_link = true;
    }
}
}; // namespace kusengine
