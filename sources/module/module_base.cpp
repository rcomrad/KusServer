#include "module_base.hpp"

#include "module_handler.hpp"

mod::ModuleBase::ModuleBase(const std::vector<std::string>& aNameArray) noexcept
{
    for (auto& i : aNameArray)
    {
        mod::ModuleHandler::addCommand(i, this);
    }
}
