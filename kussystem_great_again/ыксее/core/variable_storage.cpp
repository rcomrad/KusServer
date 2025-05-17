#include "variable_storage.hpp"

#include "core/logging.hpp"

#include "file_system/file_read.hpp"
#include "file_system/path.hpp"

#include "string/parser.hpp"
#include "string/separators.hpp"

#include "command_handler.hpp"

//--------------------------------------------------------------------------------

const int core::VariableStorage::CORRUPTED_VALUE = -100;

core::CallbackRegister core::VariableStorage::mCommandHandlerCallback(
    {core::CommandHandler::CALLBACK_VOLUME_COMMAND_HANDLER, "set",
     (void*)core::VariableStorage::setCommandHandler});

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

//--------------------------------------------------------------------------------

void
core::VariableStorage::setCommandHandler(const Command& aCommand) noexcept
{
    getInstance().setCommandHandlerNonstatic(aCommand);
}

void
core::VariableStorage::setCommandHandlerNonstatic(
    const Command& aCommand) noexcept
{
    for (const auto& i : aCommand.variables)
    {
        // TODO: in separate function
        auto it = mVariableNames.find(i.first);
        if (it != mVariableNames.end())
        {
            int num = it->second;
            int val = mVariables[num].mParser(i.second);
            if (CORRUPTED_VALUE != val)
            {
                mVariables[num].mValue = val;
                LOG_INFO("Set variable ", i.first, "with value", i.second);
            }
            else
            {
                LOG_ERROR("Set command for variable", i.first,
                          "failed: corrupted variable value", i.second);
            }
        }
        else
        {
            LOG_ERROR("Set command failed: no such variable", i.first);
        }
    }
}
