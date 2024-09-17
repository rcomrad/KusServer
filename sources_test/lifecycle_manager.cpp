#include "utility/type/lifecycle_manager.hpp"

#include <iostream>

#include "fixture.hpp"

namespace kustest
{

class LifecycleManagerTest : public Fixture
{
};

class EncapsulatedClass
{
public:
    EncapsulatedClass(const std::string& a_name,
                      bool a_flag,
                      int a_num,
                      double a_d) noexcept
        : name(a_name), flag(a_flag), num(a_num), d(a_d)
    {
        g_constructor_counter++;
    }

    ~EncapsulatedClass()
    {
        g_destructor_counter++;
    }

    std::string& getName() noexcept
    {
        return name;
    }
    bool& getFlag() noexcept
    {
        return flag;
    }
    int& getNum() noexcept
    {
        return num;
    }
    double& getD() noexcept
    {
        return d;
    }

    static int g_constructor_counter;
    static int g_destructor_counter;

private:
    std::string name;
    bool flag;
    int num;
    double d;
};

int EncapsulatedClass::g_constructor_counter = 0;
int EncapsulatedClass::g_destructor_counter  = 0;

void
create_and_check(util::LifecycleManager<EncapsulatedClass>& a_manager,
                 const char* a_name,
                 bool a_flag,
                 int a_num,
                 double a_d) noexcept
{
    a_manager.create(a_name, a_flag, a_num, a_d);
    EXPECT_STREQ(a_manager.obj.getName().c_str(), a_name);
    EXPECT_EQ(a_manager.obj.getFlag(), a_flag);
    EXPECT_EQ(a_manager.obj.getNum(), a_num);
    EXPECT_EQ(a_manager.obj.getD(), a_d);
}

TEST_F(LifecycleManagerTest, basic)
{
    // TODO: referance test
    {
        util::LifecycleManager<EncapsulatedClass> object;

        EXPECT_EQ(EncapsulatedClass::g_constructor_counter, 0);
        EXPECT_EQ(EncapsulatedClass::g_destructor_counter, 0);

        create_and_check(object, "Test", true, 37, -75378.4315);
        EXPECT_EQ(EncapsulatedClass::g_constructor_counter, 1);
        EXPECT_EQ(EncapsulatedClass::g_destructor_counter, 0);

        object.destroy();
        object.destroy();
        EXPECT_EQ(EncapsulatedClass::g_constructor_counter, 1);
        EXPECT_EQ(EncapsulatedClass::g_destructor_counter, 1);

        create_and_check(object, "AbrakaDabrA", false, -9574431, 0.00742165);
        EXPECT_EQ(EncapsulatedClass::g_constructor_counter, 2);
        EXPECT_EQ(EncapsulatedClass::g_destructor_counter, 1);
    }

    EXPECT_EQ(EncapsulatedClass::g_constructor_counter, 2);
    EXPECT_EQ(EncapsulatedClass::g_destructor_counter, 2);
}

} // namespace kustest
