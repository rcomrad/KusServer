#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "core/logging/logging.hpp"

int
main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    ::testing::InitGoogleMock(&argc, argv);

    core::Printer::setLogLevel(core::LogLevel::WARNING);

    return RUN_ALL_TESTS();
}
