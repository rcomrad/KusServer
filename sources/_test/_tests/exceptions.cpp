
#include "kernel/tester/fixture.hpp"

#pragma warning(push)
#pragma warning(disable : 4286)

namespace kustest
{

class ExceptionsTest : public Fixture
{
};

//--------------------------------------------------------------------------------

struct A
{
};
struct B : A
{
};
struct C : A
{
};

//--------------------------------------------------------------------------------

template <typename T>
int
throw_func_good_val()
{
    int result = 0;
    try
    {
        throw T();
    }
    catch (B)
    {
        result = 1;
    }
    catch (A)
    {
        result = 2;
    }
    catch (...)
    {
        result = 3;
    }
    return result;
}

TEST_F(ExceptionsTest, good_throw_base_val)
{
    EXPECT_EQ(throw_func_good_val<A>(), 2);
}

TEST_F(ExceptionsTest, good_throw_derived_val)
{
    EXPECT_EQ(throw_func_good_val<B>(), 1);
}

TEST_F(ExceptionsTest, good_throw_base_subling_val)
{
    EXPECT_EQ(throw_func_good_val<C>(), 2);
}

//--------------------------------------------------------------------------------

template <typename T>
int
throw_func_bad_val()
{
    int result = 0;
    try
    {
        throw T();
    }
    catch (A)
    {
        result = 1;
    }
    catch (B)
    {
        result = 2;
    }
    catch (...)
    {
        result = 3;
    }
    return result;
}


TEST_F(ExceptionsTest, bad_throw_base_val)
{
    EXPECT_EQ(throw_func_bad_val<A>(), 1);
}

TEST_F(ExceptionsTest, bad_throw_derived_val)
{
    EXPECT_EQ(throw_func_bad_val<B>(), 1);
}

TEST_F(ExceptionsTest, bad_throw_base_subling_val)
{
    EXPECT_EQ(throw_func_bad_val<C>(), 1);
}

//--------------------------------------------------------------------------------

template <typename T>
int
throw_func_good_ref()
{
    int result = 0;
    try
    {
        throw T();
    }
    catch (B&)
    {
        result = 1;
    }
    catch (A&)
    {
        result = 2;
    }
    catch (...)
    {
        result = 3;
    }
    return result;
}

TEST_F(ExceptionsTest, good_throw_base_ref)
{
    EXPECT_EQ(throw_func_good_ref<A>(), 2);
}

TEST_F(ExceptionsTest, good_throw_derived_ref)
{
    EXPECT_EQ(throw_func_good_ref<B>(), 1);
}

TEST_F(ExceptionsTest, good_throw_base_subling_ref)
{
    EXPECT_EQ(throw_func_good_ref<C>(), 2);
}
//--------------------------------------------------------------------------------

template <typename T>
int
throw_func_bad_ref()
{
    int result = 0;
    try
    {
        throw T();
    }
    catch (A&)
    {
        result = 1;
    }
    catch (B&)
    {
        result = 2;
    }
    catch (...)
    {
        result = 3;
    }
    return result;
}

TEST_F(ExceptionsTest, bad_throw_base_ref)
{
    EXPECT_EQ(throw_func_bad_ref<A>(), 1);
}

TEST_F(ExceptionsTest, bad_throw_derived_ref)
{
    EXPECT_EQ(throw_func_bad_ref<B>(), 1);
}

TEST_F(ExceptionsTest, bad_throw_base_subling_ref)
{
    EXPECT_EQ(throw_func_bad_ref<C>(), 1);
}

//--------------------------------------------------------------------------------

TEST_F(ExceptionsTest, ref_catch)
{
    int result = 0;
    try
    {
        throw std::string{"123"};
    }
    catch (const std::string& str)
    {
        result = std::stoi(str);
    }
    catch (...)
    {
    }
    EXPECT_EQ(result, 123);
}

//--------------------------------------------------------------------------------

class Base
{
};
class Dereved : Base
{
};

TEST_F(ExceptionsTest, private_inheritance)
{
    int result = 0;
    try
    {
        throw Dereved();
    }
    catch (Base)
    {
        result = 1;
    }
    catch (Dereved)
    {
        result = 2;
    }
    catch (...)
    {
        result = 3;
    }
    EXPECT_EQ(result, 2);
}
//--------------------------------------------------------------------------------

} // namespace kustest

#pragma warning(pop)
