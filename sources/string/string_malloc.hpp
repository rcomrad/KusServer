#pragma once

// TODO: make_unique()
#define MALLOC_STR(name, size)                             \
    std::unique_ptr<char[]> uptr_##name(new char[(size)]); \
    auto name = uptr_##name.get();                         \
    name[0]   = 0;

// TODO: sprintf_s (safe)
#define SPRINTF(name, ...) name += sprintf(name, __VA_ARGS__);
