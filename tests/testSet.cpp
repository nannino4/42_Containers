#include <string>
#include <sys/time.h>
#include <fstream>

#include "tests.hpp"

#ifdef USE_STD
	namespace ft = std;
	#include <set>
	#define FILENAME "output_set_std.txt"
#else
	#include "../containers/set.hpp"
	#define FILENAME "output_set_ft.txt"
#endif

void testSet(const int seed)
{
	srand(seed);

	std::string filename(FILENAME);
	std::ofstream output;
	output.open("outputs/" + filename, std::ofstream::trunc);
	output << std::boolalpha;
	struct timeval time_start;
	struct timeval time_end;
	gettimeofday(&time_start, NULL);

/**************************************************************************************************
 * start tests
**************************************************************************************************/
	ft::set<int> set_int;

	for (int i = 0; i < COUNT; ++i)
		set_int.insert(rand());

	{
		ft::set<int>::iterator it = set_int.begin();
		for (size_t i = 0; i < (rand() % (set_int.size() / 2)); ++i)
			++it;
		ft::set<int> tmp(it, set_int.end());
		for (int i = 0; i < COUNT; ++i)
			tmp.insert(rand());
		set_int.insert(tmp.begin(), tmp.end());
	}
	{
		ft::set<int>::iterator it = set_int.begin();
		for (size_t i = 0; i < (rand() % (set_int.size() / 2)); ++i)
			++it;
		set_int.erase(it, set_int.end());
	}

// print //////////
	for (int i = 0; i < COUNT; ++i)
	{
		ft::set<int>::iterator it = set_int.begin();
		for (size_t i = 0; i < (rand() % (set_int.size() / 2)); ++i)
			++it;
		output << *(set_int.find(*it)) << std::endl;
		if ((it = set_int.lower_bound(rand())) != set_int.end())
		output << *it << std::endl;
	}

	ft::set<int> set_copy = set_int;
	output << (set_int == set_copy) << std::endl;		// true
	output << (set_int <= set_copy) << std::endl;		// true
	output << (set_int < set_copy) << std::endl;		// false
	output << (set_int >= set_copy) << std::endl;		// true
	output << (set_int > set_copy) << std::endl;		// false

	for (ft::set<int>::iterator it = set_int.begin(), it_copy = set_copy.begin(); it != set_int.end(); ++it, ++it_copy)
	{
		output << *it << std::endl;
		output << (*it_copy) << std::endl;
	}
	for (ft::set<int>::reverse_iterator it = set_int.rbegin(), it_copy = set_copy.rbegin(); it != set_int.rend(); ++it, ++it_copy)
	{
		output << (*it) << std::endl;
		output << (*it_copy) << std::endl;
	}

	set_int.insert(rand());
	output << (set_int == set_copy) << std::endl;		// false
	output << (set_int <= set_copy) << std::endl;		// ?
	output << (set_int < set_copy) << std::endl;		// ?
	output << (set_int >= set_copy) << std::endl;		// ?
	output << (set_int > set_copy) << std::endl;		// ?
///////////////////

/**************************************************************************************************
 * end tests
**************************************************************************************************/

	gettimeofday(&time_end, NULL);
	output.close();
	output.open("performances/" + filename);
	output << time_end.tv_sec - time_start.tv_sec + 1e-6 * (time_end.tv_usec - time_start.tv_usec);
}