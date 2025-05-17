#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <iostream>
#include <stdexcept>

#include "kernel/framework/logging/logging.hpp"

int
main(int argc, char** argv)
{
    try
    {
        ::testing::InitGoogleTest(&argc, argv);
        ::testing::InitGoogleMock(&argc, argv);

        // ::testing::GTEST_FLAG(filter) = "WebTest.a_plus_b";
        // ::testing::GTEST_FLAG(filter) = "WebTest.*";
        // ::testing::GTEST_FLAG(filter) = "UTestTablePrint.*";
        // ::testing::GTEST_FLAG(filter) = "NumPrefixTreeTest.*";
        // ::testing::GTEST_FLAG(filter) = "PipeExample.*";
        // ::testing::GTEST_FLAG(filter) = "EngineTest.*";
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
