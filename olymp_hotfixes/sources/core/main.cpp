#include <fstream>
#include <string>

#include "domain/error_message.hpp"

#include "core/core.hpp"

//--------------------------------------------------------------------------------

int
main(int argc, char* argv[])
{
    std::cout << "LAMPA\n";
    // std::cout << __cplusplus << std::endl;
    std::vector<std::string> arguments;
    arguments.reserve(argc);
    for (size_t i = 0; i < argc; ++i)
    {
        arguments.push_back(argv[i]);
    }

    core::Core app;

    // if (arguments.size() < 2)
    // {
    //     WRITE_ERROR("Insufficient number of arguments");
    //     arguments = {""s, "getResults"s, "comp.txt"s, " "s, "robox8"s};
    // }

    app.run(arguments);

    return 0;
}

//--------------------------------------------------------------------------------
