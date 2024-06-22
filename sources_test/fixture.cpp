#include "fixture.hpp"

#include <cstdio>

kustest::Fixture::Fixture() noexcept
{
    setUp();
}

kustest::Fixture::~Fixture()
{
    std::fflush(stdout);
    std::fflush(stderr);
    tearDown();
}

void
kustest::Fixture::setUp() noexcept
{
}

void
kustest::Fixture::tearDown() noexcept
{
}
