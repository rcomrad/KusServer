#include "kernel/tester/fixture.hpp"

namespace kustest
{

// class RvalueTest : public Fixture
// {
// };

// //--------------------------------------------------------------------------------

// class OnlyRef
// {
// public:
//     OnlyRef(int a_data) : m_data(a_data)
//     {
//     }

//     OnlyRef(const OnlyRef&) = delete;
//     OnlyRef(OnlyRef&&)      = delete;

//     OnlyRef& operator=(const OnlyRef&) = delete;
//     OnlyRef& operator=(OnlyRef&&)      = delete;

//     int getData()
//     {
//         return m_data;
//     }

// private:
//     int m_data;
// };

// template <typename T>
// void
// testOnlyRef(T t)
// {
//     EXPECT_EQ(t.getData(), 5);
// }

// TEST_F(RvalueTest, ref)
// {
//     OnlyRef obj(5);
//     testOnlyRef(obj);
// }

//--------------------------------------------------------------------------------

} // namespace kustest
