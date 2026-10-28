#include "fixture.hpp"

#include "kernel/framework/logger/include_me.hpp"

#include <cstdio>

kustest::Fixture::Fixture()
{
}

kustest::Fixture::~Fixture()
{
    std::fflush(stdout);
    std::fflush(stderr);
}
