#include <memory>
#include <string>
#include <vector>

#include "kernel/tester/fixture.hpp"

/*
https://en.cppreference.com/w/cpp/language/static_cast.html
https://en.cppreference.com/w/cpp/language/dynamic_cast.html

A downcast can also be performed with static_cast, which avoids the cost of the
runtime check, but it is only safe if the program can guarantee (through some
other logic) that the object pointed to by expression is definitely Derived.

Some forms of dynamic_cast rely on run-time type identification (RTTI), that is,
information about each polymorphic class in the compiled program. Compilers
typically have options to disable the inclusion of this information.
*/

namespace kustest
{

class CastTest : public Fixture
{
};

//--------------------------------------------------------------------------------

namespace
{
struct A
{
    int a;
    A(int aa = 0) : a(aa)
    {
    }

    virtual std::string foo() = 0;
    virtual ~A()              = default;
};
struct B1 : A
{
    int b1;
    B1(int aa = -1) : b1(aa)
    {
    }

    std::string foo() override
    {
        return "1B" + std::to_string(b1);
    }

    std::string bb()
    {
        return "bb";
    }
};
struct B2 : A
{
    int b2;
    B2(int aa = -2) : b2(aa)
    {
    }

    std::string foo() override
    {
        return "2B" + std::to_string(b2);
    }
};
struct C : B1
{
    int c;
    C(int aa = -3) : c(aa)
    {
    }

    std::string foo() override
    {
        return "C" + std::to_string(c);
    }

    std::string cc()
    {
        return "cc" + std::to_string(c);
    }
};
} // namespace

//--------------------------------------------------------------------------------

TEST_F(CastTest, value_call)
{
    std::vector<B1> a(5);
    EXPECT_EQ(((C*)(&a[2]))->foo(), "1B-1");
}

TEST_F(CastTest, upward_cast)
{
    C c(5);
    B1* ptr = &c;
    EXPECT_EQ(static_cast<C*>(ptr)->foo(), "C5");
}

// forbidden
// TEST_F(CastTest, downward_cast)
// {
//     B1 b(5);
//     C* ptr = &b;
//     EXPECT_EQ(static_cast<B1*>(ptr)->foo(), "C5");
// }

TEST_F(CastTest, downgrade)
{
    C c(5);
    B1 b = c;
    EXPECT_EQ(b.foo(), "1B-1");
}

// forbidden
// TEST_F(CastTest, upgrade)
// {
//     B1 b(5);
//     C c = b;
//     EXPECT_EQ(c.foo(), "C-1");
// }

//--------------------------------------------------------------------------------

TEST_F(CastTest, concept_smoke)
{
    std::vector<std::unique_ptr<A>> a;

    volatile int num = 0;
    for (volatile int i = 0; i < 5; ++i)
    {
        ++num;
        switch (num % 3)
        {
            case 0:
                a.emplace_back(std::make_unique<C>(num));
                break;
            case 1:
                a.emplace_back(std::make_unique<B1>(num));
                break;
            case 2:
                a.emplace_back(std::make_unique<B2>(num));
                break;
        }
    }

    EXPECT_EQ(a[0]->foo(), "1B1");
    EXPECT_EQ(a[1]->foo(), "2B2");
    EXPECT_EQ(a[2]->foo(), "C3");

    EXPECT_EQ(static_cast<C*>(a[2].get())->cc(), "cc3");
}

//--------------------------------------------------------------------------------

namespace
{
struct Dereved1 : virtual A
{
    int var1;
    Dereved1(int q = -10) : var1(q)
    {
    }

    std::string foo() override
    {
        return "1Dereved" + std::to_string(var1);
    }

    std::string aa()
    {
        return "aa" + std::to_string(var1);
    }
};
struct Dereved2 : virtual A
{
    int var2;
    Dereved2(int q = -11) : var2(q)
    {
    }

    std::string foo() override
    {
        return "2Dereved" + std::to_string(var2);
    }

    std::string bb()
    {
        return "bb" + std::to_string(var2);
    }
};
struct Combined : Dereved1, Dereved2
{
    int varc;
    Combined(int q = -12) : varc(q)
    {
    }

    std::string foo() override
    {
        return "Combined" + std::to_string(varc);
    }

    std::string cc()
    {
        return "cc" + std::to_string(varc);
    }
};
} // namespace

TEST_F(CastTest, virtual_inheritance)
{
    std::vector<std::unique_ptr<A>> a;

    volatile int num = 9;
    for (volatile int i = 0; i < 5; ++i)
    {
        ++num;
        switch (num % 3)
        {
            case 0:
                a.emplace_back(std::make_unique<Combined>(num));
                break;
            case 1:
                a.emplace_back(std::make_unique<Dereved1>(num));
                break;
            case 2:
                a.emplace_back(std::make_unique<Dereved2>(num));
                break;
        }
    }

    EXPECT_EQ(a[0]->foo(), "1Dereved10");
    EXPECT_EQ(a[1]->foo(), "2Dereved11");
    EXPECT_EQ(a[2]->foo(), "Combined12");

    // EXPECT_EQ(static_cast<Combined*>(a[2].get())->cc(), "cc12");
    EXPECT_EQ(dynamic_cast<Combined*>(a[2].get())->cc(), "cc12");
}

//--------------------------------------------------------------------------------

} // namespace kustest
