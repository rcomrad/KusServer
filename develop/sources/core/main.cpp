#include <iostream>

#include "core/core.hpp"

//--------------------------------------------------------------------------------

int
main(int argc, char* argv[])
{
    std::cout << "LAMPA\n";

    core::Core app;
    app.run();

    return 0;
}

//--------------------------------------------------------------------------------
