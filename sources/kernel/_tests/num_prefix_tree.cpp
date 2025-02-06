// #include "kernel/utility/datastructs/num_prefix_tree.hpp"

// #include <algorithm>
// #include <ranges>
// #include <string>
// #include <vector>

// #include "kernel/tester/fixture.hpp"
// #include "kernel/utility/common/transform.hpp"

// namespace kustest
// {

// class NumPrefixTreeTest : public Fixture
// {
// };

// #define DEBUG_TEST_DATA(container) \
//     "i = " << i << ", word: '" << container[i] << "'"

// TEST_F(NumPrefixTreeTest, smoke)
// {
//     std::vector<std::string> correst{"aaaa", "aaa",          "a",   "ab",
//                                      "ac",   "aba",          "abb", "baa",
//                                      "z",    "fdsdfsdfsgers"};

//     util::NumPrefixTree<std::string, 'a', 'z'> tree;
//     for (int i = 0; i < correst.size(); ++i)
//     {
//         tree.set(correst[i], correst[i]);
//     }

//     tree.set("y", "y");
//     tree.set({'u'}, "u");
//     correst.emplace_back("y");
//     correst.emplace_back("u");

//     for (int i = 0; i < correst.size(); ++i)
//     {
//         auto data = tree.get(correst[i]);
//         EXPECT_TRUE(data) << DEBUG_TEST_DATA(correst);
//         EXPECT_EQ(data, correst[i]) << DEBUG_TEST_DATA(correst);
//     }

//     std::vector<std::string> corrupted{
//         "aa",  "aaz", "b",     "ba", "ca",
//         "bab", "",    "aaaaa", "i",  "dsfgdsfgdfghdrdhrhdr"};

//     for (int i = 0; i < corrupted.size(); ++i)
//     {
//         EXPECT_THROW(tree.get(corrupted[i]), std::runtime_error)
//             << DEBUG_TEST_DATA(corrupted);
//     }
// }

// } // namespace kustest
