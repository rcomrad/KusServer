#include <iostream>

#include "core/core.hpp"

//--------------------------------------------------------------------------------

int
main(int argc, char* argv[])
{
    std::cout << "LAMPA\n";
    // TODO: write time

    core::Core::setup();
    core::Core::run();

    return 0;
}

//--------------------------------------------------------------------------------
