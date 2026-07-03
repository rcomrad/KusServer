#pragma once

#define VK_CONVERTER(Type)                \
                                          \
    inline Type& operator*()              \
    {                                     \
        return *static_cast<Type*>(this); \
    }                                     \
                                          \
    inline Type& toBase()                 \
    {                                     \
        return *static_cast<Type*>(this); \
    }
