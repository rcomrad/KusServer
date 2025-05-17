#include <iostream>

#include "core/core.hpp"

//--------------------------------------------------------------------------------

int
main(int argc, char* argv[])
{
    std::cout << "LAMPA\n";

    core::Core::getInstance().run();

    return 0;
}

//--------------------------------------------------------------------------------
