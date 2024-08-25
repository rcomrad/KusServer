#include "fixture.hpp"
#include "string/parser.hpp"
#include "file_system/read_target.hpp"
#include "file_system/data_read.hpp"

namespace kustest
{
class UTestString : public Fixture {};

TEST_F(UTestString, test_slice_empty_input)
{
    char s[] = "";
    char buffer[256];
    std::string delimiters = ", ";
    std::string erase = "!";

    auto result = str::Parser::parse_in_new(s, buffer, delimiters, erase);
    EXPECT_EQ(result.size(), 0);
}

TEST_F(UTestString, test_slice_empty_output)
{
    std::string_view s = ",!,,, ,,!";
    char buffer[256];
    std::string delimiters = ", ";
    std::string erase = "!";

    auto result = str::Parser::parse_in_new(s, buffer, delimiters, erase);
    EXPECT_EQ(result.size(), 0);
}

TEST_F(UTestString, test_slice_simple)
{
    std::string_view s = "Hello, world!";
    char buffer[256];
    std::string delimiters = ", ";
    std::string erase = "!";

    auto result = str::Parser::parse_in_new(s, buffer, delimiters, erase);
    EXPECT_EQ(result.size(), 2);
    EXPECT_EQ(result[0], "Hello");
    EXPECT_EQ(result[1], "world");
}

TEST_F(UTestString, test_slice_repeated_delimiters) {
    std::string_view s = "!Hello!, ,world!!,,  , , !!";
    char buffer[256];
    std::string delimiters = ", ";
    std::string erase = "!";

    auto result = str::Parser::parse_in_new(s, buffer, delimiters, erase);
    EXPECT_EQ(result.size(), 2);
    EXPECT_EQ(result[0], "Hello");
    EXPECT_EQ(result[1], "world");
}

TEST_F(UTestString, test_slice_into_old_buffer)
{
    std::string s = "appleA Zorange.\t.banana!grape!!pear--peach";;
    std::string delimiters = "AZ,.- !";
    std::string erase;

    auto result = str::Parser::parse_in_current(s, delimiters, erase);
    EXPECT_EQ(result.size(), 7);
    EXPECT_EQ(result[0], "apple");
    EXPECT_EQ(result[1], "orange");
    EXPECT_EQ(result[2], "\t");
    EXPECT_EQ(result[3], "banana");
    EXPECT_EQ(result[4], "grape");
    EXPECT_EQ(result[5], "pear");
    EXPECT_EQ(result[6], "peach");
}

TEST_F(UTestString, get_lines)
{
    std::string data = "line1\nline2\nline3";
    auto lines = fs::DataRead::getLines(data);
    EXPECT_EQ(lines.size(), 3);
    EXPECT_EQ(lines[0], "line1");
    EXPECT_EQ(lines[1], "line2");
    EXPECT_EQ(lines[2], "line3");
}

TEST_F(UTestString, get_words)
{
    std::string data = "word1;word2\nword3 word4";
    auto words = fs::DataRead::getWords(data, str::Separator::newWord);
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
    auto wordsMap = fs::DataRead::getWordsMap(data, str::Separator::space);
    EXPECT_EQ(wordsMap.size(), 2);
    EXPECT_EQ(wordsMap["key1"], "value1");
    EXPECT_EQ(wordsMap["key2"], "value2");
}

TEST_F(UTestString, get_words_set)
{
    std::string data = "word1; word2 ;word3";
    auto wordsSet = fs::DataRead::getWordsSet(data, str::Separator::newWord);
    EXPECT_EQ(wordsSet.size(), 3);
    EXPECT_TRUE(wordsSet.find("word1") != wordsSet.end());
    EXPECT_TRUE(wordsSet.find("word2") != wordsSet.end());
    EXPECT_TRUE(wordsSet.find("word3") != wordsSet.end());
}

} // namespace kustest
