#include "callback_register.hpp"

#include "callback_storage.hpp"

core::CallbackRegister::CallbackRegister(const str::string& aVolumeName,
                                         const str::string& aNodeName,
                                         void* aFunc) noexcept
{
    CallbackStorage::add(aVolumeName, aNodeName, aFunc);
}
