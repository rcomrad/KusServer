//--------------------------------------------------------------------------------

#include <iostream>

#include "kernel/framework/logging/printer.hpp"
#include "kernel/framework/module/registry.hpp"
#include "kernel/utility/common/yield.hpp"

//--------------------------------------------------------------------------------

int
main(int argc, char* argv[])
{
    std::cout << "LAMPA\n";
    fflush(stdout);
    // TODO: write time

    core::Printer::setOutputType(core::Printer::OutputType::FILE, "logs.txt");

    core::ModuleRegistry::initModules();
    core::ModuleRegistry::runModules();
    // TODO: isExit()
    while (core::ModuleRegistry::isRunning())
    {
        util::Yield::large();
    }
    core::ModuleRegistry::termModules();

    return 0;
}

//--------------------------------------------------------------------------------
