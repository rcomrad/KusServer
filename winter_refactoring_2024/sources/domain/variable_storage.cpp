#include "variable_storage.hpp"

#include <thread>

#include "text_data/parser.hpp"
#include "text_data/path.hpp"

//--------------------------------------------------------------------------------

dom::VariableStorage::VariableStorage() noexcept : mMutexFlag(false)
{
    reloadSettings();
}

dom::VariableStorage&
dom::VariableStorage::getInstance() noexcept
{
    static VariableStorage instance;
    return instance;
}

void
dom::VariableStorage::reloadSettings() noexcept
{
    auto settings =
        text::Parser::getVariablesFromFile("config", "main_settings.conf");
    for (auto& var : settings)
    {
        switch (var.value.getType())
        {
            case text::Value::Type::Int:
                mInts[var.name] = var.value;
                break;
            case text::Value::Type::Bool:
                mFlags[var.name] = var.value;
                break;
            case text::Value::Type::String:
                mWords[var.name] = std::string(var.value);
                break;
        }
    }
}

//--------------------------------------------------------------------------------

bool
dom::VariableStorage::isLocked() noexcept
{
    static VariableStorage& instance = getInstance();
    return instance.mMutexFlag;
}

void
dom::VariableStorage::beginLock(std::chrono::milliseconds aSleepValue) noexcept
{
    static VariableStorage& instance = getInstance();
    while (instance.mMutexFlag) continue;
    instance.mMutexFlag = true;
    std::this_thread::sleep_for(aSleepValue);
}

void
dom::VariableStorage::endLock() noexcept
{
    static VariableStorage& instance = getInstance();
    instance.mMutexFlag              = false;
}

//--------------------------------------------------------------------------------

const bool&
dom::VariableStorage::touchFlag(const std::string& aName,
                                bool aDefaultValue) noexcept
{
    static VariableStorage& instance = getInstance();
    return instance.touch(aName, instance.mFlags,
                          std::forward<bool>(aDefaultValue));
}

const int&
dom::VariableStorage::touchInt(const std::string& aName,
                               int aDefaultValue) noexcept
{
    static VariableStorage& instance = getInstance();
    return instance.touch(aName, instance.mInts,
                          std::forward<int>(aDefaultValue));
}

//--------------------------------------------------------------------------------

void
dom::VariableStorage::setVariable(
    const std::string& aName,
    bool aValue,
    std::chrono::milliseconds aSleepValue) noexcept
{
    static VariableStorage& instance = getInstance();
    instance.set(aName, instance.mFlags, std::forward<bool>(aValue),
                 aSleepValue);
}

void
dom::VariableStorage::setVariable(
    const std::string& aName,
    int aValue,
    std::chrono::milliseconds aSleepValue) noexcept
{
    static VariableStorage& instance = getInstance();
    instance.set(aName, instance.mInts, std::forward<int>(aValue), aSleepValue);
}

//--------------------------------------------------------------------------------
