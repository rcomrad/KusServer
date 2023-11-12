#include "variable_storage.hpp"

#include "file_data/parser.hpp"
#include "file_data/path.hpp"

//--------------------------------------------------------------------------------

core::VariableStorage::VariableStorage() noexcept : mMutexFlag(false)
{
    reloadSettings();
}

core::VariableStorage&
core::VariableStorage::getInstance() noexcept
{
    static VariableStorage instance;
    return instance;
}

void
core::VariableStorage::reloadSettings() noexcept
{
    auto settings =
        file::Parser::getVariablesFromFile("config", "main_settings.conf");
    for (auto& var : settings)
    {
        switch (var.value.getType())
        {
            case file::Value::Type::Int:
                mInts[var.name] = var.value;
                break;
            case file::Value::Type::Bool:
                mFlags[var.name] = var.value;
                break;
            case file::Value::Type::String:
                mWords[var.name] = std::string(var.value);
                break;
        }
    }
}

//--------------------------------------------------------------------------------

bool
core::VariableStorage::isLocked() noexcept
{
    static VariableStorage& instance = getInstance();
    return instance.mMutexFlag;
}

void
core::VariableStorage::beginLock(std::chrono::milliseconds aSleepValue) noexcept
{
    static VariableStorage& instance = getInstance();
    while (instance.mMutexFlag) continue;
    instance.mMutexFlag = true;
    std::this_thread::sleep_for(aSleepValue);
}

void
core::VariableStorage::endLock() noexcept
{
    static VariableStorage& instance = getInstance();
    instance.mMutexFlag              = false;
}

//--------------------------------------------------------------------------------

const bool&
core::VariableStorage::touchFlag(const std::string& aName,
                                 bool aDefaultValue) noexcept
{
    static VariableStorage& instance = getInstance();
    return instance.touch(aName, instance.mFlags,
                          std::forward<bool>(aDefaultValue));
}

const int&
core::VariableStorage::touchInt(const std::string& aName,
                                int aDefaultValue) noexcept
{
    static VariableStorage& instance = getInstance();
    return instance.touch(aName, instance.mInts,
                          std::forward<int>(aDefaultValue));
}

//--------------------------------------------------------------------------------

void
core::VariableStorage::setVariable(
    const std::string& aName,
    bool aValue,
    std::chrono::milliseconds aSleepValue) noexcept
{
    static VariableStorage& instance = getInstance();
    instance.set(aName, instance.mFlags, std::forward<bool>(aValue),
                 aSleepValue);
}

void
core::VariableStorage::setVariable(
    const std::string& aName,
    int aValue,
    std::chrono::milliseconds aSleepValue) noexcept
{
    static VariableStorage& instance = getInstance();
    instance.set(aName, instance.mInts, std::forward<int>(aValue), aSleepValue);
}

//--------------------------------------------------------------------------------
