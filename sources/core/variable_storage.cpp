#include "variable_storage.hpp"

#include "core/logging.hpp"

#include "file_system/file_read.hpp"
#include "file_system/path.hpp"

#include "string/parser.hpp"
#include "string/separators.hpp"

//--------------------------------------------------------------------------------

core::VariableStorage::VariableStorage() noexcept
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
    mVariables[aNumber].mValue = aValue;
}

int
core::VariableStorage::getNonstatic(int aNumber) noexcept
{
    return mVariables[aNumber].mValue;
}

//--------------------------------------------------------------------------------

void
core::VariableStorage::reloadSettings() noexcept
{
    getInstance().reloadSettingsNonstatic();
}

void
core::VariableStorage::reloadSettingsNonstatic() noexcept
{
    auto settings = fs::FileRead::getWordsMap(
        fs::ReadFromStoredFile("main_settings.cfg"), str::Separator::variable);
    for (auto& var : settings)
    {
        auto it = mVariableNames.find(var.first);
        if (it != mVariableNames.end())
        {
            int num                = it->second;
            mVariables[num].mValue = mVariables[num].mParser(var.second);
            LOG_INFO("Variable", var.first, "set with value", var.second);
        }
        else
        {
            LOG_ERROR("No variable with that name have been registered (",
                      var.first, ")");
        }
    }
}

//--------------------------------------------------------------------------------

int
core::VariableStorage::addSettings(
    const VariableSettings& aVarSettings) noexcept
{
    return getInstance().addSettingsNonstatic(aVarSettings);
}

int
core::VariableStorage::addSettingsNonstatic(
    const VariableSettings& aVarSettings) noexcept
{
    int start_num = mVariables.size();
    mVariables.resize(start_num + aVarSettings.size());

    int num = start_num;
    for (auto& i : aVarSettings)
    {
        mVariables[num].mParser = i.second;
        mVariableNames[i.first] = num;
        ++num;
    }

    return start_num;
}
