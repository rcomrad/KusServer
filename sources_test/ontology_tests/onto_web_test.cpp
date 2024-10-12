#include <iostream>
#include <string>

#include "ontology/web_factory.hpp"
#include "utility/common/src_path.hpp"

#include "fixture.hpp"

namespace kustest
{

class WebTest : public Fixture
{
};

TEST_F(WebTest, smoke)
{
    auto file_name = __FOLDERNAME_STR__ + "basic_declare.txt";
    auto web       = onto::WebFactory::fromFile(file_name);
    std::cout << "-------------------\n";
    std::cout << web.print();
    std::cout << "-------------------\n";
}

} // namespace kustest
