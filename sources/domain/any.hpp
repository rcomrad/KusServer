#ifndef ANY_HPP
#define ANY_HPP

//--------------------------------------------------------------------------------

#include <functional>

#include "metaprogramming.hpp"

//--------------------------------------------------------------------------------

namespace dom
{
class Any
{
public:
    enum class Type
    {
        NUN,
        INT,
        BOOL,
        STRING
    };

    Any() noexcept = default;
    ~Any();

    Any(const Any& other)            = delete;
    Any& operator=(const Any& other) = delete;

    Any(Any&& other) noexcept            = default;
    Any& operator=(Any&& other) noexcept = default;

    void fromInt(const int& val) noexcept;
    void fromBool(const bool& val) noexcept;

    template <typename S, typename = dom::enableIf<dom::isString<S>>>
    void fromString(S&& val) noexcept
    {
        release();
        value   = new std::string(std::forward<S>(val));
        deleter = [&](void*) { delete (std::string*)value; };
        mType   = Type::STRING;
    }

    int& getInt() noexcept;
    bool& getBool() noexcept;
    std::string& getString() noexcept;

    void release() noexcept;

    Type getType() const noexcept;

private:
    void* value;
    std::function<void(void*)> deleter;
    Type mType;
};
} // namespace dom

//--------------------------------------------------------------------------------

#endif // !ANY_HPP
