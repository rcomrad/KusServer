#include "command.hpp"

modul::Command::Command(int aNum,
                        const std::string& aValue,
                        const std::string& aArgument,
                        bool aSaveResult) noexcept
    : num(aNum), value(aValue), argument(aArgument), saveResult(aSaveResult)
{
}
