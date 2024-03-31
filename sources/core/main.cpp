#include <iostream>

#include "core/core.hpp"

//--------------------------------------------------------------------------------

int
main(int argc, char* argv[])
{
    std::cout << "LAMPA\n";
    // XTODO: write time
    core::Core::getInstance().run();

    return 0;
}

//--------------------------------------------------------------------------------
