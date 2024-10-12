#include "pt_key_storage.hpp"

util::PTKeyStorage::PTKeyStorage(size_t a_block_size) noexcept
    : m_block_size(a_block_size + 2), m_key_structure(m_block_size)
{
}

void
util::PTKeyStorage::set(const std::vector<int>& a_keys, int val) noexcept
{
    search(a_keys, true) = val + 1;
}

std::optional<int>
util::PTKeyStorage::get(const std::vector<int>& a_keys) noexcept
{
    int res_val = search(a_keys, false);
    std::optional<int> result;
    if (res_val) result = res_val - 1;
    return result;
}

int&
util::PTKeyStorage::search(const std::vector<int>& a_keys,
                           bool a_is_builder) noexcept
{
    int indx = 0;
    for (auto& num : a_keys)
    {
        indx += num + 1;
        if (m_key_structure[indx])
        {
            indx = m_key_structure[indx];
        }
        else
        {
            if (a_is_builder)
            {
                indx = m_key_structure[indx] = m_key_structure.size();
                m_key_structure.resize(m_key_structure.size() + m_block_size);
            }
            else
            {
                indx = 0;
                break;
            }
        }
    }
    return m_key_structure[indx];
}
