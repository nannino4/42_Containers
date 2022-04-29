
#include <iostream>
#include "./tests/tests.hpp"

int error_exit(std::string s)
{
	std::cout << s << std::endl;
	return 1;
}

int main(int argc, char** argv) {
	if (argc != 2)
	{
		std::cerr << "Usage: ./test seed" << std::endl;
		std::cerr << "Provide a seed please" << std::endl;
		return 1;
	}
	const int seed = atoi(argv[1]);

	// test vector
	testVector(seed);

	// test stack
	testStack(seed);

	// test map
	testMap(seed);

	// test set
	testSet(seed);

	return (0);
}