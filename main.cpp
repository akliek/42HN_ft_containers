#include <set>
#include <map>
#include <ctime>
#include <stack>
#include <vector>
#include <iostream>

#include "./containers/vector.hpp"
#include "./containers/stack.hpp"
#include "./containers/map.hpp"
#include "./containers/set.hpp"

#define TESTED_NAMESPACE ft
#ifdef STDSTL
# undef TESTED_NAMESPACE
# define TESTED_NAMESPACE std
#endif

# define VECTOR_TEST	1
# define MAP_TEST		1
# define STACK_TEST		1
# define SET_TEST		1

#include <stdlib.h>

int	main()
{
	#if VECTOR_TEST
	{
		TESTED_NAMESPACE::vector<int>			v;
		TESTED_NAMESPACE::vector<int>::iterator	it;
		clock_t									clock;

		clock = std::clock();

		for (int i = 0; i < 100000000; i++)
			v.push_back(i);

		v.erase(v.begin(), v.end());;

		std::cout << "Time taken for vector: " << (double)(std::clock() - clock) / CLOCKS_PER_SEC << "s" << std::endl;

	}
	#ifndef STDSTL
		system("leaks my_containers | tail -3");
	#else
		system("leaks original_containers | tail -3");
	#endif
	#endif // vector	

	#if STACK_TEST
	{
		TESTED_NAMESPACE::stack<int>			st;
		clock_t									clock;

		clock = std::clock();

		for (int i = 0; i < 100000000; i++)
			st.push(i + 42);

		for (size_t i = 0; i < st.size(); i++)
			st.pop();

		std::cout << "Time taken for stack: " << (double)(std::clock() - clock) / CLOCKS_PER_SEC << "s" << std::endl;

	}
	#ifndef STDSTL
		system("leaks my_containers | tail -3");
	#else
		system("leaks original_containers | tail -3");
	#endif
	#endif // stack

	#if MAP_TEST
	{
		TESTED_NAMESPACE::map<int, int>				m;
		TESTED_NAMESPACE::map<int, int>::iterator	it;
		clock_t										clock;

		clock = std::clock();

		for (int i = 0; i < 1000000; i++)
			m.insert(TESTED_NAMESPACE::make_pair<int, int>(i, i + 42));

		m.erase(m.begin(), m.end());

		std::cout << "Time taken for map: " << (double)(std::clock() - clock) / CLOCKS_PER_SEC << "s" << std::endl;
	}
	#ifndef STDSTL
		system("leaks my_containers | tail -3");
	#else
		system("leaks original_containers | tail -3");
	#endif
	#endif // map

	#if SET_TEST
	{
		TESTED_NAMESPACE::set<int>				s;
		TESTED_NAMESPACE::set<int>::iterator	it;
		clock_t									clock;

		clock = std::clock();

		for (int i = 0; i < 1000000; i++)
			s.insert(i);

		s.erase(s.begin(), s.end());

		std::cout << "Time taken for set: " << (double)(std::clock() - clock) / CLOCKS_PER_SEC << "s" << std::endl;

	}
	#ifndef STDSTL
		system("leaks my_containers | tail -3");
	#else
		system("leaks original_containers | tail -3");
	#endif
	#endif // set

	return (0);
}
