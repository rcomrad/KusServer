#include "fixture.hpp"
#include "string/parser.hpp"

namespace kustest
{
class UTestString : public Fixture {};

TEST_F(UTestString, test_slice_simple)
{
    std::string_view s = "Hello, world!";
    char buffer[256];
    std::string delimiters = ", ";
    std::string erase = "!";
    auto result = str::Parser::slice(s, buffer, delimiters, erase);
    ASSERT_EQ(result.size(), 2);
    ASSERT_EQ(result[0], "Hello");
    ASSERT_EQ(result[1], "world");
}

TEST_F(UTestString, test_slice_repeated_delimiters) {
    std::string_view s = "!Hello!, ,world!!,,  , , !!";
    char buffer[256];
    std::string delimiters = ", ";
    std::string erase = "!";
    auto result = str::Parser::slice(s, buffer, delimiters, erase);
    ASSERT_EQ(result.size(), 2);
    ASSERT_EQ(result[0], "Hello");
    ASSERT_EQ(result[1], "world");
}

TEST_F(UTestString, test_slice_complex_case)
{
    std::string_view s = "apple,,,orange...banana!grape!!pear--peach";
    char buffer[256];
    std::string delimiters = ",.- !";
    std::string erase = "!";

    auto result = str::Parser::slice(s, buffer, delimiters, erase);

    ASSERT_EQ(result.size(), 6);
    ASSERT_EQ(result[0], "apple");
    ASSERT_EQ(result[1], "orange");
    ASSERT_EQ(result[2], "banana");
    ASSERT_EQ(result[3], "grape");
    ASSERT_EQ(result[4], "pear");
    ASSERT_EQ(result[5], "peach");
}

} // namespace kustest