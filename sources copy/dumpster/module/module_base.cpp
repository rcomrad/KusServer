#include "module_base.hpp"

#include "module_handler.hpp"

mod::ModuleBase::Command::Command(int a,
                                  const str::String& b,
                                  const str::String& c)
    : num(a), value(b), argument(c)
{
}

mod::ModuleBase::ModuleBase(const std::vector<str::String>& aNameArray) noexcept
{
    for (auto& i : aNameArray)
    {
        mod::ModuleHandler::addCommand(i, this);
    }
}
