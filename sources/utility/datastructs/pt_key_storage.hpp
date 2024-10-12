#pragma once

//------------------------------------------------------------------------------

#include <optional>
#include <vector>

//------------------------------------------------------------------------------

namespace util
{

class PTKeyStorage
{
public:
    PTKeyStorage(size_t a_block_size) noexcept;
    void set(const std::vector<int>& a_keys, int val) noexcept;
    std::optional<int> get(const std::vector<int>& a_keys) noexcept;

private:
    size_t m_block_size;
    std::vector<int> m_key_structure;

    int& search(const std::vector<int>& a_keys, bool a_is_builder) noexcept;
};

} // namespace util

//------------------------------------------------------------------------------
