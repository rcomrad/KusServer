#pragma once

//--------------------------------------------------------------------------------

#include <string.h>
#include <string>
#include <string_view>

#include "core/holy_trinity.hpp"
#include "core/logging.hpp"

//--------------------------------------------------------------------------------

namespace kstd
{

struct CharArray
{
public:
    char* m_array;
    size_t m_size;

    HOLY_TRINITY_SINGLE(CharBuffer);
    CharBuffer() noexcept = default;
};

//--------------------------------------------------------------------------------

template <const char* Name, size_t Size>
struct CharBuffer : public CharArray
{
public:
    HOLY_TRINITY_SINGLE(CharBuffer);

    CharBuffer() noexcept
    {
        m_array = m_storage;
        m_size  = 0;
    }

    // TODO: only char* and string_view
    template <typename Str>
    std::string_view add(Str&& a_ptr) noexcept
    {
        // TODO: optimise?
        // TODO: wrong (string_view end without \0)
        int ret =
            sprintf_s(m_storage, Size - m_last_element_num, getArray(a_ptr));

        std::string_view result;
        if (ret < 0)
        {
            LOG_ERROR("Not enough space for", Name, "buffer");
        }
        else
        {
            result = std::string_view(m_storage + m_last_element_num, ret);
            m_last_element_num += ret;
        }
        return result;
    }

private:
    char m_storage[Size];

    char* getArray(char* str)
    {
        return str;
    }
    char* getArray(std::string_view& str)
    {
        return str.data();
    }
};

//--------------------------------------------------------------------------------

struct CharVector : public CharArray
{
private:
    class CharVectorRef
    {
    public:
        ~CharVectorRef();
        operator std::string&() noexcept;

    private:
        CharVectorRef(CharVector& a_this_ref) noexcept;
        CharVector& m_this_ref;
    };

public:
    HOLY_TRINITY_SINGLE(CharBuffer);
    CharVector() noexcept = default;

    CharVectorRef getString() noexcept;

private:
    std::string m_str;
};

} // namespace kstd

//--------------------------------------------------------------------------------
