#include "module_base.hpp"

#include "module_handler.hpp"

mod::ModuleBase::Command::Command(int a,
                                  const std::string& b,
                                  const std::string& c)
    : num(a), value(b), argument(c)
{
}

mod::ModuleBase::ModuleBase(const std::vector<std::string>& aNameArray) noexcept
{
    for (auto& i : aNameArray)
    {
        mod::ModuleHandler::addCommand(i, this);
    }
}
