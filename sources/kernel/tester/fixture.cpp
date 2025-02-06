#include "fixture.hpp"

#include <cstdio>

kustest::Fixture::~Fixture()
{
    std::fflush(stdout);
    std::fflush(stderr);
}
