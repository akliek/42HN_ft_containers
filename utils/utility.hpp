#ifndef UTILITY_HPP
# define UTILITY_HPP

namespace ft
{
/* ==================== pair_struct ==================== */

	template <class T1, class T2>
		struct pair
		{
			typedef T1	first_type;
			typedef T2	second_type;

			T1	first;
			T2	second;

			pair(): first(), second() { }
			pair(const T1& a, const T2& b): first(a), second(b) { }
			template <class U, class V>
				pair(const pair<U, V>& pr): first(pr.first), second(pr.second) { }

			pair&	operator=(const pair& other)
			{
				this->first = other.first;
				this->second = other.second;

				return (*this);
			}
		};

/* ==================== pair_operators ==================== */

	template<class T1, class T2>
		bool operator==(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
		{
			return ((lhs.first == rhs.first) && (lhs.second == rhs.second));
		}
	template<class T1, class T2>
		bool operator!=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
		{
			return (!(lhs == rhs));
		}
	template<class T1, class T2>
		bool operator<(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
		{
			return ((lhs.first < rhs.first) || (!(lhs.first < rhs.first) && (lhs.second < rhs.second)));
		}
	template<class T1, class T2>
		bool operator>(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
		{
			return (rhs < lhs);
		}
	template<class T1, class T2>
		bool operator<=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
		{
			return (!(rhs < lhs));
		}
	template<class T1, class T2>
		bool operator>=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
		{
			return (!(lhs < rhs));
		}

/* ==================== make_pair ==================== */

	template<class T1, class T2>
		pair<T1, T2>	make_pair(T1 t, T2 u)
		{
			return (pair<T1, T2>(t, u));
		}
}

#endif // UTILITY_HPP
