#pragma once

#include <utility>

namespace util
{

// TODO: inline?

// TODO: operator=
// convertion to T

template <typename T>
union LifecycleManager
{
public:
    LifecycleManager() noexcept
    {
        data.is_freed = true;
    }

    template <typename... Args>
    LifecycleManager(Args&&... args) noexcept
    {
        create(args...);
    }

    ~LifecycleManager()
    {
        destroy();
    }

    template <typename... Args>
    void create(Args&&... args)
    {
        destroy();
        new (&data.object) T(std::forward<Args>(args)...);
        data.is_freed = false;
    }

    void destroy() noexcept
    {
        if (!data.is_freed)
        {
            obj.~T();
            data.is_freed = true;
        }
    }

    bool hasValue() const noexcept
    {
        return !data.is_freed;
    }

    operator bool() const noexcept
    {
        return !data.is_freed;
    }

    // std::optional compatibility
    bool has_value() const noexcept
    {
        return !data.is_freed;
    }

    T obj;

private:
    struct
    {
        char object[sizeof(T)];
        bool is_freed;
    } data;
};

} // namespace util
