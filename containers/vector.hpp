#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <iostream>
# include <memory>
# include <stdexcept>

# include "../utils/algorithm.hpp"
# include "../utils/type_traits.hpp"
# include "../iterators/vector_iterator.hpp"
# include "../iterators/reverse_iterator.hpp"

namespace ft
{
	template < class T, class Allocator = std::allocator<T> >
	class vector
	{
/* ================================================================ */
/* ======================== Member types ========================== */
/* ================================================================ */
		public:
		    typedef T											value_type;
    		typedef Allocator									allocator_type;
			typedef typename allocator_type::size_type			size_type;
			typedef typename allocator_type::difference_type	difference_type;
    		typedef typename allocator_type::reference			reference;
    		typedef typename allocator_type::const_reference	const_reference;
			typedef typename allocator_type::pointer			pointer;
			typedef typename allocator_type::const_pointer		const_pointer;
			typedef vector_iterator<pointer>					iterator;
    		typedef vector_iterator<const_pointer>				const_iterator;
			typedef reverse_iterator<const_iterator>			const_reverse_iterator;
	    	typedef reverse_iterator<iterator>					reverse_iterator;
/* ================================================================ */
/* ==================== Private attributes ======================== */
/* ================================================================ */
		private:
			pointer			_arr;
			size_type		_size;
			size_type		_capacity;
			allocator_type	_alloc;

