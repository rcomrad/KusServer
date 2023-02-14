#ifndef DOM_STRINGS_HPP
#define DOM_STRINGS_HPP

//--------------------------------------------------------------------------------

#define _CRT_SECURE_NO_WARNINGS
#include <string>
#undef _CRT_SECURE_NO_WARNINGS

#include <memory>
#include <optional>
#include <vector>

#include "domain/metaprogramming.hpp"

//--------------------------------------------------------------------------------

using namespace std::literals;

//--------------------------------------------------------------------------------

namespace dom
{
class CharArray;
using CharArrayTable = std::vector<CharArray>;

class CharArray
{
    template <class T>
    using isBasicString = isOneOf<T, char*, const char[], std::string>;

    template <class T>
    using isString =
        isOneOf<T, char*, const char[], std::string, dom::CharArray>;

    //--------------------------------------------------------------------------------

public:
    CharArray() noexcept;
    ~CharArray() = default;

    CharArray(const CharArray& other)            = delete;
    CharArray& operator=(const CharArray& other) = delete;

    CharArray(CharArray&& other) noexcept            = default;
    CharArray& operator=(CharArray&& other) noexcept = default;

    //--------------------------------------------------------------------------------

    template <typename S, typename = enableIf<isBasicString<S>>>
    CharArray(S&& aStr) noexcept : mSize(0), mCapacity(0)
    {
        add(std::forward<S>(aStr));
    }
    CharArray(const CharArrayTable& aStr, char aDelimiter = '\0') noexcept;

    explicit CharArray(const void* aStr) noexcept;
    explicit CharArray(const unsigned char* aStr) noexcept;

    //--------------------------------------------------------------------------------

    template <typename S, typename = enableIf<isString<S>>>
    CharArray& operator=(S&& aStr) noexcept
    {
        *this = std::move(CharArray(std::forward<S>(aStr)));
        return *this;
    }
    CharArray& operator=(const void* aStr) noexcept;
    CharArray& operator=(const unsigned char* aStr) noexcept;

    //--------------------------------------------------------------------------------

    template <typename S, typename = enableIf<isString<S>>>
    void operator+=(S&& aStr) noexcept
    {
        add(std::forward<S>(aStr));
    }

    //--------------------------------------------------------------------------------

    template <typename S, typename = enableIf<isString<S>>>
    bool operator==(S&& aStr) noexcept
    {
        size_t i = 0, j = 0;
        while (mData[i] && aStr[j])
        {
            if (mData[i++] != aStr[j++]) return false;
        }
        return true;
    }

    //--------------------------------------------------------------------------------

    void reserve(size_t aSize) noexcept;

    operator char*() noexcept;
    operator const char*() const noexcept;
    std::string getString() const noexcept;

    friend std::ostream& operator<<(std::ostream& os,
                                    const dom::CharArray& aStr) noexcept;

    bool isEmpty() const noexcept;
    size_t getSize() const noexcept;

    template <typename S, typename = enableIf<isString<S>>>
    void pushFront(S&& aStr) noexcept
    {
        size_t combinedSize = getSize(aStr) + mSize;
        CharArray temp;
        temp.reserve(combinedSize);
        temp.add(aStr);
        temp.add(mData);
        mData = std::move(temp.mData);
    }

    std::optional<std::string> backSubStr(char aDelimiter) const noexcept;

    CharArray getCopy() const noexcept;

    char& operator[](size_t aNum) noexcept;

    //--------------------------------------------------------------------------------

private:
    std::unique_ptr<char[]> mData;
    size_t mCapacity;
    size_t mSize;

    //--------------------------------------------------------------------------------

    template <typename S> void add(S&& aStr) noexcept
    {
        reserve(mSize + getSize(aStr));
        mSize += copyArray(mData, aStr, mSize);
    }

    template <typename S1, typename S2>
    size_t copyArray(S1&& aTo, S2&& aFrom, size_t aStartInd = 0) noexcept
    {
        size_t j = 0;
        while (aFrom[j])
        {
            aTo[aStartInd++] = aFrom[j++];
        }
        aTo[aStartInd] = '\0';
        return j;
    }

    //--------------------------------------------------------------------------------

    size_t getSize(const char* str) const noexcept;
    size_t getSize(const std::string& str) const noexcept;
    size_t getSize(const dom::CharArray& str) const noexcept;
};
} // namespace dom

//--------------------------------------------------------------------------------

#endif // !DOM_STRINGS_HPP
