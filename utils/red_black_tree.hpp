#ifndef RED_BLACK_TREE
# define RED_BLACK_TREE

# include <memory>
# include <iostream>
# include "utility.hpp"
# include "../iterators/reverse_iterator.hpp"
# include "../iterators/red_black_tree_iterator.hpp"

# define RED 1
# define BLACK 0

namespace ft {
	template <class T>
	class Node
	{
		public:
			typedef T		value_type;
			typedef Node*	node_ptr;

			bool			is_left;
			bool			color;
			value_type		value;
			node_ptr		parent;
			node_ptr		left;
			node_ptr		right;

			Node(void): is_left(0), color(BLACK), parent(NULL), left(NULL), right(NULL) { }
			Node(const value_type &value): is_left(0), color(RED), value(value), parent(NULL), left(NULL), right(NULL) { }
			Node(const Node& other): is_left(other.is_left), color(other.color), value(other.value), parent(other.parent), left(other.left), right(other.right) { }
			~Node() { }

			Node&	operator=(const Node& other)
			{
				value = other.value;
				parent = other.parent;
				right = other.right;
				left = other.left;
				color = other.color;
				is_left = other.is_left;

				return (*this);
			}

			node_ptr	get_aunt()
			{
				if (parent == NULL)
					return (NULL);
				else if (parent->is_left)
					return (parent->parent->right);
				else
					return (parent->parent->left);
			}
	};

	template <class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<Node<T> > >
	class red_black_tree
	{
		public:
			typedef	Node<T>													node;
			typedef node*													node_ptr;
			typedef T														value_type;
			typedef Allocator												allocator_type;
			typedef Compare													key_compare;
			typedef key_compare												value_compare;
			typedef typename allocator_type::reference						reference;
			typedef typename allocator_type::const_reference				const_reference;
			typedef typename allocator_type::pointer						pointer;
			typedef typename allocator_type::const_pointer					const_pointer;
			typedef typename allocator_type::size_type						size_type;
			typedef typename allocator_type::difference_type				difference_type;

		private:
			node_ptr		_end;
			node_ptr		_root;
			size_type		_size;
			key_compare		_cmp;
			allocator_type	_alloc;

		public:
			explicit red_black_tree(const key_compare& cmp, const allocator_type& alloc = allocator_type()): _root(NULL), _size(0), _cmp(cmp), _alloc(alloc)
			{
				_end = _create_node(value_type());
				_end->left = NULL;
				_end->right = NULL;
				_end->parent = NULL;
				_end->is_left = 0;
				_end->color = 0;
			}
			red_black_tree(const red_black_tree& other): _end(NULL), _root(NULL), _cmp(other._cmp), _alloc(other._alloc) { *this = other; }

			red_black_tree&	operator=(const red_black_tree& other)
			{
				clear();
				this->_cmp = other._cmp;
				this->_alloc = other._alloc;
				_cut_end_connections();
				_copy(other._root, other._end);

				return (*this);
			}

			~red_black_tree()
			{
				clear();
				_alloc.destroy(_end);
				_alloc.deallocate(_end, 1);
				_end = NULL;				
			}

			size_type	size() const
			{
				return (_size);
			}

			node_ptr	get_end() const { return(_end); }

			void		clear()
			{
				_cut_end_connections();
				_clear(_root);
				_size = 0;
				_root = NULL;
			}