			void			_delete(size_type cap)
			{
				for (size_type i = 0; i < _size; i++)
					_alloc.destroy(_arr + i);
				_alloc.deallocate(_arr, cap);
			}
			template <class InputIt>
				size_type		_distance(InputIt first, InputIt last)
				{
					size_type	res;

					res = 0;
					while (first != last)
					{
						res++;
						first++;
					}

					return (res);
				}
			size_type	_get_idx(iterator pos)
			{
				size_type	idx;

				idx = 0;
				for (iterator it = begin(); it < pos; it++)
					idx++;

				return (idx);
			}
/* ================================================================ */
/* ======================= Member functions ======================= */
/* ================================================================ */
		public:
			/* ================================== */
			/* ========== Constructors ========== */
			/* ================================== */
			vector(): _arr(NULL), _size(0), _capacity(0) { }
			explicit vector(const allocator_type &alloc): _arr(NULL), _size(0), _capacity(0) { _alloc = alloc; }
			explicit vector(size_type count, const_reference value = value_type(),
							const allocator_type &alloc = allocator_type()): _size(count), _capacity(count), _alloc(alloc)
			{
				_arr = _alloc.allocate(_capacity);
				for (size_type i = 0; i < count; i++)
					_alloc.construct(_arr + i, value);
			}
			template <class InputIt>
				vector(InputIt first, InputIt last, const allocator_type& alloc = Allocator(),
						typename ft::enable_if<!ft::is_integral<InputIt>::value, bool>::type = true): _alloc(alloc)
				{
					InputIt	tmp = first;

					while (tmp != last)
					{
						_size++;
						tmp++;
					}
					_capacity = _size;
					_arr = _alloc.allocate(_capacity);
					for (size_type i = 0; first != last; i++)
					{
						_alloc.construct(_arr + i, *(first));
						first++;
					}
				}
			vector(const vector& other): _arr(NULL), _size(0), _capacity(0) { *this = other; }
			/* ================================== */
			/* ========== Destructor ============ */
			/* ================================== */
			~vector()
			{
				if (_arr)
				{
					clear();
					_alloc.deallocate(_arr, _capacity);
				}
			}
			/* ====================================================== */
			/* ========== Assignation operator overloading ========== */
			/* ====================================================== */
			vector&			operator=(const vector& other)
			{
				if (_capacity)
					_delete(_capacity);
				this->_size = other._size;
				this->_capacity = other._capacity;
				this->_alloc = other._alloc;
				this->_arr = this->_alloc.allocate(this->_capacity);
				for (size_type i = 0; i < this->_size; i++)
					this->_alloc.construct(this->_arr + i, other._arr[i]);

				return (*this);
			}
			/* ==================================== */
			/* ============ Allocator ============= */
			/* ==================================== */
			allocator_type	get_allocator() const { return (_alloc); }
			/* ==================================== */
			/* ========== Element access ========== */
			/* ==================================== */
			reference		operator[](size_type pos) { return (_arr[pos]); }
			const_reference	operator[](size_type pos) const { return (_arr[pos]); }
			reference		front() { return (_arr[0]); }
			const_reference	front() const { return (_arr[0]); }
			reference		back() { return (_arr[_size - 1]); }
			const_reference	back() const { return (_arr[_size - 1]); }
			pointer			data() { return (_arr); }
			const_pointer	data() const { return (_arr); }
			reference		at(size_type pos)
			{
				if (pos >= _size)
					throw std::out_of_range("vector");
				return (_arr[pos]);
			}
			const_reference	at(size_type pos) const
			{
				if (pos >= _size)
					throw std::out_of_range("vector");
				return (_arr[pos]);
			}
			/* ============================== */
			/* ========== Capacity ========== */
			/* ============================== */
			bool		empty() const { return (_size == 0); }
			size_type	size() const { return (_size); }
			size_type	max_size() const { return (_alloc.max_size()); }
			size_type	capacity() const { return (_capacity); }
			void		reserve(size_type new_cap)
			{
				pointer	new_arr;

				if (new_cap > max_size())
					throw std::length_error("vector");
				if (new_cap <= _capacity)
					return ;
				new_arr = _alloc.allocate(new_cap);
				for (size_type i = 0; i < _size; i++)
					_alloc.construct(new_arr + i, _arr[i]);
				_delete(_capacity);
				_capacity = new_cap;
				_arr = new_arr;
			}
			void		resize(size_type count, value_type value = value_type())
			{
				pointer		new_arr;
				size_type	old_cap;

				if (count > max_size())
					throw std::length_error("vector");
				old_cap = _capacity;
				if (_capacity < count)
				{
					if (!_capacity)
						_capacity = count;
					while (_capacity < count)
						_capacity *= 2;
					new_arr = _alloc.allocate(_capacity);
					for (size_type i = 0; i < _size; i++)
						_alloc.construct(new_arr + i, _arr[i]);
					for (size_type i = _size; i < count; i++)
						_alloc.construct(new_arr + i, value);
					_delete(old_cap);
					_arr = new_arr;
				}
				else if (_size > count)
					for (int i = _size - 1; i >= (int)count; i--)
						_alloc.destroy(_arr + i);
				else
					for (size_type i = _size; i < count; i++)
						_alloc.construct(_arr + i, value);
				_size = count;
			}
			/* =============================== */
			/* ========== Modifiers ========== */
			/* =============================== */
			void	push_back(const_reference value) { resize(_size + 1, value); }
			void	pop_back()
			{
				if (!_size)
					_size -= 1;
				else	
					resize(_size - 1);
			}
			void	clear()
			{
				for (size_type i = 0; i < _size; i++)
					_alloc.destroy(_arr + i);
				_size = 0;
			}
			void	swap(vector& other)
			{
				size_type	size_tmp = _size;
				size_type	capacity_tmp = _capacity;
				pointer		arr_tmp = _arr;

				_size = other._size;
				_capacity = other._capacity;
				_arr = other._arr;
				other._size = size_tmp;
				other._capacity = capacity_tmp;
				other._arr = arr_tmp;
			}
			void	assign(size_type count, const_reference value)
			{
				resize(count, value);
				for (size_type i = 0; i < _size; i++)
				{
					_alloc.destroy(_arr + i);
					_alloc.construct(_arr + i, value);
				}
			}
			template <class InputIt>
				void	assign(InputIt first, InputIt last,
								typename ft::enable_if<!ft::is_integral<InputIt>::value, bool>::type = true)
				{
					resize(_distance(first, last));
					for (size_type i = 0; i < _size; i++)
					{
						_alloc.destroy(_arr + i);
						_alloc.construct(_arr + i, *(first));
						first++;
					}
				}
			iterator	insert(iterator pos, const_reference value)
			{
				insert(pos, 1, value);

				return (pos);
			}
			void		insert(iterator pos, size_type count, const_reference value)
			{
				size_type	dst = _distance(begin(), pos);
				iterator	old_end = end() - 1;

				resize(_size + count);
				for (iterator it = end() - 1; it >= begin() + dst + count; it--)
				{
					*it = *old_end;
					old_end--;
				}
				for (iterator it = begin() + dst; it != begin() + (dst + count); it++)
					*it = value;
			}
			template < class InputIt >
				void	insert(iterator pos, InputIt first, InputIt last,
								typename ft::enable_if<!ft::is_integral<InputIt>::value, bool>::type = true)
				{
					size_type	count = _distance(first, last);
					value_type	values[count];
					size_type	dst = _distance(begin(), pos);
					iterator	old_end = end() - 1;

					resize(_size + count);
					for (size_type i = 0; first != last; i++)
					{
						values[i] = *first;
						first++;
					}
					for (iterator it = end() - 1; it >= begin() + dst + count; it--)
					{
						*it = *old_end;
						old_end--;
					}
					for (size_type i = 0; i < count; i++)
						*(begin() + dst + i) = values[i];
				}
			iterator	erase(iterator pos)
			{
                for (size_type i = pos - this->begin(); i < this->size() - 1; ++i)
                    *(_arr + i) = *(_arr + i + 1);
                _alloc.destroy(_arr + _size - 1);
				--_size;

				return (pos);
			}
			iterator	erase(iterator first, iterator last)
			{
				size_type	first_dst = _distance(begin(), first);
				size_type	last_dst = _distance(begin(), last);
				iterator	first_end = begin() + first_dst;

				for (iterator it = begin() + last_dst; it != end(); it++)
				{
					*first_end = *it;
					first_end++;
				}
				while (last_dst != _size)
				{
					_alloc.destroy(_arr + last_dst);
					last_dst++;
				}
				_size -= _distance(first, last);

				return (first);
			}
			/* =============================== */
			/* ========== Iterator =========== */
			/* =============================== */
			iterator				begin() { return (iterator(_arr)); }
			const_iterator			begin() const { return (const_iterator(_arr)); }
			iterator				end() { return (iterator(_arr + _size)); }
			const_iterator			end() const { return (const_iterator(_arr + _size)); }
			reverse_iterator		rbegin() { return (reverse_iterator(end())); }
			const_reverse_iterator	rbegin() const { return (const_reverse_iterator(end())); }
			reverse_iterator		rend() { return (reverse_iterator(begin())); }
			const_reverse_iterator	rend() const { return (const_reverse_iterator(begin())); }
	};
/* =================================================================== */
/* ======================= Non-member functions ====================== */
/* =================================================================== */
	template< class T, class Alloc >
		bool	operator==(const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>& rhs)
		{
			if (lhs.size() != rhs.size())
				return (false);
			return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
		}
	template< class T, class Alloc >
		bool	operator!=(const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>& rhs)
		{
			return (!(lhs == rhs));
		}
	template< class T, class Alloc >
		bool	operator<(const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>& rhs)
		{
			return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
		}
	template< class T, class Alloc >
		bool	operator<=(const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>& rhs)
		{
			return (!(rhs < lhs));
		}
	template< class T, class Alloc >
		bool	operator>(const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>& rhs)
		{
			return (rhs < lhs);
		}
	template< class T, class Alloc >
		bool	operator>=(const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>& rhs)
		{
			return (!(rhs > lhs));
		}

	template <class T, class Alloc>
		void	swap(vector<T, Alloc>& x, vector<T, Alloc>& y)
		{
			x.swap(y);
		}
}

#endif // VECTOR_HPP
