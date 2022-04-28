#include <string>
#include <map>
#include <sys/time.h>

#include "tests.hpp"
#include "../containers/map.hpp"

#define COUNT 10

testOutput testMap(bool isSTD, const int seed)
{
	if (isSTD)
		namespace ft = std;
	srand(seed);

	testOutput ret;
	std::stringstream output;
	output << std::boolalpha;
	struct timeval time_start;
	struct timeval time_end;
	gettimeofday(&time_start, NULL);

/**************************************************************************************************
 * start tests
**************************************************************************************************/
	ft::map<int, int> map_int;

	for (int i = 0; i < COUNT; ++i)
	{
		map_int.insert(ft::make_pair(rand(), rand()));
	}

	{
		ft::map<int,int> tmp(map_int.begin() + (rand() % (map_int.size() / 2)), map_int.end());
		map_int.insert(tmp.begin(), tmp.end());
	}

	map_int.erase(map_int.begin() + (rand() % (map_int.size() / 2)), map_int.end());

// print //////////
	for (int i = 0; i < COUNT; ++i)
	{
		output << (map_int.find((map_int.begin() + (rand() % (map_int.size() - 1)))->first))->first << std::endl;
		output << map_int.lower_bound(rand())->first << std::endl;
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
	ret.time = time_end.tv_sec - time_start.tv_sec + 1e-6 * (time_end.tv_usec - time_start.tv_usec);
	ret.output = output.str();
	return ret;
}