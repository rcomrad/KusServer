#include "module_base.hpp"

#include "variable_storage.hpp"

std::vector<core::ModuleBase::Module> core::ModuleBase::mModules;

core::ModuleBase::ModuleBase(const std::string& aName,
                             file::Value::Type aType) noexcept
{
    mModules.emplace_back(this, aName, aType);
}

void
core::ModuleBase::process() noexcept
{
    for (auto& i : mModules)
    {
        if (hasValue(i) && VariableStorage::touchWord("command_result").empty())
        {
            VariableStorage::beginLock();
            VariableStorage::setVariable("command_result",
                                         std::move(i.ptr->doAction()));
            removeValue(i);
            VariableStorage::setVariable("executed_command", i.name);
            VariableStorage::endLock();
        }
    }
}

bool
core::ModuleBase::hasValue(const Module& aModule) noexcept
{
    bool result = false;
    switch (aModule.type)
    {
        case file::Value::Type::Int:
            result = VariableStorage::touchInt(aModule.name);
            break;
        case file::Value::Type::Bool:
            result = VariableStorage::touchFlag(aModule.name);
            break;
        case file::Value::Type::String:
            result = VariableStorage::touchWord(aModule.name).empty();
            break;
    }
    return result;
}

void
core::ModuleBase::removeValue(const Module& aModule) noexcept
{
    switch (aModule.type)
    {
        case file::Value::Type::Int:
            VariableStorage::setVariable(aModule.name, 0);
            break;
        case file::Value::Type::Bool:
            VariableStorage::setVariable(aModule.name, false);
            break;
        case file::Value::Type::String:
            VariableStorage::setVariable(aModule.name, "");
            break;
    }
}
