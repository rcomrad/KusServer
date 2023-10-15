#ifndef MODULE_BASE_HPP
#define MODULE_BASE_HPP

//--------------------------------------------------------------------------------

#include <string>
#include <vector>

#include "file_data/value.hpp"

//--------------------------------------------------------------------------------

namespace core
{
class ModuleBase
{
public:
    ModuleBase(const std::string& aName, file::Value::Type aType) noexcept;
    static void process() noexcept;

protected:
    virtual std::string doAction() noexcept = 0;

private:
    struct Module
    {
        ModuleBase* ptr;
        std::string name;
        file::Value::Type type;
    };

    static std::vector<Module> mModules;

    static bool hasValue(const Module& aModule) noexcept;
    static void removeValue(const Module& aModule) noexcept;
};
} // namespace core

//--------------------------------------------------------------------------------

#endif // !MODULE_BASE_HPP
