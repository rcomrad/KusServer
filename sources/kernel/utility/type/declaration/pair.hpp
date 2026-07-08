#pragma once

namespace core
{
template <typename T1, typename T2 = T1>
union Pair
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
        T1 width;
        T2 height;
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

    Pair() = default;

    Pair(T1&& iInit, T2&& jInit) : i(iInit), j(jInit)
    {
    }

    Pair(const T1& iInit, const T2& jInit) : i(iInit), j(jInit)
    {
    }

    template <typename T3, typename T4>
    Pair& assign(const Pair<T3, T4>& n)
    {
        i = n.i;
        j = n.j;
        return *this;
    }

    // ******************************************************

    template <typename T3, typename T4>
    Pair& operator+=(const Pair<T3, T4>& n)
    {
        i += n.i;
        j += n.j;
        return *this;
    }
    template <typename T3, typename T4>
    Pair& operator-=(const Pair<T3, T4>& n)
    {
        i -= n.i;
        j -= n.j;
        return *this;
    }

    template <typename T3, typename T4>
    Pair operator+(const Pair<T3, T4>& n) const
    {
        return Pair(i + n.i, j + n.j);
    }
    template <typename T3, typename T4>
    Pair operator-(const Pair<T3, T4>& n) const
    {
        return Pair(i - n.i, j - n.j);
    }

    // ******************************************************

    template <typename NumT>
    Pair& operator+=(const NumT n)
    {
        i += n;
        j += n;
        return *this;
    }
    template <typename NumT>
    Pair& operator-=(const NumT n)
    {
        i -= n;
        j -= n;
        return *this;
    }

    template <typename NumT>
    Pair operator+(const NumT n) const
    {
        return Pair(i + n, j + n);
    }
    template <typename NumT>
    Pair operator-(const NumT n) const
    {
        return Pair(i - n, j - n);
    }

    // ******************************************************

    template <typename T3, typename T4>
    Pair& operator*=(const Pair<T3, T4>& n)
    {
        i *= n.i;
        j *= n.j;
        return *this;
    }
    template <typename T3, typename T4>
    Pair& operator/=(const Pair<T3, T4>& n)
    {
        i /= n.i;
        j /= n.j;
        return *this;
    }

    template <typename T3, typename T4>
    Pair operator*(const Pair<T3, T4>& n) const
    {
        return Pair(i * n.i, j * n.j);
    }
    template <typename T3, typename T4>
    Pair<float> operator/(const Pair<T3, T4>& n) const
    {
        return Pair<float>(static_cast<float>(i) / n.i,
                           static_cast<float>(j) / n.j);
    }

    // ******************************************************

    template <typename NumT>
    Pair& operator*=(const NumT n)
    {
        i *= n;
        j *= n;
        return *this;
    }
    template <typename NumT>
    Pair& operator/=(const NumT n)
    {
        i /= n;
        j /= n;
        return *this;
    }

    template <typename NumT>
    Pair operator*(const NumT n) const
    {
        return Pair(i * n, j * n);
    }
    template <typename NumT>
    Pair<float> operator/(const NumT n) const
    {
        return Pair<float>(static_cast<float>(i) / n,
                           static_cast<float>(j) / n);
    }

    // ******************************************************

    bool operator<(const Pair& n) const
    {
        if (i != n.i) return i < n.i;
        return j < n.j;
    }
    bool operator>(const Pair& n) const
    {
        if (i != n.i) return i > n.i;
        return j > n.j;
    }
    bool operator==(const Pair& n) const
    {
        return i == n.i && j == n.j;
    }
    bool operator!=(const Pair& n) const
    {
        return i != n.i || j != n.j;
    }

    bool inside(const Pair& n)
    {
        return i > n.i && j > n.j;
    }
};
} // namespace core
