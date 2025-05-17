#include "module_base.hpp"

#include "module_handler.hpp"

mod::ModuleBase::Command::Command(int a,
                                  const std::string& b,
                                  const std::string& c,
                                  bool r)
    : num(a), value(b), argument(c), saveResult(r)
{
}

mod::ModuleBase::ModuleBase(const std::vector<std::string>& aNameArray) noexcept
{
    for (auto& i : aNameArray)
    {
        mod::ModuleHandler::addCommandHandler(i, this);
    }
}
