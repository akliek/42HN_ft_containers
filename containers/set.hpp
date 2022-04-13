#ifndef SET_HPP
# define SET_HPP

# include <iostream>
# include <memory>
# include <stdexcept>

# include "../utils/less.hpp"
# include "../utils/utility.hpp"
# include "../utils/algorithm.hpp"
# include "../utils/type_traits.hpp"
# include "../utils/red_black_tree.hpp"
# include "../iterators/reverse_iterator.hpp"
# include "../iterators/red_black_tree_iterator.hpp"

namespace ft {
	template < class T, class Compare = std::less<T>, class Allocator = std::allocator<T> >
	class set {
		public:
			typedef T												key_type;
			typedef T												value_type;
			typedef Compare											key_compare;
            typedef Compare											value_compare;
			typedef Allocator										allocator_type;
			typedef typename allocator_type::reference				reference;
			typedef typename allocator_type::const_reference		const_reference;
			typedef typename allocator_type::pointer				pointer;
			typedef typename allocator_type::const_pointer			const_pointer;
			typedef typename allocator_type::size_type				size_type;
			typedef typename allocator_type::difference_type		difference_type;

			typedef typename Allocator::template rebind<Node<value_type> >::other	node_allocator;

			class value_cmp: public std::binary_function <value_type, value_type, bool>
			{
				private:
					friend class set;
				protected:
					key_compare comp;
					value_cmp (key_compare c) : comp(c) {}
				public:
					bool operator() (const value_type& x, const value_type& y) const { return comp(x, y); }
			};

			typedef red_black_tree<T, value_type, value_cmp>		tree;
			typedef Node<value_type>*								node_ptr;
			typedef Node<value_type>								node;

			typedef ft::const_red_black_tree_iterator<Node<value_type> >	iterator;
			typedef ft::const_red_black_tree_iterator<Node<value_type> >	const_iterator;
			typedef ft::reverse_iterator<iterator>							reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>					const_reverse_iterator;

		private:
			tree			_tree;
			key_compare		_cmp;
			allocator_type	_alloc;
			node_allocator	_max_size_alloc;
		public:
			explicit set(const Compare& cmp = Compare(), const Allocator& alloc = Allocator()): _tree(tree(value_compare(key_compare()))), _cmp(cmp), _alloc(alloc) { }
			template <class Iter>
				set(Iter first, Iter last, const key_compare& cmp = key_compare(), const allocator_type& alloc = allocator_type()): _tree(tree(value_compare(key_compare()))), _cmp(cmp), _alloc(alloc)
				{
					while (first != last)
					{
						_tree.insert(*first);
						first++;
					}
				}
			set(const set& other): _tree(tree(value_compare(key_compare()))) { *this = other; }

			~set() { }

			set&	operator=(const set& other)
			{
				if (*this != other)
				{
					this->_cmp = other._cmp;
					this->_alloc = other._alloc;
					this->_tree = other._tree;
				}

				return (*this);
			}

