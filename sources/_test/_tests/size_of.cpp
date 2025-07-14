#include "kernel/tester/fixture.hpp"

namespace kustest
{

class UDummyTest : public Fixture
{
};

//--------------------------------------------------------------------------------

/*
The C++ standard does not permit objects (or classes) of size 0. This is because
that would make it possible for two distinct objects to have the same memory
location. This is the reason behind the concept that even an empty class and
structure must have a size of at least 1.
*/

struct Empty
{
};

TEST_F(UDummyTest, empty_test)
{
    EXPECT_EQ(sizeof(Empty), 1);
}

//--------------------------------------------------------------------------------

// https://www.youtube.com/watch?v=iz958I8Xb2g
// https://learn.microsoft.com/en-us/cpp/cpp/alignment-cpp-declarations?view=msvc-170

struct Example
{
    short a; // 2
    char b;  // 1
    int* c;  // 8
    float d; // 4
}; // max(all) = 8

/*
This is data alignment of the Example structure:

aac-|----
cccc|cccc
dddd|----

For effective data access, all elements must be properly aligned. This means
that the memory address of each element must be a multiple of X, where X is the
alignment value. This applies to each element of the structure, as well as to
the structure itself. To properly align the structure itself, we add padding
even at the end of the data elements.

For example, a pointer has an alignment of 8, so it can only start at an address
that is a multiple of 8.
*/

TEST_F(UDummyTest, alignment_example)
{
    EXPECT_EQ(sizeof(Example), 24);
    Example array[3];
    EXPECT_EQ(sizeof(array), 24 * 3);
    EXPECT_EQ(alignof(Example), 8);
}

//--------------------------------------------------------------------------------

/*
alignas allows us to change the alignment of types. This can be useful to avoid
sharing the cache line between multiple cores (two cores modify different
variables in the same cache line, invalidating each other's cache). This is
called "false data sharing", as opposed to "true data sharing", when cpus try to
change same variable.
*/

struct KeepApart
{
    alignas(std::hardware_destructive_interference_size) std::atomic<int> cat;
    alignas(std::hardware_destructive_interference_size) std::atomic<int> dog;
};

TEST_F(UDummyTest, cache_line)
{
    EXPECT_EQ(alignof(KeepApart), 64);
}

//--------------------------------------------------------------------------------

struct Int
{
    int a;
};
struct IntChar
{
    int a;
    char b;
};
struct IntCharDouble
{
    int a;
    char b;
    double c;
};

TEST_F(UDummyTest, alignment_mix)
{
    EXPECT_EQ(sizeof(Int), 4);
    EXPECT_EQ(sizeof(IntChar), 8);
    EXPECT_EQ(sizeof(IntCharDouble), 16);
}

//--------------------------------------------------------------------------------

struct Double
{
    double c;
};
struct DoubleInt
{
    double c;
    int a;
};
struct DoubleIntChar
{
    double c;
    int a;
    char b;
    char scary;
};

TEST_F(UDummyTest, alignment_good)
{
    EXPECT_EQ(sizeof(Double), 8);
    EXPECT_EQ(sizeof(DoubleInt), 16);
    EXPECT_EQ(sizeof(DoubleIntChar), 16);
}

//--------------------------------------------------------------------------------

struct Char
{
    char b;
};
struct CharInt
{
    int a;
    char b;
};
struct CharIntDouble
{
    char b;
    int a;
    double c;
};
struct CharIntDoubleScary
{
    char b;
    int a;
    double c;
    char scary;
};
struct CharIntDoubleNotSoScary
{
    char b;
    char scary;
    int a;
    double c;
};

TEST_F(UDummyTest, alignment_bad)
{
    EXPECT_EQ(sizeof(Char), 1);
    EXPECT_EQ(sizeof(CharInt), 8);
    EXPECT_EQ(sizeof(CharIntDouble), 16);
    EXPECT_EQ(sizeof(CharIntDoubleScary), 24);
    EXPECT_EQ(sizeof(CharIntDoubleNotSoScary), 16);
}

//--------------------------------------------------------------------------------

struct DoubleIntForArray
{
    double c;
    int a;
};

TEST_F(UDummyTest, struct_array)
{
    EXPECT_EQ(sizeof(DoubleIntForArray), 16);
    DoubleIntForArray array[3];
    EXPECT_EQ(sizeof(array), 16 * 3);
    EXPECT_EQ(alignof(DoubleIntForArray), 8);
}

//--------------------------------------------------------------------------------

struct Virtual
{
    virtual void foo()
    {
    }
    virtual void bar()
    {
    }
    virtual void gaf()
    {
    }
    virtual void af()
    {
    }
};

TEST_F(UDummyTest, virtual_class)
{
    EXPECT_EQ(sizeof(Virtual), 8);
}

//--------------------------------------------------------------------------------

} // namespace kustest
