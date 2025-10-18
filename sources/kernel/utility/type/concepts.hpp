#include <concepts>

namespace util
{

template <typename T>
concept Container = requires(T t) {
    { *t.begin() };
};

template <typename T>
concept Container2D = requires(T t) {
    { *t.begin()->begin() };
};

template <typename T>
concept MapedContainer = requires(T t) {
    { t.begin()->second };
};

template <typename T>
concept IsStdString = std::same_as<T, std::string>;

template <typename T>
concept IsNotStdString = !std::same_as<T, std::string>; 

} // namespace util
