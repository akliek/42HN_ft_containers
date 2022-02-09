#ifndef STACK_HPP
# define STACK_HPP

# include "vector.hpp"

namespace ft
{
	template < class T, class Container = ft::vector<T> >
	class stack
	{
		/* ========== Member types ========== */
		public:
    		typedef Container									container_type;
			typedef typename container_type::size_type			size_type;
			typedef typename container_type::value_type			value_type;
			typedef typename container_type::reference			reference;
			typedef typename container_type::const_reference	const_reference;
		/* ========== Underlying container ========== */
		protected:
			container_type	c;
		/* ========== Member functions ========== */
		public:
			/* ========== Constructor ========== */
			explicit stack(const Container &cont = Container()): c(cont) {};

			/* ========== Destructor ========== */
			~stack() { c.clear(); };

			void			pop() { c.pop_back(); };
			void			push(const value_type& value) { c.push_back(value); };
			bool			empty() const { return (c.empty()); };
			size_type		size() const { return (c.size()); };
			reference		top() { return (c.back()); };
			const_reference	top() const { return (c.back()); };

			/* ========== Assignation operator overloading ========== */
			stack&	operator=(const stack& other)
			{
				this->c = other.c;

				return (*this);
			};
			/* ========== Friend non-member functions declaration ========== */
			template< class DT, class ContainerFriend >
				friend bool	operator==( const ft::stack<DT,ContainerFriend>& lhs, const ft::stack<DT,ContainerFriend>& rhs );
			template< class DT, class ContainerFriend >
				friend bool	operator!=( const ft::stack<DT,ContainerFriend>& lhs, const ft::stack<DT,ContainerFriend>& rhs );
			template< class DT, class ContainerFriend >
				friend bool	operator<( const ft::stack<DT,ContainerFriend>& lhs, const ft::stack<DT,ContainerFriend>& rhs );
			template< class DT, class ContainerFriend >
				friend bool	operator<=( const ft::stack<DT,ContainerFriend>& lhs, const ft::stack<DT,ContainerFriend>& rhs );
			template< class DT, class ContainerFriend >
				friend bool	operator>( const ft::stack<DT,ContainerFriend>& lhs, const ft::stack<DT,ContainerFriend>& rhs );
			template< class DT, class ContainerFriend >
				friend bool	operator>=( const ft::stack<DT,ContainerFriend>& lhs, const ft::stack<DT,ContainerFriend>& rhs );
	};
	/* ========== Non-member functions ========== */
	template< class T, class Container >
		bool	operator==( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs ) { return(lhs.c == rhs.c); };
	template< class T, class Container >
		bool	operator!=( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs ) { return(lhs.c != rhs.c); };
	template< class T, class Container >
		bool	operator<( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs ) { return(lhs.c < rhs.c); };
	template< class T, class Container >
		bool	operator<=( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs ) { return(lhs.c <= rhs.c); };
	template< class T, class Container >
		bool	operator>( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs ) { return(lhs.c > rhs.c); };
	template< class T, class Container >
		bool	operator>=( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs ) { return(lhs.c >= rhs.c); };
}

#endif  // STACK_HPP
