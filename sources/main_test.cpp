#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <iostream>
#include <stdexcept>

#include "kernel/framework/logger/include_me.hpp"

int
main(int argc, char** argv)
{
    try
    {
        ::testing::InitGoogleTest(&argc, argv);
        ::testing::InitGoogleMock(&argc, argv);

        // ::testing::GTEST_FLAG(filter) = "UTablePrinter.*";
    }
    catch (const std::runtime_error& err)
    {
        std::cout << "EXCEPTION: " << err.what();
    }
    catch (...)
    {
        std::cout << "UNKNOWN EXCEPTION";
    }

    return RUN_ALL_TESTS();
}
