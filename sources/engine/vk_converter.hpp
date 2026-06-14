#pragma once

#define VK_CONVERTER(Type)                \
                                          \
    Type& operator*()                     \
    {                                     \
        return *static_cast<Type*>(this); \
    }
