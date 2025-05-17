#include "fixture.hpp"

#include <cstdio>

#include "kernel/framework/logger/include_me.hpp"

kustest::Fixture::Fixture()
{
}

kustest::Fixture::~Fixture()
{
    std::fflush(stdout);
    std::fflush(stderr);
}
