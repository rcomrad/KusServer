//--------------------------------------------------------------------------------

#include <iostream>
#include <stdexcept>

#include "kernel/framework/core/kernel.hpp"

//--------------------------------------------------------------------------------

int
main(int argc, char* argv[])
{
    try
    {
        KERNEL.create();
        KERNEL.listenSTDIN();
        KERNEL.run();
        KERNEL.destroy();
    }
    catch (const std::runtime_error& err)
    {
        std::cout << "EXCEPTION: " << err.what();
    }
    catch (...)
    {
        std::cout << "UNKNOWN EXCEPTION";
    }

    return 0;
}

//--------------------------------------------------------------------------------
