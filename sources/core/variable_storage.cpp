#include "variable_storage.hpp"

#include <thread>
#include <utility>

#include "file_system/file_read.hpp"
#include "string/file.hpp"
#include "string/parser.hpp"

#include "path.hpp"

//--------------------------------------------------------------------------------

core::VariableStorage::VariableStorage() noexcept : mMutexFlag(false)
{
}

core::VariableStorage&
core::VariableStorage::getInstance() noexcept
{
    static VariableStorage instance;
    return instance;
}

//--------------------------------------------------------------------------------

void
core::VariableStorage::set(int aNumber, int aValue) noexcept
{
    getInstance().setNonstatic(aNumber, aValue);
}

int
core::VariableStorage::get(int aNumber) noexcept
{
    return getInstance().getNonstatic(aNumber);
}

void
core::VariableStorage::setNonstatic(int aNumber, int aValue) noexcept
{
    mVariables[aNumber] = aValue;
}

int
core::VariableStorage::getNonstatic(int aNumber) noexcept
{
    return mVariables[aNumber];
}

//--------------------------------------------------------------------------------

void
core::VariableStorage::reloadSettings(int aNumber, int aValue) noexcept
{
    getInstance().reloadSettingsNonstatic();
}

void
core::VariableStorage::reloadSettingsNonstatic() noexcept
{
    // auto settings =
    //     file::Parser::getVariablesFromFile("config", "main_settings.conf");

    auto settings = fs::FileRead::getWordsMap(ReadFromFile());
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
                mWords[var.name] = str::string(var.value);
                break;
        }
    }
}

//--------------------------------------------------------------------------------
