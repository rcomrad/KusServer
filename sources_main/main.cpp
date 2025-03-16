//--------------------------------------------------------------------------------

#include <iostream>

#include "core/logging/printer.hpp"
#include "core/module/registry.hpp"

#include "engine/app.hpp"
#include "utility/common/yield.hpp"
#include "utility/file_system/path_storage.hpp"

//--------------------------------------------------------------------------------

int
main(int argc, char* argv[])
{
    std::cout << "LAMPA\n";
    fflush(stdout);
    // TODO: write time

    core::Printer::setOutputType(core::Printer::OutputType::FILE, "logs.txt");

    // core::ModuleRegistry::initModules();
    // core::ModuleRegistry::runModules();
    // auto p = util::PathStorage::getFolderPath("src");

    // if (p.has_value())
    // {
    //     std::cout << p.value();
    // }

    // TODO: isExit()
    // while (core::ModuleRegistry::isRunning())
    // {
    //     util::Yield::large();
    // }
    // core::ModuleRegistry::termModules();

    kusengine::App a;

    a.run();

    return 0;
}

//--------------------------------------------------------------------------------
