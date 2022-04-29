#include <string>
#include <sys/time.h>
#include <fstream>

#include "tests.hpp"

#ifdef USE_STD
	namespace ft = std;
	#include <map>
	#define FILENAME "output_map_std.txt"
#else
	#include "../containers/map.hpp"
	#define FILENAME "output_map_ft.txt"
#endif

void testMap(const int seed)
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
	ft::map<int, int> map_int;

	for (int i = 0; i < COUNT; ++i)
		map_int.insert(ft::make_pair(rand(), rand()));

	{
		ft::map<int,int>::iterator it = map_int.begin();
		for (size_t i = 0; i < (rand() % (map_int.size() / 2)); ++i)
			++it;
		ft::map<int,int> tmp(it, map_int.end());
		for (int i = 0; i < COUNT; ++i)
			tmp.insert(ft::make_pair(rand(), rand()));
		map_int.insert(tmp.begin(), tmp.end());
	}
	{
		ft::map<int,int>::iterator it = map_int.begin();
		for (size_t i = 0; i < (rand() % (map_int.size() / 2)); ++i)
			++it;
		map_int.erase(it, map_int.end());
	}

// print //////////
	for (int i = 0; i < COUNT; ++i)
	{
		ft::map<int,int>::iterator it = map_int.begin();
		for (size_t i = 0; i < (rand() % (map_int.size() / 2)); ++i)
			++it;
		output << (map_int.find(it->first))->first << std::endl;
		if ((it = map_int.lower_bound(rand())) != map_int.end())
		output << it->first << std::endl;
		output << map_int[rand()] << std::endl;
	}

	ft::map<int, int> map_copy = map_int;
	output << (map_int == map_copy) << std::endl;		// true
	output << (map_int <= map_copy) << std::endl;		// true
	output << (map_int < map_copy) << std::endl;		// false
	output << (map_int >= map_copy) << std::endl;		// true
	output << (map_int > map_copy) << std::endl;		// false

	for (ft::map<int,int>::iterator it = map_int.begin(), it_copy = map_copy.begin(); it != map_int.end(); ++it, ++it_copy)
	{
		output << (*it).first << " " << (*it).second << std::endl;
		output << (*it_copy).first << " " << (*it_copy).second << std::endl;
	}
	for (ft::map<int,int>::reverse_iterator it = map_int.rbegin(), it_copy = map_copy.rbegin(); it != map_int.rend(); ++it, ++it_copy)
	{
		output << (*it).first << " " << (*it).second << std::endl;
		output << (*it_copy).first << " " << (*it_copy).second << std::endl;
	}

	map_int.insert(ft::make_pair<int,int>(rand(),rand()));
	output << (map_int == map_copy) << std::endl;		// false
	output << (map_int <= map_copy) << std::endl;		// ?
	output << (map_int < map_copy) << std::endl;		// ?
	output << (map_int >= map_copy) << std::endl;		// ?
	output << (map_int > map_copy) << std::endl;		// ?
///////////////////

/**************************************************************************************************
 * end tests
**************************************************************************************************/

	gettimeofday(&time_end, NULL);
	output.close();
	output.open("performances/" + filename);
	output << time_end.tv_sec - time_start.tv_sec + 1e-6 * (time_end.tv_usec - time_start.tv_usec);
}