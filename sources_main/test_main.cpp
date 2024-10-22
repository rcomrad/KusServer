#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "core/logging/logging.hpp"

int
main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    ::testing::InitGoogleMock(&argc, argv);
    ::testing::GTEST_FLAG(filter) = "WebTest.*";

    core::Printer::setLogLevel(core::LogLevel::WARN);

    return RUN_ALL_TESTS();
}
