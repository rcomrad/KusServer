#pragma once

#include <utility>

#define HOLY_TRINITY_FULL(NAME)                       \
    NAME() noexcept                        = default; \
    ~NAME()                                = default; \
    NAME(const NAME&) noexcept             = default; \
    NAME& operator=(const NAME&) noexcept  = default; \
    NAME(NAME&& other) noexcept            = default; \
    NAME& operator=(NAME&& other) noexcept = default;

#define HOLY_TRINITY_DEFAULT(NAME)                    \
    NAME(const NAME&) noexcept             = default; \
    NAME& operator=(const NAME&) noexcept  = default; \
    NAME(NAME&& other) noexcept            = default; \
    NAME& operator=(NAME&& other) noexcept = default;

#define HOLY_TRINITY_NOCOPY(NAME)                     \
    NAME(const NAME&) noexcept             = delete;  \
    NAME& operator=(const NAME&) noexcept  = delete;  \
    NAME(NAME&& other) noexcept            = default; \
    NAME& operator=(NAME&& other) noexcept = default;

// TODO: remove redandant
// SINGLETON_INITIALIZER
#define SINGLETON_DEFINITOR(NameSpace, ClassName)          \
    namespace                                              \
    {                                                      \
    struct SingletonEntryPoint##NameSpace##ClassName       \
    {                                                      \
        SingletonEntryPoint##NameSpace##ClassName()        \
        {                                                  \
            NameSpace::ClassName::getInstance();           \
        }                                                  \
    };                                                     \
    SingletonEntryPoint##NameSpace##ClassName              \
        g_singleton_entry_point_for##NameSpace##ClassName; \
    }

// #define SINGLETON_DEFINITOR(NameSpace, ClassName)                      \
//     NameSpace::ClassName& NameSpace::ClassName::getInstance() noexcept \
//     {                                                                  \
//         static ClassName instance;                                     \
//         return instance;                                               \
//     }                                                                  \
//     namespace                                                          \
//     {                                                                  \
//     struct SingletonEntryPoint##NameSpace##ClassName                   \
//     {                                                                  \
//         SingletonEntryPoint##NameSpace##ClassName()                    \
//         {                                                              \
//             NameSpace::ClassName::getInstance();                       \
//         }                                                              \
//     };                                                                 \
//     SingletonEntryPoint##NameSpace##ClassName                          \
//         g_singleton_entry_point_for##NameSpace##ClassName;             \
//     }

#define HOLY_TRINITY_SINGLETON(NAME)                 \
    NAME(const NAME&) noexcept             = delete; \
    NAME& operator=(const NAME&) noexcept  = delete; \
    NAME(NAME&& other) noexcept            = delete; \
    NAME& operator=(NAME&& other) noexcept = delete; \
                                                     \
    static inline NAME& getInstance() noexcept       \
    {                                                \
        static NAME instance;                        \
        return instance;                             \
    }

#define HOLY_EMPTINESS

#define SINGL_METHOD(public_def, private_def, result, name, params, action) \
    template <typename... Args>                                             \
    static inline result name(Args&&... args) noexcept                      \
    {                                                                       \
        action getInstance().name##Nonstatic(std::forward<Args>(args)...);  \
    }                                                                       \
                                                                            \
    private_def result name##Nonstatic params noexcept;                     \
    public_def

#define SINGL_VOID_METHOD(name, params) \
    SINGL_METHOD(public:, private:, void, name, params, HOLY_EMPTINESS)

#define SINGL_RET_METHOD(result, name, params) \
    SINGL_METHOD(public:, private:, result, name, params, return)

#define SINGL_PRIV_VOID_METHOD(name, params) \
    SINGL_METHOD(;, ;, void, name, params, HOLY_EMPTINESS)

#define SINGL_PRIV_RET_METHOD(result, name, params) \
    SINGL_METHOD(;, ;, result, name, params, return)

#define HOLY_TRINITY_NO_OBJECT(NAME)                 \
    NAME()                                 = delete; \
    NAME(const NAME&) noexcept             = delete; \
    NAME& operator=(const NAME&) noexcept  = delete; \
    NAME(NAME&& other) noexcept            = delete; \
    NAME& operator=(NAME&& other) noexcept = delete;
