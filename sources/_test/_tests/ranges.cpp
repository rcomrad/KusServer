#include <algorithm>
#include <ranges>
#include <sstream>
#include <vector>

#include "kernel/tester/fixture.hpp"

namespace kustest
{

class RangesTest : public Fixture
{
};

//--------------------------------------------------------------------------------

TEST_F(RangesTest, for_each_basic)
{
    std::stringstream os;

    std::vector<int> a{20, 3, 10, 2, 1};
    for_each(a.begin(), a.end(),
             [&os](int d)
             {
                 if (d < 5) os << d * 2 << " ";
             });

    EXPECT_EQ(os.str(), "6 4 2 ");
}

//--------------------------------------------------------------------------------

// TEST_F(RangesTest, for_each_basic)
// {
//     std::stringstream os;

//     std::vector<int> a{20, 3, 10, 2, 1}, v;
//     std::copy_if(a, begin(), a.end(), std::back_inserter(v),
//                  [](int n) { return n < 5; });
//     std::transform(v.begin(), v.end(), d_start, [](int n) { return n * 2; });

//     EXPECT_EQ(os.str(), "6 4 2 ");
// }

//--------------------------------------------------------------------------------

TEST_F(RangesTest, range_sort)
{
    std::vector<int> a{1, 9, 2, 4, 8, 6, 3, 5, 7};
    std::vector<int> answer{1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::ranges::sort(a);
    EXPECT_EQ(a, answer);
}

//--------------------------------------------------------------------------------

// TEST_F(RangesTest, for_each_basic)
// {
//     std::stringstream os;

//     auto r = ranges::views::filter([](int n) { return n < 5; }) |
//              ranges::views::transform([](int n) { return n * 2; });

//     ranges::copy(r, std::ostream_iterator<int>{os, " "});
//     std::vector<int> a{20, 3, 10, 2, 1};
//     for_each(a.begin(), a.end(),
//              [&os](int d)
//              {
//                  if (d < 5) os << d * 2 << " ";
//              });

//     EXPECT_EQ(os.str(), "6 4 2 ");
// }

//--------------------------------------------------------------------------------

} // namespace kustest
