#include <iostream>
#include <semaphore>

#include "fixture.hpp"

namespace kustest
{

class CPP20 : public Fixture
{
};

TEST_F(CPP20, use_set_command)
{
    // std::cout << "CPP standart test!\n";
    std::counting_semaphore<10> gfhfghfgh{5};
    // std::counting
}

} // namespace kustest
