#include <atomic>
#include <semaphore>
#include <thread>
#include <vector>

#include "fixture.hpp"

namespace kustest
{

class UKusBasicCheck : public Fixture
{
};

TEST_F(UKusBasicCheck, simpl_test)
{
    // std::vector<int&> a;
}

// struct Data
// {
    
// }

// void
// foo(std::counting_semaphore<3>& a_sem,
//     std::atomic<int>& a_cnt,
//     std::atomic<bool>& a_flag)
// {
//     a_sem.acquire();
//     ++a_cnt;
//     if (a_cnt == 3)
//     {
//         a_flag = true;
//     }
//     --a_cnt;
//     a_sem.release();
// }

// TEST_F(UKusBasicCheck, semaphore)
// {
//     std::atomic<int> cnt   = 0;
//     std::atomic<bool> flag = false;
//     std::counting_semaphore<3> sem{0};

//     std::atomic<bool> is_running = true;
//     std::vector<std::thread>
// }
} // namespace kustest
