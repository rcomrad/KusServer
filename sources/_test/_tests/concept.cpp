#include <concepts>
#include <string>
#include <type_traits>

#include "kernel/tester/fixture.hpp"
#include "kernel/utility/type/concepts.hpp"

namespace kustest
{

class ConceptsTest : public Fixture
{
};

//--------------------------------------------------------------------------------
// Integer concept

template <std::integral T>
std::string
to_str(T number)
{
    return std::to_string(number);
}

//--------------------------------------------------------------------------------
// SFINAE enable_if & is_same

template <typename T, std::enable_if_t<std::is_same_v<T, std::string>, int> = 0>
std::string
to_str(const T& str)
{
    return str;
}

template <typename T,
          std::enable_if_t<std::is_same_v<std::decay_t<T>, char*>, int> = 0>
std::string
to_str(const T& str)
{
    return std::string(str);
}

//--------------------------------------------------------------------------------
// SFINAE struct member access

struct Storage
{
    int a;
    double b;
    std::string str;
    using str_type = std::string;
};

template <typename T>
T::str_type
to_str(const T& storage)
{
    return storage.str;
}

//--------------------------------------------------------------------------------
// Dumb concept

template <typename T>
std::string
to_str(const T& vec)
    requires !std::integral<T> && !std::is_same_v<std::decay_t<T>, char*> &&
             !std::is_same_v<T, std::string> &&
             !std::is_same_v<T, Storage> && std::is_same_v<T, std::vector<int>>
{
    std::string result;
    for (const auto& i : vec)
    {
        result += std::to_string(i);
    }
    return result;
}

//--------------------------------------------------------------------------------
// Complex concept

template <util::Container2D T>
std::string
to_str(const T& vec)
{
    std::string result;
    for (const auto& i : vec)
    {
        result += i;
    }
    return result;
}

//--------------------------------------------------------------------------------

TEST_F(ConceptsTest, concept_smoke)
{
    EXPECT_EQ(to_str(1), "1");
    EXPECT_EQ(to_str("g"), "g");
    EXPECT_EQ(to_str(std::string("test")), "test");
    EXPECT_EQ(to_str(Storage(2, -99.99, "storage")), "storage");
    EXPECT_EQ(to_str(std::vector<int>{1, 2, 3}), "123");
    EXPECT_EQ(to_str(std::vector<std::string>{"a", "b b", "dd"}), "ab bdd");
}

} // namespace kustest
