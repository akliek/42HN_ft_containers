#ifndef RED_BLACK_TREE_ITERATOR_HPP
# define RED_BLACK_TREE_ITERATOR_HPP

# include "iterator.hpp"

namespace ft
{
	template < class Node>
	class red_black_tree_iterator: public ft::iterator<bidirectional_iterator_tag, Node>
	{
		public:
			typedef Node*								iterator_type;
			typedef Node								iterator_value;
			typedef typename iterator_value::value_type	value_type;
			typedef value_type&							reference;
			typedef value_type*							pointer;

		private:
			iterator_type	_ptr;

			iterator_type	_get_successor(iterator_type node)
			{
				iterator_type	res;

				if (!node)
					return (NULL);
				if (node->right)
				{
					res = node->right;
					while (res->left)
						res = res->left;
				}
				else
				{
					res = node->parent;
					while (res && !node->is_left)
					{
						node = res;
						res = res->parent;
					}
				}
				return(res);
			}
			iterator_type	_get_predecessor(iterator_type node)
			{
				iterator_type	res;

				if (!node)
					return (NULL);
				if (node->left)
				{
					res = node->left;
					while (res->right)
						res = res->right;
				}
				else
				{
					res = node->parent;
					while (res && node->is_left)
					{
						node = res;
						res = res->parent;
					}
				}
				return(res);
			}
		public:
			explicit red_black_tree_iterator(iterator_type ptr = NULL): _ptr(ptr) { }
			red_black_tree_iterator(const red_black_tree_iterator& other) { *this = other; }
			~red_black_tree_iterator() { }

			template<class Iter>
				red_black_tree_iterator&	operator=(const Iter& other)
				{
					if (this != other)
						_ptr = other.base();
					return (*this);
				}

			iterator_type	base()
			{
				return (_ptr);
			}
			const iterator_type	base() const
			{
				return (_ptr);
			}

			reference	operator*() const
			{
				return (_ptr->value);
			}
			pointer		operator->() const
			{
				return (&(_ptr->value));
			}

			red_black_tree_iterator&	operator++()
			{
				_ptr = _get_successor(_ptr);
				return (*this);
			}
			red_black_tree_iterator		operator++(int)
			{
				red_black_tree_iterator	tmp(*this);
				++*this;
				return (tmp);
			}
	
			red_black_tree_iterator&	operator--()
			{
				_ptr = _get_predecessor(_ptr);
				return (*this);
			}
			red_black_tree_iterator		operator--(int)
			{
				red_black_tree_iterator	tmp(*this);
				--*this;
				return (tmp);
			}

			bool	operator==(const red_black_tree_iterator &rhs)
			{
				return (_ptr == rhs._ptr);
			}
			bool	operator!=(const red_black_tree_iterator &rhs)
			{
				return (_ptr != rhs._ptr);
			}
	};
	template < class Node>
	class const_red_black_tree_iterator: public ft::iterator<bidirectional_iterator_tag, Node>
	{
		public:
			typedef Node*										iterator_type;
			typedef Node										iterator_value;
			typedef const typename iterator_value::value_type	value_type;
			typedef value_type&									reference;
			typedef value_type*									pointer;

		private:
			iterator_type	_ptr;

			iterator_type	_get_successor(iterator_type node)
			{
				iterator_type	res;

				if (!node)
					return (NULL);
				if (node->right)
				{
					res = node->right;
					while (res->left)
						res = res->left;
				}
				else
				{
					res = node->parent;
					while (res && !node->is_left)
					{
						node = res;
						res = res->parent;
					}
				}
				return(res);
			}
			iterator_type	_get_predecessor(iterator_type node)
			{
				iterator_type	res;

				if (!node)
					return (NULL);
				if (node->left)
				{
					res = node->left;
					while (res->right)
						res = res->right;
				}
				else
				{
					res = node->parent;
					while (res && node->is_left)
					{
						node = res;
						res = res->parent;
					}
				}
				return(res);
			}
		public:
			explicit const_red_black_tree_iterator(iterator_type ptr = NULL): _ptr(ptr) { }
			~const_red_black_tree_iterator() { }

			template<class Iter>
				const_red_black_tree_iterator(const Iter& other) { *this = other; }

			template<class Iter>
				const_red_black_tree_iterator&	operator=(const Iter& other)
				{
					_ptr = other.base();
					return (*this);
				}

			iterator_type	base()
			{
				return (_ptr);
			}
			const iterator_type	base() const
			{
				return (_ptr);
			}


			reference	operator*() const
			{
				return (_ptr->value);
			}
			pointer		operator->() const
			{
				return (&(_ptr->value));
			}

			const_red_black_tree_iterator&	operator++()
			{
				_ptr = _get_successor(_ptr);
				return (*this);
			}
			const_red_black_tree_iterator	operator++(int)
			{
				const_red_black_tree_iterator	tmp(*this);
				++*this;
				return (tmp);
			}
	
			const_red_black_tree_iterator&	operator--()
			{
				_ptr = _get_predecessor(_ptr);
				return (*this);
			}
			const_red_black_tree_iterator	operator--(int)
			{
				const_red_black_tree_iterator	tmp(*this);
				--*this;
				return (tmp);
			}

			bool	operator==(const const_red_black_tree_iterator &rhs)
			{
				return (_ptr == rhs._ptr);
			}
			bool	operator!=(const const_red_black_tree_iterator &rhs)
			{
				return (_ptr != rhs._ptr);
			}
	};
}

#endif // RED_BLACK_TREE_ITERATOR_HPP
