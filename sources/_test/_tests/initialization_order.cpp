#include <string>
#include <vector>

#include "kernel/tester/fixture.hpp"

namespace kustest
{

class InitializationOrderTest : public Fixture
{
};

//--------------------------------------------------------------------------------
// Complex concept

static std::vector<std::string> global_order;

#define CONSTRUCTOR(name)                 \
    name()                                \
    {                                     \
        global_order.emplace_back(#name); \
    }
#define DESTRUCTOR(name)                      \
    ~name()                                   \
    {                                         \
        global_order.emplace_back("~" #name); \
    }

namespace
{
struct A
{
    CONSTRUCTOR(A);
    DESTRUCTOR(A);
};
struct B
{
    CONSTRUCTOR(B);
    DESTRUCTOR(B);
};
struct C
{
    CONSTRUCTOR(C);
    DESTRUCTOR(C);
};

struct Top
{
    Top() : c(), b(), a()
    {
        global_order.emplace_back("Top");
    }
    DESTRUCTOR(Top);

    B b;
    A a;
    C c;
};
} // namespace

//--------------------------------------------------------------------------------

TEST_F(InitializationOrderTest, basic)
{
    global_order.clear();
    {
        Top top;
    }
    std::vector<std::string> answer = {"B",    "A",  "C",  "Top",
                                       "~Top", "~C", "~A", "~B"};
    EXPECT_EQ(global_order, answer);
}

//--------------------------------------------------------------------------------

struct AException
{
    AException()
    {
        global_order.emplace_back("AException");
        throw "exception";
    }
    DESTRUCTOR(AException);
};
struct TopException
{
    CONSTRUCTOR(TopException);
    DESTRUCTOR(TopException);

    B b;
    AException a;
    C c;
};

TEST_F(InitializationOrderTest, exception_inside)
{
    global_order.clear();
    try
    {
        TopException top;
    }
    catch (...)
    {
    }
    std::vector<std::string> answer = {"B", "AException", "~B"};
    EXPECT_EQ(global_order, answer);
}

} // namespace kustest