			/* =============================== */
			/* ========== Allocator ========== */
			/* =============================== */
			allocator_type	get_allocator() const { return (_alloc); }
			/* ============================== */
			/* ========== Capacity ========== */
			/* ============================== */
			bool		empty() const { return (_tree.size() == 0); }
			size_type	size() const { return (_tree.size()); }
			size_type	max_size() const { return (_max_size_alloc.max_size()); };
			/* =============================== */
			/* ========== Modifiers ========== */
			/* =============================== */
			ft::pair<iterator, bool>	insert(const value_type& value)
			{
				ft::pair<node_ptr, bool> new_elem = _tree.insert(value);
				return (ft::make_pair(iterator(new_elem.first), new_elem.second));
			}
			iterator					insert(iterator pos, const value_type& value)
			{
				(void)pos;
				ft::pair<node_ptr, bool> new_elem = _tree.insert(value);
				return (iterator(new_elem.first));
			}
			template <class Iter>
				void					insert(Iter first, Iter last)
				{
					while (first != last)
					{
						_tree.insert(*first);
						first++;
					}
				}
			void						erase(iterator pos) { _tree.erase(*pos); }
			void						erase(iterator first, iterator last)
			{
				while (first != last)
				{
					iterator	to_delete = first++;
					erase(to_delete);
				}
			}
			size_type					erase(const key_type& key)
			{
				size_type	old_size;

				old_size = _tree.size();
				_tree.erase(key);
				return (old_size - _tree.size());
			}
			void						swap(set& other)
			{
				_tree.swap(other._tree);
			}
			void						clear() { _tree.clear(); }
			/* =============================== */
			/* ========== Observers ========== */
			/* =============================== */	
			key_compare		key_comp() const { return (Compare()); }
			value_compare	value_comp() const { return (value_compare(key_comp())); }
			/* ================================ */
			/* ========== Operations ========== */
			/* ================================ */
			iterator		find(const key_type& key) { return (iterator(_tree.find(key))); }
			const_iterator	find(const key_type& key) const { return (iterator(_tree.find(key))); }
			size_type		count(const key_type& key) const
			{
				if (_tree.exist(key))
					return (1);
				return (0);
			}
			iterator		lower_bound(const key_type& key)
			{
				iterator it;

				it = begin();
				while (it != end() && *it < key)
					it++;
				return (it);
			}
			const_iterator	lower_bound(const key_type& key) const
			{
				const_iterator	it;

				it = begin();
				while (it != end() && *it < key)
					it++;
				return (it);
			}
			iterator		upper_bound(const key_type& key)
			{
				iterator it;

				it = begin();
				while (it != end() && *it <= key)
					it++;
				return (it);
			}
			const_iterator	upper_bound(const key_type& key) const
			{
				const_iterator	it;

				it = begin();
				while (it != end() && *it <= key)
					it++;
				return (it);
			}
			ft::pair<iterator, iterator>				equal_range(const key_type& key)
			{
				return (ft::make_pair<iterator, iterator>(lower_bound(key), upper_bound(key)));
			}
			ft::pair<const_iterator, const_iterator>	equal_range(const key_type& key) const
			{
				return (ft::make_pair<const_iterator, const_iterator>(lower_bound(key), upper_bound(key)));
			}
			/* ================================ */
			/* ========== Iterators =========== */
			/* ================================ */
			iterator				begin() { return (iterator(_tree.get_lowest())); }
			const_iterator			begin() const { return (const_iterator(_tree.get_lowest())); }
			iterator				end() { return (iterator(_tree.get_end())); }
			const_iterator			end() const { return (const_iterator(_tree.get_end())); }
			reverse_iterator		rbegin() { return (reverse_iterator(end())); }
			const_reverse_iterator	rbegin() const { return (const_reverse_iterator(end())); }
			reverse_iterator		rend() { return (reverse_iterator(begin())); }
			const_reverse_iterator	rend() const { return (const_reverse_iterator(begin())); }
	};
	template <typename T, typename Compare>
		void swap(set<T, Compare>& x, set<T, Compare>& y)
		{
			x.swap(y);
		}
	template <class T, class Compare, class Alloc>
		bool operator== (const set<T, Compare, Alloc>& lhs, const set<T, Compare, Alloc>& rhs)
		{
			if (lhs.size() != rhs.size())
				return (false);
			return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
		}
	template <class T, class Compare, class Alloc>
		bool operator!= (const set<T, Compare, Alloc>& lhs, const set<T, Compare, Alloc>& rhs)
		{
			return (!(lhs == rhs));
		}
	template <class T, class Compare, class Alloc>
		bool operator<  (const set<T, Compare, Alloc>& lhs, const set<T, Compare, Alloc>& rhs)
		{
			return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
		}
	template <class T, class Compare, class Alloc>
		bool operator<= (const set<T, Compare, Alloc>& lhs, const set<T, Compare, Alloc>& rhs)
		{
			return !(rhs < lhs);
		}
	template <class T, class Compare, class Alloc>
		bool operator>  (const set<T, Compare, Alloc>& lhs, const set<T, Compare, Alloc>& rhs)
		{
			return (rhs < lhs);
		}
	template <class T, class Compare, class Alloc>
		bool operator>= (const set<T, Compare, Alloc>& lhs, const set<T, Compare, Alloc>& rhs)
		{
			return (!(lhs < rhs));
		}
}

#endif // SET_HPP
