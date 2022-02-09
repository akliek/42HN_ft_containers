#ifndef VECTOR_ITERATOR_HPP
# define VECTOR_ITERATOR_HPP

# include "iterator.hpp"

namespace ft
{
	template < class Iter >
	class vector_iterator
	{
		/* ========== Member types ========== */
		public:
			typedef Iter															iterator_type;
			typedef typename ft::iterator_traits<iterator_type>::value_type			value_type;
			typedef typename ft::iterator_traits<iterator_type>::reference			reference;
			typedef typename ft::iterator_traits<iterator_type>::pointer			pointer;
			typedef typename ft::iterator_traits<iterator_type>::difference_type	difference_type;
			typedef	typename ft::iterator_traits<iterator_type>::iterator_category	iterator_category;
		private:
			iterator_type	_ptr;
		/* ========== Member functions ========== */
		public:
			/* ========== Constructors ========== */
			vector_iterator(): _ptr(NULL) {}
			vector_iterator(pointer ptr): _ptr(ptr) { }
			template <class It>
				vector_iterator(const vector_iterator<It>& other) { *this = other; }

			/* ========== Destructor ========== */
			~vector_iterator() {};

			/* ========== Assignation operator overloading ========== */
			template <class It>
				vector_iterator&	operator=(const vector_iterator<It>& other)
				{
					this->_ptr = other.base();

					return (*this);
				}

			pointer				base() const { return (_ptr); }
			pointer				operator->() const { return (_ptr); }
			reference			operator*() const { return (*_ptr); }
			reference			operator[](difference_type n) const { return (*(_ptr + n)); }
			vector_iterator&	operator++()
			{
				_ptr++;

				return (*this);
			}
			vector_iterator		operator++(int)
			{
				vector_iterator	tmp = *this;

				++(*this);

				return (tmp);
			}
			vector_iterator&	operator--()
			{
				_ptr--;

				return (*this);
			}
			vector_iterator		operator--(int)
			{
				vector_iterator	tmp = *this;

				--(*this);

				return (tmp);
			}
			vector_iterator		operator+(difference_type n) { return (vector_iterator(_ptr + n)); }
			vector_iterator		operator+(difference_type n) const { return (vector_iterator(_ptr + n)); }
			vector_iterator&	operator+=(difference_type n)
			{
				_ptr += n;

				return (*this);
			}
			vector_iterator		operator-(difference_type n) { return (vector_iterator(_ptr - n)); }
			vector_iterator		operator-(difference_type n) const { return (vector_iterator(_ptr - n)); }
			vector_iterator&	operator-=(difference_type n)
			{
				_ptr -= n;

				return (*this);
			}
	};
	/* ========== Non-member functions ========== */

	template <class iter1, class iter2>
		typename ft::vector_iterator<iter1>::difference_type
		operator-(const ft::vector_iterator<iter1>& lhs, const ft::vector_iterator<iter2>& rhs)
		{
			return (lhs.base() - rhs.base());
		}
	template <class iter1, class iter2>
		typename ft::vector_iterator<iter1>::difference_type
		operator+(const ft::vector_iterator<iter1>& lhs, const ft::vector_iterator<iter2>& rhs)
		{
			return (lhs.base() + rhs.base());
		}
	template<class iter>
		ft::vector_iterator<iter> operator+(typename ft::vector_iterator<iter>::difference_type n,
											ft::vector_iterator<iter> x)
		{
			x += n;

			return (x);
		}
	template <class iter1, class iter2>
		bool operator==(const ft::vector_iterator<iter1>& lhs, const ft::vector_iterator<iter2>& rhs)
		{
			return (lhs.base() == rhs.base());
		}
	template <class iter1, class iter2>
		bool operator!=(const ft::vector_iterator<iter1>& lhs, const ft::vector_iterator<iter2>& rhs)
		{
			return (lhs.base() != rhs.base());
		}
	template <class iter1, class iter2>
		bool operator<(const ft::vector_iterator<iter1>& lhs, const ft::vector_iterator<iter2>& rhs)
		{
			return (lhs.base() < rhs.base());
		}
	template <class iter1, class iter2>
		bool operator>(const ft::vector_iterator<iter1>& lhs, const ft::vector_iterator<iter2>& rhs)
		{
			return (lhs.base() > rhs.base());
		}
	template <class iter1, class iter2>
		bool operator>=(const ft::vector_iterator<iter1>& lhs, const ft::vector_iterator<iter2>& rhs)
		{
			return (lhs.base() >= rhs.base());
		}
	template <class iter1, class iter2>
		bool operator<=(const ft::vector_iterator<iter1>& lhs, const ft::vector_iterator<iter2>& rhs)
		{
			return (lhs.base() <= rhs.base());
		}
}

#endif // VECTOR_ITERATOR_HPP
