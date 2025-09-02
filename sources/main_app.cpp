//--------------------------------------------------------------------------------

#include <iostream>
#include <stdexcept>

#include "engine/app.hpp"
#include "kernel/framework/core/kernel.hpp"

//--------------------------------------------------------------------------------

int
main(int argc, char* argv[])
{
    KERNEL.create();
    kusengine::App m_app;
    m_app.run();

    // try
    // {
    //
    //     KERNEL.listenSTDIN();
    //     KERNEL.run();
    //     KERNEL.destroy();
    // }
    // catch (const std::runtime_error& err)
    // {
    //     std::cout << "EXCEPTION: " << err.what();
    // }
    // catch (...)
    // {
    //     std::cout << "UNKNOWN EXCEPTION";
    // }

    return 0;
}

//--------------------------------------------------------------------------------
