#include <iostream>

// #include "core/core.hpp"

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
#include <stdlib.h>

// #include "database/database_structures.hpp"

void
print(const char* s)
{
    printf("%s", s);
}

auto
get()
{
    char c[5] = "abv";
    // char* c = (char*)malloc(6);
    c[0] = 'A';
    c[1] = 'B';
    c[2] = 'V';
    c[3] = '\0';
    return c;
}

int
main(int argc, char* argv[])
{
    auto res = get();
    print(res);
    // data::Dummy d;
    // std::cout << d.getAsCondition();
    // return 0;
}

//--------------------------------------------------------------------------------
