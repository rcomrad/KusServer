#include <string>
#include <unordered_set>

#include "kernel/tester/kernel_fixture.hpp"
#include "kernel/utility/string/parser.hpp"
#include "kernel/utility/string/slicer.hpp"

namespace kustest
{

class UTestString : public KernelFixture
{
    std::vector<std::string> slice(const std::string& a_data,
                                   const std::string& a_sep)
    {
        std::vector<std::string> result{""};
        std::unordered_set<char> sep(a_sep.begin(), a_sep.end());

        for (auto i : a_data)
        {
            if (sep.count(i))
            {
                if (result.empty() || !result.back().empty())
                {
                    result.emplace_back();
                }
                continue;
            }

            result.back().push_back(i);
        }

        if (result.size() && result.back().empty())
        {
            result.pop_back();
        }

        return result;
    }

    std::string erase(const std::string& a_data, const std::string& a_sep)
    {
        std::string result;
        std::unordered_set<char> sep(a_sep.begin(), a_sep.end());
        for (auto i : a_data)
        {
            if (sep.count(i))
            {
                continue;
            }
            result.push_back(i);
        }
        return result;
    }

    std::vector<std::string_view> view(const std::vector<std::string>& a_data)
    {
        std::vector<std::string_view> result;
        for (auto& i : a_data)
        {
            result.emplace_back(i);
        }
        return result;
    }

    std::vector<std::vector<std::string_view>> view(
        const std::vector<std::vector<std::string>>& a_data)
    {
        std::vector<std::vector<std::string_view>> result;
        for (auto& i : a_data)
        {
            result.emplace_back();
            for (auto& j : i)
            {
                result.back().emplace_back(j);
            }
        }
        return result;
    }

public:
    void testSlice(const std::string& a_data,
                   const std::string& a_sep,
                   const std::string& a_erase)
    {
        std::string data = a_data;
        auto ans_1       = slice(data, a_sep);
        auto ans_2       = slice(erase(data, a_erase), a_sep);

        EXPECT_EQ(util::Slicer::copy(data, a_sep), ans_1);
        EXPECT_EQ(data, a_data) << "without erase (1)";
        EXPECT_EQ(util::Slicer::copy(data, a_sep, a_erase), ans_2);
        EXPECT_EQ(data, a_data) << "with erase (2)";

        EXPECT_EQ(util::Slicer::change(data, a_sep), view(ans_1));
        data = a_data;
        EXPECT_EQ(util::Slicer::change(data, a_sep, a_erase), view(ans_2));
    }

    void testLines(const std::string& a_data)
    {
        std::string data = a_data;
        auto ans         = slice(data, "\n");

        EXPECT_EQ(util::Parser::getLinesCopy(data), ans);
        EXPECT_EQ(data, a_data) << "lines";

        EXPECT_EQ(util::Parser::getLinesRef(data), view(ans));
    }

    void testWords(const std::string& a_data)
    {
        std::string data = a_data;

        auto lines = slice(data, "\n");
        std::vector<std::vector<std::string>> ans(lines.size());
        for (int i = 0; i < ans.size(); ++i)
        {
            ans[i] = slice(lines[i], "\t ");
        }

        EXPECT_EQ(util::Parser::getWordsCopy(data), ans);
        EXPECT_EQ(data, a_data) << "words";

        EXPECT_EQ(util::Parser::getWordsRef(data), view(ans));
    }
};

TEST_F(UTestString, test_slice_nun)
{
    testSlice("", "", "");
}

TEST_F(UTestString, test_slice_empty_input)
{
    testSlice("", ", ", "!");
}

TEST_F(UTestString, test_slice_empty_output)
{
    testSlice(",!,,, ,,!", ", ", "!");
}

TEST_F(UTestString, test_slice_simple)
{
    testSlice("Hello, world!", ", ", "!");
}

TEST_F(UTestString, test_slice_repeated_delimiters)
{
    testSlice("!Hello!, ,world!!,,  , , !!", ", ", "!");
}

TEST_F(UTestString, test_slice_into_old_buffer)
{
    testSlice("appleA Zorange.\t.banana!grape!!pear--peach", "AZ,.- !", "\t");
}

TEST_F(UTestString, get_lines)
{
    testLines("line1\nline2\nline3");
}

TEST_F(UTestString, get_words)
{
    testWords("word1 word2\nword3 word4");
}

// TEST_F(UTestString, get_words_map)
// {
//     std::string data = "key1 value1\nkey2 value2";
//     auto wordsMap    = util::Parser::getWordsMap(data);
//     EXPECT_EQ(wordsMap.size(), 2);
//     EXPECT_EQ(wordsMap["key1"], "value1");
//     EXPECT_EQ(wordsMap["key2"], "value2");
// }

// TEST_F(UTestString, get_words_set)
// {
//     std::string data = "word1; word2 ;word3";
//     auto wordsSet    = util::Parser::getWordsSet(data, ";");
//     EXPECT_EQ(wordsSet.size(), 3);
//     EXPECT_TRUE(wordsSet.find("word1") != wordsSet.end());
//     EXPECT_TRUE(wordsSet.find(" word2 ") != wordsSet.end());
//     EXPECT_TRUE(wordsSet.find("word3") != wordsSet.end());
// }

} // namespace kustest
