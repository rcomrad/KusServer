#include "variable_storage.hpp"

#include <utility>

#include "file_data/file.hpp"
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
        if (var.name == "additional_path")
        {
            file::Path::addFoldersFrom(var.value);
            continue;
        }

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
    instance.mMutexFlag              = true;
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
                                 bool aDefaultValu) noexcept
{
    static VariableStorage& instance = getInstance();
    auto it                          = instance.mFlags.find(aName);
    if (it != instance.mFlags.end())
    {
        return it->second;
    }
    return instance.mFlags.insert({aName, aDefaultValu}).first->second;
}

const int&
core::VariableStorage::touchInt(const std::string& aName,
                                int aDefaultValue) noexcept
{
    static VariableStorage& instance = getInstance();
    auto it                          = instance.mInts.find(aName);
    if (it != instance.mInts.end())
    {
        return it->second;
    }
    return instance.mInts.insert({aName, aDefaultValue}).first->second;
}

const std::string&
core::VariableStorage::touchWord(const std::string& aName,
                                 const std::string& aDefaultValue) noexcept
{
    static VariableStorage& instance = getInstance();
    auto it                          = instance.mWords.find(aName);
    if (it != instance.mWords.end())
    {
        return it->second;
    }
    return instance.mWords.insert({aName, aDefaultValue}).first->second;
}

//--------------------------------------------------------------------------------

void
core::VariableStorage::setVariable(
    const std::string& aName,
    bool aValue,
    std::chrono::milliseconds aSleepValue) noexcept
{
    static VariableStorage& instance = getInstance();
    if (instance.mMutexFlag == false)
    {
        instance.beginLock(aSleepValue);
        instance.mFlags[aName] = aValue;
        instance.endLock();
    }
    else
    {
        instance.mFlags[aName] = aValue;
    }
}

void
core::VariableStorage::setVariable(
    const std::string& aName,
    int aValue,
    std::chrono::milliseconds aSleepValue) noexcept
{
    static VariableStorage& instance = getInstance();
    if (instance.mMutexFlag == false)
    {
        instance.beginLock(aSleepValue);
        instance.mInts[aName] = aValue;
        instance.endLock();
    }
    else
    {
        instance.mInts[aName] = aValue;
    }
}

// void
// core::VariableStorage::setVariable(
//     const std::string& aName,
//     const std::string& aValue,
//     std::chrono::milliseconds aSleepValue) noexcept
// {
//     static VariableStorage& instance = getInstance();
//     if (instance.mMutexFlag == false)
//     {
//         instance.beginLock(aSleepValue);
//         instance.mWords[aName] = aValue;
//         instance.endLock();
//     }
//     else
//     {
//         instance.mWords[aName] = aValue;
//     }
// }

//--------------------------------------------------------------------------------
