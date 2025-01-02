#include <iostream>
#include <string>

#include "ontology/web_factory.hpp"
#include "utility/common/src_path.hpp"

#include "fixture.hpp"

namespace kustest
{

class WebTest : public Fixture
{
public:
    void check(const std::string& a_test_file_name,
               const std::string& a_test_resalt)
    {
        auto file_name = __FOLDERNAME_STR__ + a_test_file_name;
        auto web       = onto::WebFactory::fromFile(file_name);
        EXPECT_EQ(web.serialize(), a_test_resalt);

        std::cout << "-------------------\n";
        std::cout << web.print() << std::endl;
        std::cout << web.serialize() << std::endl;
        std::cout << "-------------------\n";
    }
};

TEST_F(WebTest, basic_declare)
{
    std::string filename = "basic_declare.txt";
    std::string result   = "main[-------7:{int}-----] "
                           "a[---------9:{int}---] "
                           "int[-1:{main}-3:{a}---------]";
    check(filename, result);
}

TEST_F(WebTest, variable_declarations)
{
    std::string filename = "variable_declarations.txt";
    std::string result   = "5 [----4:{5}------11:{a}-] "
                           "6 [----4:{6}------11:{z}-] "
                           "7 [----4:{7}------11:{b}-] "
                           "main[-------7:{int}-----] "
                           "a[-----5:{5 }---9:{int}---] "
                           "b[-----5:{7 }---9:{int}---] "
                           "s[---------9:{int}---] "
                           "z[-----5:{6 }---9:{int}---] "
                           "int[-1:{main}-3:{s,b,z,a}---------] "
                           "5[----------10:{5 }--] "
                           "6[----------10:{6 }--] "
                           "7[----------10:{7 }--]";
    check(filename, result);
}

} // namespace kustest
