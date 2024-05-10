#pragma once

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

// TODO: rename
#define HOLY_TRINITY_SINGLE(NAME)                    \
    NAME(const NAME&) noexcept             = delete; \
    NAME& operator=(const NAME&) noexcept  = delete; \
    NAME(NAME&& other) noexcept            = delete; \
    NAME& operator=(NAME&& other) noexcept = delete;

#define HOLY_TRINITY_NO_OBJECT(NAME)                  \
    NAME()                                 = delete;  \
    NAME(const NAME&) noexcept             = delete;  \
    NAME& operator=(const NAME&) noexcept  = delete;  \
    NAME(NAME&& other) noexcept            = delete;  \
    NAME& operator=(NAME&& other) noexcept = delete;
