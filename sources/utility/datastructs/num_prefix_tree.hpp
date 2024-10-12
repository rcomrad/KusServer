#pragma once

//------------------------------------------------------------------------------

#include <boost/optional.hpp>

#include <algorithm>
#include <string_view>
#include <vector>

#include "utility/common/transform.hpp"

#include "pt_key_storage.hpp"

//------------------------------------------------------------------------------

namespace util
{

template <typename StoredType, int MinNum, int MaxNum>
class NumPrefixTree
{
public:
    NumPrefixTree() noexcept : m_key_structure(MaxNum - MinNum)
    {
    }

    template <typename KeyContainer>
    void set(const KeyContainer& a_keys, const StoredType& a_value) noexcept
    {
        // TODO: add key range check: a_keys[i] in [MinNum, MaxNum]
        m_data_storage.emplace_back(a_value);
        m_key_structure.set(Transform::toNumVector(a_keys, MinNum),
                            m_data_storage.size() - 1);
    }

    template <typename KeyContainer>
    boost::optional<StoredType&> get(const KeyContainer& a_keys) noexcept
    {
        boost::optional<StoredType&> result;
        auto indx = m_key_structure.get(Transform::toNumVector(a_keys, MinNum));
        if (indx) result = m_data_storage[indx.value()];
        return result;
    }

    template <typename CellType>
    void set(std::initializer_list<CellType>&& a_keys,
             const StoredType& a_value) noexcept
    {
        set(a_keys, a_value);
    }

    template <typename CellType>
    void get(std::initializer_list<CellType>&& a_keys) noexcept
    {
        return get(a_keys);
    }

    // TODO: make char arrays better?
    // the problem is calling the end function for the array of characters below
    // https://stackoverflow.com/questions/18732352/stdend-with-raw-arrays-of-char
    void set(const char* a_keys, const StoredType& a_value) noexcept
    {
        set(std::string_view(a_keys), a_value);
    }

    void get(const char* a_keys) noexcept
    {
        return get(std::string_view(a_keys));
    }

private:
    PTKeyStorage m_key_structure;
    std::vector<StoredType> m_data_storage;
};

} // namespace util

//------------------------------------------------------------------------------
