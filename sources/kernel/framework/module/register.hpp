#pragma once

//--------------------------------------------------------------------------------

#include <memory>
#include <vector>

#include "kernel/utility/defines/holy_trinity.hpp"

#include "module.hpp"

//--------------------------------------------------------------------------------

extern std::vector<std::unique_ptr<core::Module>> global_modules;

//--------------------------------------------------------------------------------

namespace core
{
template <typename T>
class ModuleRegister
{
public:
    HOLY_TRINITY_NOCOPY(ModuleRegister);

    template <typename... Args>
    ModuleRegister(Args&&... args)
    {
        global_modules.emplace_back(
            std::make_unique<T>(std::forward<Args>(args)...));
    }
};
} // namespace core

//--------------------------------------------------------------------------------