			node_ptr	find(value_type key) const
			{
				node_ptr	node;

				node = _find(_root, key);
				if (!node)
					return (_end);
				return(node);
			}
			node_ptr	exist(value_type key) const
			{
				node_ptr	node;

				node = _find(_root, key);
				return(node);	
			}
			void		swap(red_black_tree& other)
			{
				node_ptr		_end_tmp = this->_end;
				node_ptr		_root_tmp = this->_root;
				size_type		_size_tmp = this->_size;
				key_compare		_cmp_tmp = this->_cmp;
				allocator_type	_alloc_tmp = this->_alloc;

				this->_end = other._end;
				this->_root = other._root;
				this->_size = other._size;
				this->_cmp = other._cmp;
				this->_alloc = other._alloc;
				other._end = _end_tmp;
				other._root = _root_tmp;
				other._size = _size_tmp;
				other._cmp = _cmp_tmp;
				other._alloc = _alloc_tmp;
			}
			node_ptr	get_lowest() const
			{
				node_ptr	res = _root;

				if (!res)
					return (_end);
				while (res->left)
					res = res->left;
				return (res);
			}
			node_ptr	get_biggest() const
			{
				node_ptr	res = _root;

				if (!res)
					return (NULL);
				while (res->right && res->right != _end)
					res = res->right;
				return (res);
			}
			ft::pair<node_ptr, bool>	insert(value_type value)
			{
				node_ptr					exists;
				node_ptr					new_node;
				ft::pair<node_ptr, bool>	res;

				exists = exist(value);
				if (exists)
				 	return (ft::make_pair(exists, false));
				new_node = _create_node(value);
				if (!_root)
				{
					_root = new_node;
					_root->color = BLACK;
					++_size;
					_connect_end();
					return (ft::make_pair(new_node, true));
				}
				_cut_end_connections();
				res = _insert(_root, new_node);
				++_size;
				_connect_end();
				return (res);
			}
			void		erase(value_type key)
			{
				node_ptr	node_to_delete;

				node_to_delete = exist(key);
				if (!node_to_delete)
					return ;
				else if (_size == 1)
					_root = NULL;
				else
				{
					_cut_end_connections();
					_erase(node_to_delete);
				}
				_alloc.destroy(node_to_delete);
				_alloc.deallocate(node_to_delete, 1);
				_size--;
				_connect_end();
			}
		private:
			node_ptr	_create_node(value_type value)
			{
				node_ptr	new_node;

				new_node = _alloc.allocate(1);
				_alloc.construct(new_node, value);

				return (new_node);
			}
			void		_clear(node_ptr node_to_delete)
			{
				if (!node_to_delete)
					return ;
				if (node_to_delete->left)
					_clear(node_to_delete->left);
				if (node_to_delete->right)
					_clear(node_to_delete->right);
				_alloc.destroy(node_to_delete);
				_alloc.deallocate(node_to_delete, 1);
				node_to_delete = NULL;
			}
			void 		_copy(node_ptr copy, node_ptr copy_end)
			{
				if (!copy || copy == copy_end)
					return ;
				if (copy->left)
					_copy(copy->left, copy_end);
				if (copy->right)
					_copy(copy->right, copy_end);
				insert(copy->value);
			}
			node_ptr	_find(node_ptr node, value_type key) const
			{
				if (!node)
					return (NULL);
				else if (_cmp(key, node->value) && !_cmp(node->value, key))
					return (_find(node->left, key));
				else if (!_cmp(key, node->value) && _cmp(node->value, key))
					return (_find(node->right, key));
				return (node);
			}
			void 		_cut_end_connections()
			{
				node_ptr	biggest;

				biggest = get_biggest();
				if (biggest)
					biggest->right = NULL;
				if (_end)
					_end->parent = NULL;
			}
			void 		_connect_end()
			{
				node_ptr	biggest;

				biggest = get_biggest();
				if (biggest)
					biggest->right = _end;
				if (!_end)
					_end = _create_node(value_type());
				_end->parent = biggest;
			}
/* ================================================================ */
/* ============================ Rotations ========================= */
/* ================================================================ */
			void	_left_right_rotation(node_ptr imbalanced_node)
			{
				_left_rotation(imbalanced_node->left);
				_right_rotation(imbalanced_node);
			}
			void	_right_left_rotation(node_ptr imbalanced_node)
			{
				_right_rotation(imbalanced_node->right);
				_left_rotation(imbalanced_node);
			}
			void	_left_rotation(node_ptr imbalanced_node)
			{
				node_ptr	tmp;

				tmp = imbalanced_node->right;
				imbalanced_node->right = tmp->left;
				if (imbalanced_node->right)
				{
					imbalanced_node->right->parent = imbalanced_node;
					imbalanced_node->right->is_left = 0;
				}
				if (!imbalanced_node->parent)
				{
					_root = tmp;
					tmp->parent = NULL;
				}
				else
				{
					tmp->parent = imbalanced_node->parent;
					if (imbalanced_node->is_left)
					{
						tmp->is_left = 1;
						tmp->parent->left = tmp;
					}
					else
					{
						tmp->is_left = 0;
						tmp->parent->right = tmp;
					}
				}
				tmp->left = imbalanced_node;
				imbalanced_node->is_left = 1;
				imbalanced_node->parent = tmp;
			}
			void	_right_rotation(node_ptr imbalanced_node)
			{
				node_ptr	tmp;

				tmp = imbalanced_node->left;
				imbalanced_node->left = tmp->right;
				if (imbalanced_node->left)
				{
					imbalanced_node->left->parent = imbalanced_node;
					imbalanced_node->left->is_left = 1;
				}
				if (!imbalanced_node->parent)
				{
					_root = tmp;
					tmp->parent = NULL;
				}
				else
				{
					tmp->parent = imbalanced_node->parent;
					if (imbalanced_node->is_left)
					{
						tmp->is_left = 1;
						tmp->parent->left = tmp;
					}
					else
					{
						tmp->is_left = 0;
						tmp->parent->right = tmp;
					}
				}
				tmp->right = imbalanced_node;
				imbalanced_node->is_left = 0;
				imbalanced_node->parent = tmp;
			}
			void	_rotate(node_ptr imbalanced_node)
			{
				if (imbalanced_node->is_left && imbalanced_node->parent->is_left)
				{
					_right_rotation(imbalanced_node->parent->parent);
					imbalanced_node->color = RED;
					imbalanced_node->parent->color = BLACK;
					if (imbalanced_node->parent->right)
						imbalanced_node->parent->right->color = RED;
				}
				else if (!imbalanced_node->is_left && !imbalanced_node->parent->is_left)
				{
					_left_rotation(imbalanced_node->parent->parent);
					imbalanced_node->color = RED;
					imbalanced_node->parent->color = BLACK;
					if (imbalanced_node->parent->left)
						imbalanced_node->parent->left->color = RED;
				}
				else if (!imbalanced_node->is_left && imbalanced_node->parent->is_left)
				{
					_left_right_rotation(imbalanced_node->parent->parent);
					imbalanced_node->color = BLACK;
					imbalanced_node->right->color = RED;
					imbalanced_node->left->color = RED;
				}
				else
				{
					_right_left_rotation(imbalanced_node->parent->parent);
					imbalanced_node->color = BLACK;
					imbalanced_node->right->color = RED;
					imbalanced_node->left->color = RED;
				}
			}
/* ================================================================ */
/* ============================ Insert ============================ */
/* ================================================================ */
			void	_color_flip(node_ptr imbalanced_node)
			{
				imbalanced_node->parent->color = BLACK;
				imbalanced_node->parent->parent->color = RED;
				imbalanced_node->get_aunt()->color = BLACK;
			}
			void	_check_color(node_ptr new_node)
			{
				if (!new_node)
					return ;
				if (new_node == _root)
				{
					new_node->color = BLACK;
					return ;
				}
				if (new_node->color == RED && new_node->parent->color == RED)
					_insert_balance(new_node);
				_check_color(new_node->parent);
			}
			void	_insert_balance(node_ptr imbalanced_node)
			{
				if (imbalanced_node->get_aunt() && imbalanced_node->get_aunt()->color == RED)
					_color_flip(imbalanced_node);
				else
					_rotate(imbalanced_node);
			}
			ft::pair<node_ptr, bool>	_insert(node_ptr parent, node_ptr new_node)
			{
				if (_cmp(parent->value, new_node->value))
				{
					if (!parent->right)
					{
						parent->right = new_node;
						new_node->parent = parent;
						new_node->is_left = 0;
					}
					else
						_insert(parent->right, new_node);
				}
				else
				{
					if (!parent->left)
					{
						parent->left = new_node;
						new_node->parent = parent; 
						new_node->is_left = 1;
					}
					else
						_insert(parent->left, new_node);
				}
				_check_color(new_node);
				return (ft::make_pair(new_node, true));
			}
/* ================================================================ */
/* ============================= Erase ============================ */
/* ================================================================ */
			void		_assign(node_ptr parent, node_ptr to, bool is_left)
			{
				if (is_left)
					parent->left = to;
				else
					parent->right = to;
				if (to)
					to->is_left = is_left;
			}
			node_ptr	_replace(node_ptr node_to_delete, node_ptr replacement)
			{
				if (node_to_delete == _root)
				{
					_root = replacement;
					_root->parent = NULL;
					_root->color = BLACK;
				}
				else
				{
					if (node_to_delete->is_left)
						_assign(node_to_delete->parent, replacement, 1);
					else
						_assign(node_to_delete->parent, replacement, 0);
					if (replacement && replacement->parent)
						replacement->parent = node_to_delete->parent;
				}
				return (replacement);
			}
			node_ptr	_get_successor(node_ptr node)
			{
				node_ptr	res;

				res = node->right;
				while (res->left)
					res = res->left;
				return(res);
			}
			void	_fixup_case_1(node_ptr parent, bool is_left)
			{
				parent->color = RED;
				if (is_left)
				{
					parent->right->color = BLACK;
					_left_rotation(parent);
				}
				else
				{
					parent->left->color = BLACK;
					_right_rotation(parent);
				}
				_get_sibling(parent, is_left);
			}
			void	_fixup_case_2(node_ptr parent, bool is_left)
			{
				if (is_left)
					parent->right->color = RED;
				else
					parent->left->color = RED;
				if (parent->color == RED)
					parent->color = BLACK;
				else if (parent->color == BLACK && parent == _root)
					return ;
				else
					_get_sibling(parent->parent, parent->is_left);
			}
			void	_fixup_case_3(node_ptr parent, bool is_left)
			{
				if (is_left)
				{
					if (parent->right->left)
						parent->right->left->color = BLACK;
					parent->right->color = RED;
					_right_rotation(parent->right);
				}
				else
				{
					if (parent->left->right)
						parent->left->right->color = BLACK;
					parent->left->color = RED;
					_left_rotation(parent->left);
				}
				_fixup_case_4(parent, is_left);
			}
			void	_fixup_case_4(node_ptr parent, bool is_left)
			{
				if (is_left)
				{
					parent->right->color = parent->color;
					parent->color = BLACK;
					if (parent->right->right)
						parent->right->right->color = BLACK;
					_left_rotation(parent);
				}
				else
				{
					parent->left->color = parent->color;
					parent->color = BLACK;
					if (parent->left->left)
						parent->left->left->color = BLACK;
					_right_rotation(parent);
				}
			}
			void 	_erase_fixup(node_ptr parent, node_ptr sibling, node_ptr x, bool is_left)
			{
				if (x && x->color == RED)
					x->color = BLACK;
				else if (sibling && sibling->color == RED)
					_fixup_case_1(parent, is_left);
				else if (sibling && sibling->color == BLACK
						&& (!sibling->right || (sibling->right && sibling->right->color == BLACK))
						&& (!sibling->left || (sibling->left && sibling->left->color == BLACK)))
					_fixup_case_2(parent, is_left);
				else if (sibling && sibling->color == BLACK
						&& ((is_left && sibling->left && sibling->left->color == RED
						&& (!sibling->right || (sibling->right && sibling->right->color == BLACK)))
						|| (!is_left && sibling->right && sibling->right->color == RED
						&& (!sibling->left || (sibling->left && sibling->left->color == BLACK)))))
					_fixup_case_3(parent, is_left);
				else if (sibling && sibling->color == BLACK
						&& ((is_left && sibling->right && sibling->right->color == RED)
						|| (!is_left && sibling->left && sibling->left->color == RED)))
					_fixup_case_4(parent, is_left);
			}
			void		_get_sibling(node_ptr parent, bool is_left)
			{
				if (is_left)
					_erase_fixup(parent, parent->right, parent->left, is_left);
				else
					_erase_fixup(parent, parent->left, parent->right, is_left);
			}
			void		_erase_balance(node_ptr node_to_delete, node_ptr replacement, node_ptr parent, bool is_left)
			{
				node_ptr	x;

				if (is_left)
					x = parent->left;
				else
					x = parent->right;
				if (node_to_delete->color == RED
					&& (!replacement || (replacement && replacement->color == RED)))
					return ;
				else if (node_to_delete->color == RED && replacement && replacement->color == BLACK)
				{
					replacement->color = RED;
					_get_sibling(parent, is_left);
				}
				else if (node_to_delete->color == BLACK && replacement && replacement->color == RED)
					replacement->color = BLACK;
				else if (node_to_delete->color == BLACK
						&& (!replacement || (replacement && replacement->color == BLACK)) && x == _root)
					return ;
				else if (node_to_delete->color == BLACK
						&& (!replacement || (replacement && replacement->color == BLACK)) && x != _root)
					_get_sibling(parent, is_left);
			}
			void		_child_is_null(node_ptr node_to_delete)
			{
				bool		is_left;
				node_ptr	parent;
				node_ptr	replacement;

				parent = NULL;
				if (!node_to_delete->left && !node_to_delete->right)
				{
					replacement = _replace(node_to_delete, NULL);
					parent = node_to_delete->parent;
					is_left = node_to_delete->is_left;
				}
				else if (!node_to_delete->right)
				{
					replacement = _replace(node_to_delete, node_to_delete->left);
					parent = replacement->parent;
					is_left = 1;
				}
				else if (!node_to_delete->left)
				{
					replacement = _replace(node_to_delete, node_to_delete->right);
					parent = replacement->parent;
					is_left = 0;
				}
				if (!parent)
					return ;
				_erase_balance(node_to_delete, replacement, parent, is_left);
			}
			void 		_both_child_exist(node_ptr node_to_delete)
			{
				bool		is_left;
				node_ptr	parent;
				node_ptr	replacement;

				replacement = _get_successor(node_to_delete);
				if (replacement == node_to_delete->right)
				{
					_replace(node_to_delete, replacement);
					replacement->left = node_to_delete->left;
					replacement->left->parent = replacement;
					parent = replacement;
					is_left = 0;
				}
				else
				{
					parent = replacement->parent;
					is_left = replacement->is_left;
					_replace(replacement, replacement->right);
					_replace(node_to_delete, replacement);
					replacement->left = node_to_delete->left;
					replacement->right = node_to_delete->right;
					replacement->left->parent = replacement;
					replacement->right->parent = replacement;
				}
				_erase_balance(node_to_delete, replacement, parent, is_left);		
			}
			void		_erase(node_ptr node_to_delete)
			{
				if (!node_to_delete->right || !node_to_delete->left)
					_child_is_null(node_to_delete);
				else
					_both_child_exist(node_to_delete);
			}
	};
}

#endif // RED_BLACK_TREE

/*
	RED BLACK TREE RULES

	1. Every node is red or black
	2. Root is always black
	3. New insertions are always red
	4. Every path from root - leaf(NULL) has the same number of BALCK nodes
	5. No path can have two consecutice RED nodes
	6. NULLs are black

	FIX TREE RULES

	1. If we have BLACK aunt - rotate
		- if imbalance is in right child and right subtree - left rotation
		- if imbalance is in right child and left subtree - right/left rotation
		- if imbalance is in left child and right subtree - left/right rotation
		- if imbalance is in left child and left subtree - right rotation
	2. If we have RED aunt - color flip
	3. After rotation working nodes should look like: parent - black, childrens - red
	4. Afrter color flip working nodes should look like: parent - red, childrens - black
*/
