#include <iostream>

#include "core/core.hpp"

//--------------------------------------------------------------------------------

#include "database/database.hpp"
#include "database/database_structures.hpp"
int
main(int argc, char* argv[])
{
    std::cout << "LAMPA\n";
    // TODO: write time

    core::Core::setup();
    core::Core::run();

    // data::ConnectionPool::create(0);
    // auto& conn = data::ConnectionPool::get();
    // conn.populateDatabse();

    // data::ConnectionPool::put(conn);

    return 0;
}

//--------------------------------------------------------------------------------
