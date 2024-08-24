#include "fixture.hpp"
#include "string/parser.hpp"
#include "file_system/read_target.hpp"
#include "file_system/file_read.hpp"

namespace kustest
{
class UTestString : public Fixture {};

TEST_F(UTestString, test_slice_empty_input)
{
    std::string_view s;
    char buffer[256];
    std::string delimiters = ", ";
    std::string erase = "!";

    auto result = str::Parser::parse_in_new(s, buffer, delimiters, erase);
    ASSERT_EQ(result.size(), 0);
}

TEST_F(UTestString, test_slice_empty_output)
{
    std::string_view s = ",!,,, ,,!";
    char buffer[256];
    std::string delimiters = ", ";
    std::string erase = "!";

    auto result = str::Parser::parse_in_new(s, buffer, delimiters, erase);
    ASSERT_EQ(result.size(), 0);
}

TEST_F(UTestString, test_slice_simple)
{
    std::string_view s = "Hello, world!";
    char buffer[256];
    std::string delimiters = ", ";
    std::string erase = "!";

    auto result = str::Parser::parse_in_new(s, buffer, delimiters, erase);
    ASSERT_EQ(result.size(), 2);
    ASSERT_EQ(result[0], "Hello");
    ASSERT_EQ(result[1], "world");
}

TEST_F(UTestString, test_slice_repeated_delimiters) {
    std::string_view s = "!Hello!, ,world!!,,  , , !!";
    char buffer[256];
    std::string delimiters = ", ";
    std::string erase = "!";

    auto result = str::Parser::parse_in_new(s, buffer, delimiters, erase);
    ASSERT_EQ(result.size(), 2);
    ASSERT_EQ(result[0], "Hello");
    ASSERT_EQ(result[1], "world");
}

TEST_F(UTestString, test_slice_into_old_buffer)
{
    std::string s = "apple,,,orange...banana!grape!!pear--peach";
    std::string delimiters = ",.- !";
    std::string erase = "!";

    auto result = str::Parser::parse_in_current(s, delimiters, erase);
    ASSERT_EQ(result.size(), 6);
    ASSERT_EQ(result[0], "apple");
    ASSERT_EQ(result[1], "orange");
    ASSERT_EQ(result[2], "banana");
    ASSERT_EQ(result[3], "grape");
    ASSERT_EQ(result[4], "pear");
    ASSERT_EQ(result[5], "peach");
}

TEST_F(UTestString, get_data)
{
    fs::DataTarget target("test data");
    EXPECT_EQ(fs::FileRead::getData(target), "test data");
}

TEST_F(UTestString, get_lines)
{
    std::string data = "line1\nline2\nline3";
    fs::DataTarget target(data);
    auto lines = fs::FileRead::getLines(target);
    EXPECT_EQ(lines.size(), 3);
    EXPECT_EQ(lines[0], "line1");
    EXPECT_EQ(lines[1], "line2");
    EXPECT_EQ(lines[2], "line3");
}

TEST_F(UTestString, get_words)
{
    std::string data = "word1;word2\nword3 word4";
    fs::DataTarget target(data);
    auto words = fs::FileRead::getWords(target, str::Separator::newWord);
    EXPECT_EQ(words.size(), 2);
    EXPECT_EQ(words[0].size(), 2);
    EXPECT_EQ(words[0][0], "word1");
    EXPECT_EQ(words[0][1], "word2");
    EXPECT_EQ(words[1].size(), 2);
    EXPECT_EQ(words[1][0], "word3");
    EXPECT_EQ(words[1][1], "word4");
}

TEST_F(UTestString, get_words_map)
{
    std::string data = "key1 value1\nkey2 value2";
    fs::DataTarget target(data);
    auto wordsMap = fs::FileRead::getWordsMap(target, str::Separator::space);
    EXPECT_EQ(wordsMap.size(), 2);
    EXPECT_EQ(wordsMap["key1"], "value1");
    EXPECT_EQ(wordsMap["key2"], "value2");
}

TEST_F(UTestString, get_words_set)
{
    std::string data = "word1; word2 ;word3";
    fs::DataTarget target(data);
    auto wordsSet =fs::FileRead::getWordsSet(target, str::Separator::newWord);
    EXPECT_EQ(wordsSet.size(), 3);
    EXPECT_TRUE(wordsSet.find("word1") != wordsSet.end());
    EXPECT_TRUE(wordsSet.find("word2") != wordsSet.end());
    EXPECT_TRUE(wordsSet.find("word3") != wordsSet.end());
}

} // namespace kustest
