#ifndef MBDDII_BUFFER_HPP
#define MBDDII_BUFFER_HPP

#include <algorithm>

namespace kusengine
{
namespace render
{
template <typename MBDD_T>
class MBDDIBuffer
{
public:
    using MBDDtype = MBDD_T;

    virtual ~MBDDIBuffer();

    MBDDIBuffer();

    MBDDIBuffer(const MBDDIBuffer& other);
    MBDDIBuffer(MBDDIBuffer&& other) noexcept;

    MBDDIBuffer& operator=(const MBDDIBuffer& other);
    MBDDIBuffer& operator=(MBDDIBuffer&& other) noexcept;

protected:
    MBDD_T* m_data;

    bool is_link;
};

template <typename MBDD_T>
MBDDIBuffer<MBDD_T>::MBDDIBuffer() : is_link(false)
{
    m_data = new MBDD_T();
}

template <typename MBDD_T>
MBDDIBuffer<MBDD_T>::~MBDDIBuffer()
{
    if (is_link == false) delete m_data;
}

template <typename MBDD_T>
MBDDIBuffer<MBDD_T>::MBDDIBuffer(const MBDDIBuffer& other)
{
    *this = other;
}

template <typename MBDD_T>
MBDDIBuffer<MBDD_T>::MBDDIBuffer(MBDDIBuffer&& other) noexcept
{
    *this = std::move(other);
}

template <typename MBDD_T>
MBDDIBuffer<MBDD_T>&
MBDDIBuffer<MBDD_T>::operator=(const MBDDIBuffer& other)
{
    MBDD_T* temp = new MBDD_T();
    *temp        = *other.m_data;

    // -- Kolb line -- //
    if (is_link == false) delete m_data;
    std::swap(temp, m_data);
    is_link = false;

    return *this;
}

template <typename MBDD_T>
MBDDIBuffer<MBDD_T>&
MBDDIBuffer<MBDD_T>::operator=(MBDDIBuffer&& other) noexcept
{
    if (is_link == false) delete m_data;
    m_data       = other.m_data;
    other.m_data = nullptr;
    is_link      = other.is_link;

    return *this;
}
}; // namespace render
}; // namespace kusengine

#endif // MBDDII_BUFFER_HPP
