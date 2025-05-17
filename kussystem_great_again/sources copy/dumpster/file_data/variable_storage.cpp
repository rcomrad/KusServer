#include "variable_storage.hpp"

#include <utility>

#include "file.hpp"
#include "parser.hpp"
#include "path.hpp"

//--------------------------------------------------------------------------------

file::VariableStorage::VariableStorage() noexcept
{
    reloadSettings();
}

file::VariableStorage&
file::VariableStorage::getInstance() noexcept
{
    static VariableStorage instance;
    return instance;
}

void
file::VariableStorage::reloadSettings() noexcept
{
    auto settings =
        file::Parser::getVariablesFromFile("config", "main_settings.conf");
    for (auto& var : settings)
    {
        if (var.name == "additional_path")
        {
            core::Path::addFoldersFrom(var.value);
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
                mWords[var.name] = str::String(var.value);
                break;
        }
    }
}

//--------------------------------------------------------------------------------

std::optional<bool>
file::VariableStorage::getFlag(const char* aName) const noexcept
{
    const std::lock_guard<std::mutex> lock(mBoolMutex);

    std::optional<bool> result;
    auto it = mFlags.find(aName);
    if (it != mFlags.end())
    {
        result = it->second;
    }
    return result;
}

std::optional<int>
file::VariableStorage::getInt(const char* aName) const noexcept
{
    const std::lock_guard<std::mutex> lock(mIntMutex);

    std::optional<int> result;
    auto it = mInts.find(aName);
    if (it != mInts.end())
    {
        result = it->second;
    }
    return result;
}

boost::optional<const char*>
file::VariableStorage::getWord(const char* aName) const noexcept
{
    const std::lock_guard<std::mutex> lock(mWordMutex);

    boost::optional<const char*> result;
    auto it = mWords.find(aName);
    if (it != mWords.end())
    {
        result = it->second;
    }
    return result;
}

//--------------------------------------------------------------------------------

bool
file::VariableStorage::getFlagUnsafe(const char* aName,
                                     bool aDefault) const noexcept
{
    bool result = aDefault;
    auto temp   = getFlag(aName);
    if (temp.has_value()) result = temp.value();
    return result;
}

int
file::VariableStorage::getIntUnsafe(const char* aName,
                                    int aDefault) const noexcept
{
    int result = aDefault;
    auto temp  = getInt(aName);
    if (temp.has_value()) result = temp.value();
    return result;
}

const char*
file::VariableStorage::getWordUnsafe(const char* aName,
                                     const char* aDefault) const noexcept
{
    auto temp          = getWord(aName);
    const char* result = temp.has_value() ? temp.value() : aDefault;
    return result;
}

//--------------------------------------------------------------------------------

void
file::VariableStorage::setVariable(const char* aName, bool aValue) noexcept
{
    const std::lock_guard<std::mutex> lock(mBoolMutex);
    mFlags[aName] = aValue;
}

void
file::VariableStorage::setVariable(const char* aName, int aValue) noexcept
{
    const std::lock_guard<std::mutex> lock(mIntMutex);
    mInts[aName] = aValue;
}

void
file::VariableStorage::setVariable(const char* aName,
                                   const char* aValue) noexcept
{
    const std::lock_guard<std::mutex> lock(mWordMutex);
    mWords[aName] = aValue;
}

//--------------------------------------------------------------------------------
