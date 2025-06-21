#ifndef MBDDII_BUFFER_HPP
#define MBDDII_BUFFER_HPP

#include <algorithm>

namespace kusengine
{
namespace render
{
template <typename MBDDType>
class MBDDIBuffer
{
public:
    virtual ~MBDDIBuffer();

    MBDDIBuffer();

    MBDDIBuffer(const MBDDIBuffer& other);
    MBDDIBuffer(MBDDIBuffer&& other) noexcept;

    MBDDIBuffer& operator=(const MBDDIBuffer& other);
    MBDDIBuffer& operator=(MBDDIBuffer&& other) noexcept;

    void linkData(MBDDType* data);

protected:
    bool is_link;

    MBDDType* m_data;
};

template <typename MBDDType>
MBDDIBuffer<MBDDType>::MBDDIBuffer() : is_link(false)
{
    m_data = new MBDDType();
}

template <typename MBDDType>
MBDDIBuffer<MBDDType>::~MBDDIBuffer()
{
    if (is_link == false) delete m_data;
}

template <typename MBDDType>
MBDDIBuffer<MBDDType>::MBDDIBuffer(const MBDDIBuffer& other)
{
    *this = other;
}

template <typename MBDDType>
MBDDIBuffer<MBDDType>::MBDDIBuffer(MBDDIBuffer&& other) noexcept
{
    *this = std::move(other);
}

template <typename MBDDType>
MBDDIBuffer<MBDDType>&
MBDDIBuffer<MBDDType>::operator=(const MBDDIBuffer& other)
{
    MBDDType* temp = new MBDDType();
    *temp          = *other.m_data;

    // -- Kolb line -- //
    if (is_link == false) delete m_data;
    std::swap(temp, m_data);
    is_link = false;

    return *this;
}

template <typename MBDDType>
MBDDIBuffer<MBDDType>&
MBDDIBuffer<MBDDType>::operator=(MBDDIBuffer&& other) noexcept
{
    if (is_link == false) delete m_data;
    m_data       = other.m_data;
    other.m_data = nullptr;
    is_link      = other.is_link;

    return *this;
}

template <typename MBDDType>
void
MBDDIBuffer<MBDDType>::linkData(MBDDType* data)
{
    if (data != m_data)
    {
        MBDDType temp = *m_data;

        // -- Kolb line -- //

        if (is_link == false) delete m_data;
        std::swap(*data, temp);

        m_data  = data;
        is_link = true;
    }
}
}; // namespace render
}; // namespace kusengine

#endif // MBDDII_BUFFER_HPP
