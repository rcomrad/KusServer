#include "char_array.cpp"

kstd::CharVector::CharVectorRef::CharVectorRef(CharVector& a_this_ref) noexcept
    : m_this_ref(a_this_ref)
{
}

kstd::CharVector::CharVectorRef::~CharVectorRef()
{
    m_this_ref->m_array = const_cast<char*>(m_this_ref->m_str.cstr());
}

kstd::CharVector::CharVectorRef::CharVectorRef(CharVector& a_this_ref) noexcept
    :
m_this_ref(a_this_ref)
{
}

kstd::CharVector::CharVectorRef::operator std::string&() noexcept
{
    return m_this_ref.m_str;
}

kstd::CharVector::CharVectorRef::operator std::string&() noexcept
{
    return m_this_ref.m_str;
}

kstd::CharVector::CharVectorRef
kstd::CharVector::getString() noexcept
{
    return *this;
}
