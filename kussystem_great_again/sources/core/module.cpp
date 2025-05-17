#include "module.hpp"

#include "file_system/file_read.hpp"

#include "callback_storage.hpp"

void
core::Module::setupModules() noexcept
{
    auto moduleList =
        fs::FileRead::getWordsSet(fs::ReadFromStoredFile("module_list.cfg"));

    auto setupFuncs =
        core::CallbackStorage::getVolumeCallbacks(CALLBACK_VOLUME_SETUP);

    for (auto& i : setupFuncs)
    {
        if (moduleList.count(i.first))
        {
            auto settings = ((ModuleSettings(*)())i.second)();
            settings.mVariableRegister();
            CallbackStorage::add(CALLBACK_VOLUME_START, i.first,
                                 (void*)settings.mModuleLoppFunc);
        }
    }
}
