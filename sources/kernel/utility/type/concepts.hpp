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

} // namespace util
