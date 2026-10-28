#include "fixture.hpp"

#include "kernel/framework/logger/include_me.hpp"

#include <cstdio>

kustest::Fixture::Fixture() : m_filler_cnt(0)
{
}

kustest::Fixture::~Fixture()
{
    std::fflush(stdout);
    std::fflush(stderr);
}
