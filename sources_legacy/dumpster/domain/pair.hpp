#ifndef DOM_PAIR_HPP
#define DOM_PAIR_HPP

namespace dom
{
	template<typename T1, typename T2 = T1>
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
			T1 key;
			T2 value;
		};
		struct
		{
			T1 first;
			T2 second;
		};

		Pair()
		{
				int yy = 0;
				++yy;

		}
		Pair(const Pair& other)
		{
			i = other.i;
			j = other.j;
		}

		Pair(T1&& iInit, T2&& jInit) :
			i(iInit),
			j(jInit)
		{}

		Pair(const T1& iInit, const T2& jInit) :
			i(iInit),
			j(jInit)
		{}

		~Pair(){}

		void operator+= (const Pair& n)
		{
			i += n.i;
			j += n.j;
		}
		void operator-= (const Pair& n)
		{
			i -= n.i;
			j -= n.j;
		}

		Pair operator+ (const Pair& n) const
		{
			Pair ret;
			ret.i = i + n.i;
			ret.j = j + n.j;
			return ret;
		}
		Pair operator- (const Pair& n) const
		{
			Pair ret;
			ret.i = i - n.i;
			ret.j = j - n.j;
			return ret;
		}

		bool operator< (const Pair& n) const
		{
			if (i != n.i) return i < n.i;
			return j < n.j;
		}
		bool operator>(const Pair& n) const
		{
			if (i != n.i) return i > n.i;
			return j > n.j;
		}
		bool operator== (const Pair& n) const
		{
			return i == n.i && j == n.j;
		}
		bool operator!= (const Pair& n) const
		{
			return i != n.i || j != n.j;
		}

		Pair& operator=(const Pair& other)
		{
			j = other.j;
			i = other.i;

			return *this;
		}
	};
}

#endif // !DOM_PAIR_HPP