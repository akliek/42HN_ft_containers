#ifndef ALGORITHM_HPP
# define ALGORITHM_HPP

namespace ft
{
/* ================================================================ */
/* ============================== equal =========================== */
/* ================================================================ */
	template < class InputIt1, class InputIt2>
		bool	equal(InputIt1 first1, InputIt1 last1, InputIt2 first2)
		{
			while (first1 != last1)
			{
				if (!(*first1 == *first2))
					return (false);
				first1++;
				first2++;
			}
			return (true);
		}
	template < class InputIt1, class InputIt2, class BinaryPredicate>
		bool	equal(InputIt1 first1, InputIt1 last1,
						InputIt2 first2, BinaryPredicate p)
		{
			while (first1 != last1)
			{
				if (!p(*first1, *first2))
					return (false);
				first1++;
				first2++;
			}
			return (true);			
		}
/* ================================================================ */
/* =================== lexicographical_compare ==================== */
/* ================================================================ */
	template<class InputIt1, class InputIt2>
		bool lexicographical_compare(InputIt1 first1, InputIt1 last1,
										InputIt2 first2, InputIt2 last2)
		{
			while (first1 != last1 && first2 != last2)
			{
				if (*first1 < *first2)
					return (true);
				if (*first2 < *first1)
					return (false);

				first1++;
				first2++;
			}
		    return ((first1 == last1) && (first2 != last2));
		}
	template<class InputIt1, class InputIt2, class Compare>
		bool lexicographical_compare(InputIt1 first1, InputIt1 last1,
										InputIt2 first2, InputIt2 last2, Compare comp)
		{
			while (first1 != last1 && first2 != last2)
			{
				if (comp(*first1, *first2))
					return (true);
				if (comp(*first2, *first1))
					return (false);

				first1++;
				first2++;
			}
		    return ((first1 == last1) && (first2 != last2));
		}
}

#endif // ALGORITHM_HPP
