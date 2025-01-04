#include <iostream>
#include <regex>
#include <string>

#include "ontology/web_factory.hpp"
#include "utility/common/src_path.hpp"
#include "utility/string/slicer.hpp"

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

        std::string ans_str = a_test_resalt;
        auto web_repr       = web.serialize();
        auto ser_copy       = web_repr;
        EXPECT_EQ(ans_str, web_repr);

        auto ans = util::Slicer::process(ans_str, ";");
        auto out = util::Slicer::process(web_repr, ";");

        EXPECT_EQ(ans.size(), out.size());
        for (int i = 0; i < std::min(ans.size(), out.size()); ++i)
        {
            EXPECT_EQ(ans[i], out[i]);
        }

        std::cout << "-------------------\n";
        std::cout << web.print() << std::endl;

        std::string ser_result = "std::string result = \"";
        ser_result += std::regex_replace(ser_copy, std::regex(";"), ";\"\n\"");
        ser_result.pop_back();
        ser_result.back() = ';';
        std::cout << ser_result << std::endl;

        std::cout << "-------------------\n";
    }
};

TEST_F(WebTest, basic_declare)
{
    std::string filename = "basic_declare.txt";
    std::string result   = "(main)[-2:{int}];"
                           "(a)[-4:{int}];"
                           "(int)[2:{main}4:{a}];";
    check(filename, result);
}

TEST_F(WebTest, variable_declarations)
{
    std::string filename = "variable_declarations.txt";
    std::string result   = "(5)[5:{lit_5}-5:{a+b}-6:{a}];"
                           "(6)[5:{lit_6}-6:{z}];"
                           "(7)[5:{lit_7}-5:{a+b}-6:{b}];"
                           "(a+b)[5:{7,5}-6:{s}];"
                           "(main)[-2:{int}];"
                           "(a)[-4:{int}6:{5}];"
                           "(b)[-4:{int}6:{7}];"
                           "(s)[-4:{int}6:{a+b}];"
                           "(z)[-4:{int}6:{6}];"
                           "(int)[2:{main}4:{b,z,s,a}];"
                           "(lit_5)[-5:{5}];"
                           "(lit_6)[-5:{6}];"
                           "(lit_7)[-5:{7}];";
    check(filename, result);
}

TEST_F(WebTest, a_plus_b)
{
    std::string filename = "a_plus_b.txt";
    std::string result   = "(a+b)[5:{cin_1,cin_0}-6:{cout_0}];"
                           "(main)[-2:{int}];"
                           "(a)[-4:{int}6:{cin_0}];"
                           "(b)[-4:{int}6:{cin_1}];"
                           "(cin)[7:{cin_1,cin_0}];"
                           "(cout)[7:{cout_0}];"
                           "(int)[2:{main}4:{b,a}];"
                           "(cin_0)[-5:{a+b}-6:{a}-7:{cin}];"
                           "(cin_1)[-5:{a+b}-6:{b}-7:{cin}];"
                           "(cout_0)[6:{a+b}-7:{cout}];";
    check(filename, result);
}

} // namespace kustest
