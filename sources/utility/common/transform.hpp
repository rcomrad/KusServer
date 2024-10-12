#pragma once

//--------------------------------------------------------------------------------

#include <algorithm>
#include <iterator>
#include <type_traits>

//--------------------------------------------------------------------------------

namespace util
{

#define INTERNAL_TYPE_DECLARING                                            \
    using FromCellType = std::remove_cvref_t<decltype(*std::begin(from))>; \
    using ToCellType   = std::remove_cvref_t<decltype(*std::begin(to))>;

class Transform
{
public:
    Transform() = delete;

    template <typename FromContainer, typename ToContainer>
    static void container(const FromContainer& from, ToContainer& to)
    {
        INTERNAL_TYPE_DECLARING
        std::copy(std::cbegin(from), std::cend(from), back_inserter(to));
    }

    template <typename FromContainer, typename ToContainer>
    static void container(const FromContainer& from,
                          ToContainer& to,
                          int offset)
    {
        INTERNAL_TYPE_DECLARING
        std::transform(std::cbegin(from), std::cend(from), back_inserter(to),
                       [offset](const FromCellType& c)
                       { return static_cast<ToCellType>(c) - offset; });
    }

    template <typename FromContainer>
    static std::vector<int> toNumVector(const FromContainer& from, int offset)
    {
        std::vector<int> result;
        container(from, result, offset);
        return result;
    }
};

#undef INTERNAL_TYPE_DECLARING

} // namespace util

//--------------------------------------------------------------------------------
