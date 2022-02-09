#include <iostream>
#include "./containers/vector.hpp"
#include "./containers/stack.hpp"

#include <vector>

int	main()
{
	// {
	// 	ft::stack<int>	s;
	
	// 	s.push(41);
	// 	s.push(29);
	// 	s.push(10);
	// 	s.push(42);

	// 	while (s.size() != 0)
	// 	{
	// 		std::cout << "- " << s.top() << std::endl;
	// 		s.pop();
	// 	}
	// }

	{
		ft::vector<int>	v(5, 7);
		ft::vector<int>	copy(3, 2);

		for (int i = 0; i < v.size(); i++)
			std::cout << v[i] << " ";
		std::cout << std::endl;
		std::cout << "size: " << v.size() << " capacity: " << v.capacity() << std::endl;
		for (int i = 0; i < copy.size(); i++)
			std::cout << copy[i] << " ";
		std::cout << std::endl;
		std::cout << "size: " << copy.size() << " capacity: " << copy.capacity() << std::endl;
		ft::swap(v, copy);
		for (int i = 0; i < v.size(); i++)
			std::cout << v[i] << " ";
		std::cout << std::endl;
		std::cout << "size: " << v.size() << " capacity: " << v.capacity() << std::endl;
		for (int i = 0; i < copy.size(); i++)
			std::cout << copy[i] << " ";
		std::cout << std::endl;
		std::cout << "size: " << copy.size() << " capacity: " << copy.capacity() << std::endl;
	}

	system("leaks a.out");

	return (0);
}
