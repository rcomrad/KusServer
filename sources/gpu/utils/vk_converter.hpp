#pragma once

#define VK_CONVERTER(Type)                      \
                                                \
    inline Type& toBase()                       \
    {                                           \
        return *static_cast<Type*>(this);       \
    }                                           \
                                                \
    inline Type& operator*()                    \
    {                                           \
        return *static_cast<Type*>(this);       \
    }                                           \
                                                \
    inline const Type& operator*() const        \
    {                                           \
        return *static_cast<const Type*>(this); \
    }                                           \
    \
