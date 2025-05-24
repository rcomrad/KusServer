#pragma once

//--------------------------------------------------------------------------------

#include <memory>
#include <string>
#include <unordered_map>

#include "kernel/framework/command/command_caller.hpp"
#include "kernel/framework/logger/table/include_me.hpp"

#include "module.hpp"

//--------------------------------------------------------------------------------

namespace core
{

class ModuleConstructor : public TablePrinter
{
public:
    using ModuleType            = std::unique_ptr<core::Module>;
    using ModuleConstructorFunc = ModuleType (*)();

    static ModuleConstructor& getInstance();

    void add(const std::string& a_name, ModuleConstructorFunc a_func) noexcept;
    ModuleType construct(const std::string& a_name);

    void print() const override;

private:
    std::unordered_map<std::string, ModuleConstructorFunc> m_functors;

    ModuleConstructor();
};

} // namespace core

//--------------------------------------------------------------------------------

#define REG_MODULE(module_name, class_name)                         \
    namespace                                                       \
    {                                                               \
    class __moduleConstructor                                       \
    {                                                               \
    public:                                                         \
        __moduleConstructor()                                       \
        {                                                           \
            core::ModuleConstructor::getInstance().add(module_name, \
                                                       construct);  \
        }                                                           \
                                                                    \
    private:                                                        \
        static core::ModuleConstructor::ModuleType construct()      \
        {                                                           \
            return std::make_unique<class_name>();                  \
        }                                                           \
    };                                                              \
                                                                    \
    __moduleConstructor __globalConstructor;                        \
    }

//--------------------------------------------------------------------------------
