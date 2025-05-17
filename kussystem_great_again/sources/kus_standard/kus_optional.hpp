#pragma once

#include <utility>

#include "core/holy_trinity.hpp"

namespace kstd
{
// TODO: check all
// TODO: std::forward
template <typename DataT>
class OptionalBase
{
public:
    HOLY_TRINITY_NO_RELEASE_COPY(OptionalBase);

    OptionalBase() noexcept : m_has_value(false)
    {
    }

    OptionalBase(DataT&& a_data) noexcept : m_has_value(true)
    {
        m_data = std::forward<DataT>(a_data);
    }

    operator bool() const noexcept
    {
        return m_has_value;
    }

    // void set(DataT&& a_data) noexcept
    // {
    //     m_data      = std::forward<DataT>(a_data);
    //     m_has_value = true;
    // }

    template <typename Arg>
    void set(Arg&& a_data) noexcept
    {
        // m_data      = std::forward<Arg>(a_data);
        m_data      = (DataT)(void*)a_data;
        m_has_value = true;
    }

protected:
    DataT get() noexcept
    {
        return m_data;
    }

private:
    DataT m_data;
    bool m_has_value;
};

template <typename DataT>
class OptionalValue : public OptionalBase<DataT>
{
public:
    HOLY_TRINITY_NO_RELEASE_COPY(OptionalValue);

    OptionalValue() noexcept = default;

    auto getValue() noexcept
    {
        return this->get();
    }
};

template <typename DataT>
class OptionalPtr : public OptionalBase<DataT*>
{
public:
    HOLY_TRINITY_NO_RELEASE_COPY(OptionalPtr);

    OptionalPtr() noexcept = default;

    auto getPtr() noexcept
    {
        return this->get();
    }
};

template <typename DataT>
class OptionalRValue : public OptionalBase<DataT&&>
{
public:
    HOLY_TRINITY_NO_RELEASE_COPY(OptionalRValue);

    OptionalRValue() noexcept = default;

    auto getRValue() noexcept
    {
        return this->get();
    }
};

} // namespace kstd
