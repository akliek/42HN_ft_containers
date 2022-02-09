#ifndef REVERSE_ITERATOR_HPP
# define REVERSE_ITERATOR_HPP

# include "iterator.hpp"
# include <iterator>

namespace ft
{
	template <class Iter>
	class reverse_iterator
		: public iterator < typename iterator_traits<Iter>::iterator_category,
							typename iterator_traits<Iter>::value_type,
							typename iterator_traits<Iter>::difference_type,
							typename iterator_traits<Iter>::pointer,
							typename iterator_traits<Iter>::reference >
	{
		/* ========== Member types ========== */
		public:
			typedef Iter															iterator_type;
			typedef typename ft::iterator_traits<iterator_type>::reference			reference;
			typedef typename ft::iterator_traits<iterator_type>::pointer			pointer;
			typedef typename ft::iterator_traits<iterator_type>::difference_type	difference_type;
		protected:
			iterator_type	_current;
		/* ========== Member functions ========== */
		public:
			/* ========== Constructors ========== */
			reverse_iterator(): _current() {}
			explicit reverse_iterator(iterator_type it): _current(it) {}
			template <class It>
				reverse_iterator(const reverse_iterator<It>& other) { *this = other; }

			/* ========== Destructor ========== */
			~reverse_iterator() {}

			/* ========== Assignation operator overloading ========== */
			template <class It>
				reverse_iterator&	operator=(const reverse_iterator<It>& other)
				{
					_current = other.base();

					return (*this);
				} 

			iterator_type		base() const { return (_current); }
			pointer				operator->() const { return (&(this->operator*())); }
			reference			operator*() const
			{
				iterator_type	tmp = _current;

				return (*--tmp);
			}
			reference			operator[](difference_type n) const { return *(*this + n); }
			reverse_iterator&	operator++()
			{
				--_current;

				return (*this);
			}
			reverse_iterator	operator++(int)
			{
				reverse_iterator	tmp(*this);

				--_current;

				return (tmp);
			}
			reverse_iterator&	operator--()
			{
				++_current;

				return (*this);
			}
			reverse_iterator	operator--(int)
			{
				reverse_iterator	tmp(*this);

				++_current;

				return (tmp);
			}
			reverse_iterator	operator+(difference_type n) const { return (reverse_iterator(_current - n)); }
			reverse_iterator	operator-(difference_type n) const { return (reverse_iterator(_current + n)); }
			reverse_iterator&	operator+=(difference_type n)
			{
				_current -= n;

				return (*this);
			}
			reverse_iterator&	operator-=(difference_type n)
			{
				_current += n;

				return (*this);
			}
	};
	/* ========== Non-member functions ========== */
	template <class iter1, class iter2>
		typename ft::reverse_iterator<iter1>::difference_type
		operator-(const ft::reverse_iterator<iter1>& lhs, const ft::reverse_iterator<iter2>& rhs)
		{
			return (rhs.base() - lhs.base());
		}
	template <class iter>
		ft::reverse_iterator<iter> operator+(typename ft::reverse_iterator<iter>::difference_type n,
												const ft::reverse_iterator<iter>& x)
		{
			return (ft::reverse_iterator<iter>(x.base() - n));
		}
	template <class iter1, class iter2>
		bool operator==(const ft::reverse_iterator<iter1>& lhs, const ft::reverse_iterator<iter2>& rhs)
		{
			return (lhs.base() == rhs.base());
		}
	template <class iter1, class iter2>
		bool operator!=(const ft::reverse_iterator<iter1>& lhs, const ft::reverse_iterator<iter2>& rhs)
		{
			return (lhs.base() != rhs.base());
		}
	template <class iter1, class iter2>
		bool operator<(const ft::reverse_iterator<iter1>& lhs, const ft::reverse_iterator<iter2>& rhs)
		{
			return (lhs.base() > rhs.base());
		}
	template <class iter1, class iter2>
		bool operator>(const ft::reverse_iterator<iter1>& lhs, const ft::reverse_iterator<iter2>& rhs)
		{
			return (lhs.base() < rhs.base());
		}
	template <class iter1, class iter2>
		bool operator>=(const ft::reverse_iterator<iter1>& lhs, const ft::reverse_iterator<iter2>& rhs)
		{
			return (lhs.base() <= rhs.base());
		}
	template <class iter1, class iter2>
		bool operator<=(const ft::reverse_iterator<iter1>& lhs, const ft::reverse_iterator<iter2>& rhs)
		{
			return (lhs.base() >= rhs.base());
		}
}

#endif // REVERSE_ITERATOR_HPP
