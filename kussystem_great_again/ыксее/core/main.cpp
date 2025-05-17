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


void print(const char* s)
{
	printf("%s", s);
}

#pragma optimize("gf", on)
char* get() 
{
	char c[5] = "abv";
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
