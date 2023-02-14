#ifndef DOM_PAIR_HPP
#define DOM_PAIR_HPP

//--------------------------------------------------------------------------------

#include "metaprogramming.hpp"

//--------------------------------------------------------------------------------

namespace dom
{
template <typename T1, typename T2 = T1> union Pair
{
    struct
    {
        T1 i;
        T2 j;
    };
    struct
    {
        T1 x;
        T2 y;
    };
    struct
    {
        T1 key;
        T2 value;
    };
    struct
    {
        T1 first;
        T2 second;
    };

    //--------------------------------------------------------------------------------

    Pair() noexcept : x(), y()
    {
    }

    template <typename Arg, typename = enableIfSame<Pair<T1, T2>, Arg>>
    Pair(Arg&& other) noexcept
        : x(std::forward<T1>(other.x)), y(std::forward<T2>(other.y))
    {
    }

    template <typename Arg1, typename Arg2>
    Pair(Arg1&& xInit, Arg2&& yInit) noexcept
        : x(std::forward<T1>(xInit)), y(std::forward<T2>(yInit))
    {
    }

    ~Pair() = default;

    //--------------------------------------------------------------------------------

    void operator+=(const Pair& other) noexcept
    {
        x += other.x;
        y += other.y;
    }
    void operator-=(const Pair& other) noexcept
    {
        x -= other.x;
        y -= other.y;
    }

    //--------------------------------------------------------------------------------

    template <typename Arg, typename = enableIfSame<Pair<T1, T2>, Arg>>
    Pair& operator=(Arg&& other) noexcept
    {
        x = std::forward<T1>(other.x);
        y = std::forward<T2>(other.y);
        return *this;
    }

    //--------------------------------------------------------------------------------

    template <typename Arg, typename = enableIfSame<Pair<T1, T2>, Arg>>
    friend Pair operator+(Pair&& a1, Arg&& a2) noexcept
    {
        a1.x += a2.x;
        a1.y += a2.y;
        return std::move(a1);
    }

// TODO: Linux can't handle this code for some
//      unknown reason
#ifndef LINUS_LINUX
    friend Pair operator+(const Pair& a1, Pair&& a2) noexcept
    {
        return std::move(a2) + a1;
    }

    friend Pair operator+(const Pair& a1, const Pair& a2) noexcept
    {
        return Pair<T1, T2>{a1.x + a2.x, a1.y + a2.y};
    }
#endif

    //--------------------------------------------------------------------------------

    template <typename Arg, typename = enableIfSame<Pair<T1, T2>, Arg>>
    friend Pair operator-(Pair&& a1, Arg&& a2) noexcept
    {
        a1.x -= a2.x;
        a1.y -= a2.y;
        return std::move(a1);
    }
    template <typename Arg, typename = enableIfSame<Pair<T1, T2>, Arg>>
    friend Pair operator-(const Pair& a1, Arg&& a2) noexcept
    {
        return Pair<T1, T2>{a1.x - a2.x, a1.y - a2.y};
    }

    //--------------------------------------------------------------------------------

    bool operator<(const Pair& other) const noexcept
    {
        if (x != other.x) return y < other.y;
        return y < other.y;
    }
    bool operator>(const Pair& other) const noexcept
    {
        if (x != other.x) return y > other.y;
        return y > other.y;
    }
    bool operator==(const Pair& other) const noexcept
    {
        return x == other.x && y == other.y;
    }
    bool operator!=(const Pair& other) const noexcept
    {
        return x != other.x || y != other.y;
    }

    //--------------------------------------------------------------------------------

private:
    class PairBracketAccessResult
    {
        friend Pair;

    public:
        operator T1&() noexcept
        {
#ifdef _DBG_
            if (mIndex != 0) exit(-1);
#endif

            return mRes.x;
        }

        operator T2&() noexcept
        {
#ifdef _DBG_
            if (mIndex != 1) exit(-1);
#endif

            return mRes.y;
        }

        //--------------------------------------------------------------------------------

    private:
        Pair& mRes;
        uint8_t mIndex;

        PairBracketAccessResult(Pair& aRes, uint8_t aIndex) noexcept
            : mRes(aRes), mIndex(aIndex)
        {
        }
    };

    //--------------------------------------------------------------------------------

public:
    PairBracketAccessResult operator[](uint8_t aIndex) noexcept
    {
        return PairBracketAccessResult(*this, aIndex);
    }
};
} // namespace dom

//--------------------------------------------------------------------------------

#endif // !DOM_PAIR_HPP
