#include <iostream>

#include "core/core.hpp"

//--------------------------------------------------------------------------------

// int
// main(int argc, char* argv[])
// {
//     std::cout << "LAMPA\n";
//     // TODO: write time

//     core::Core::setup();
//     core::Core::run();

//     return 0;
// }

#include <iostream>

#include "database/database_structures.hpp"
int
main(int argc, char* argv[])
{
    data::Dummy d;
    std::cout << d.getAsCondition();
    return 0;
}

//--------------------------------------------------------------------------------
