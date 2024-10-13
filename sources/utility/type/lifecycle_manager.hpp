#pragma once

#include <utility>

namespace util
{

// TODO: inline?

template <typename T>
union LifecycleManager
{
public:
    LifecycleManager() noexcept
    {
        is_freed.value = true;
    }

    ~LifecycleManager()
    {
        destroy();
    }

    template <typename... Args>
    void create(Args&&... args) noexcept
    {
        destroy();
        new (&data) T(std::forward<Args>(args)...);
        is_freed.value = false;
    }

    void destroy() noexcept
    {
        if (!is_freed.value)
        {
            obj.~T();
            is_freed.value = true;
        }
    }

    bool hasValue() const noexcept
    {
        return !is_freed.value;
    }

    T obj;
    char data[sizeof(T)];

private:
    struct
    {
        char filler[sizeof(T)];
        bool value;
    } is_freed;
};

} // namespace util