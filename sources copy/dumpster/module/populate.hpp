#ifndef POPULATE_HPP
#define POPULATE_HPP

//--------------------------------------------------------------------------------

#include <string>

#include "module_base.hpp"

//--------------------------------------------------------------------------------

namespace mod
{
class Populate : public ModuleBase
{
protected:
    str::String doAction(const Command& aCommand) noexcept override;

private:
    static Populate mInstance;
    Populate() noexcept;

    static void remakeDatabase() noexcept;
    static void populate() noexcept;

    static void createDatabaseFromFile(str::String aFileName) noexcept;
    static void createEnvironment() noexcept;
};
} // namespace mod

//--------------------------------------------------------------------------------

#endif // !POPULATE_HPP
