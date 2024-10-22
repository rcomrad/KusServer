#include <fstream>
#include <iostream>
#include <string>

#include "ontology/web.hpp"

#include "fixture.hpp"

namespace kustest
{

class WebTest : public Fixture
{
};

TEST_F(WebTest, smoke)
{
    std::string code;
    std::ifstream code_file("basic_declare.txt");
    std::getline(code_file, code);

    onto::Web web_from_code;
    web_from_code.applyData(code);

    std::cout << web_from_code.print();

    // onto::Web jury_web;
    // jury_web.createFunction();
}

} // namespace kustest
