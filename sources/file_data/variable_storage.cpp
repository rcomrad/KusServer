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
    auto settings = file::Parser::getVariablesFromFile(
        file::Path::getPathUnsafe("config", "main_settings.conf"), true);
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
                mWords[var.name] = var.value;
                break;
        }
    }
}

//--------------------------------------------------------------------------------

std::optional<bool>
file::VariableStorage::getFlag(const std::string& aName) const noexcept
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
file::VariableStorage::getInt(const std::string& aName) const noexcept
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

boost::optional<const std::string&>
file::VariableStorage::getWord(const std::string& aName) const noexcept
{
    const std::lock_guard<std::mutex> lock(mWordMutex);

    boost::optional<const std::string&> result;
    auto it = mWords.find(aName);
    if (it != mWords.end())
    {
        result = it->second;
    }
    return result;
}

//--------------------------------------------------------------------------------

bool
file::VariableStorage::getFlagUnsafe(const std::string& aName,
                                     bool aDefault) const noexcept
{
    bool result = aDefault;
    auto temp   = getFlag(aName);
    if (temp.has_value()) result = temp.value();
    return result;
}

int
file::VariableStorage::getIntUnsafe(const std::string& aName,
                                    int aDefault) const noexcept
{
    int result = aDefault;
    auto temp  = getInt(aName);
    if (temp.has_value()) result = temp.value();
    return result;
}

const std::string&
file::VariableStorage::getWordUnsafe(const std::string& aName,
                                     const std::string& aDefault) const noexcept
{
    auto temp                 = getWord(aName);
    const std::string& result = temp.has_value() ? temp.value() : aDefault;
    return result;
}

//--------------------------------------------------------------------------------

void
file::VariableStorage::setVariable(const std::string& aName,
                                   bool aValue) noexcept
{
    const std::lock_guard<std::mutex> lock(mBoolMutex);
    mFlags[aName] = aValue;
}

void
file::VariableStorage::setVariable(const std::string& aName,
                                   int aValue) noexcept
{
    const std::lock_guard<std::mutex> lock(mIntMutex);
    mInts[aName] = aValue;
}

void
file::VariableStorage::setVariable(const std::string& aName,
                                   const std::string& aValue) noexcept
{
    const std::lock_guard<std::mutex> lock(mWordMutex);
    mWords[aName] = aValue;
}

//--------------------------------------------------------------------------------
