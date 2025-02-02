#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "core/logging/logging.hpp"

int
main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    ::testing::InitGoogleMock(&argc, argv);

    // ::testing::GTEST_FLAG(filter) = "WebTest.a_plus_b";
    // ::testing::GTEST_FLAG(filter) = "WebTest.*";
    // ::testing::GTEST_FLAG(filter) = "UTestTablePrint.*";
    // ::testing::GTEST_FLAG(filter) = "NumPrefixTreeTest.*";
    // ::testing::GTEST_FLAG(filter) = "PipeExample.*";
    ::testing::GTEST_FLAG(filter) = "EngineTest.*";

    core::Printer::setLogLevel(core::LogLevel::WARN);

    return RUN_ALL_TESTS();
}
