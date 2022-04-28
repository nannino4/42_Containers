
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
	testOutput ftOutput;
	testOutput stdOutput;

	// test vector
	stdOutput = testVector("STD", seed);
	ftOutput = testVector("FT", seed);
	if ((ftOutput.time / stdOutput.time) > 20)
		return (error_exit("ft::vector is too slow"));
	if (ftOutput.output.compare(stdOutput.output))
		return (error_exit("ft::vector has different outputs than std::vector"));
	// std::cout << ftOutput.output << std::endl << std::endl;
	// std::cout << stdOutput.output << std::endl << std::endl;
	std::cout << "ft::vector time: " << ftOutput.time << std::endl;
	std::cout << "std::vector time: " << stdOutput.time << std::endl << std::endl;

	// test stack
	stdOutput = testStack("STD", seed);
	ftOutput = testStack("FT", seed);
	if ((ftOutput.time / stdOutput.time) > 20)
		return (error_exit("ft::stack is too slow"));
	if (ftOutput.output.compare(stdOutput.output))
		return (error_exit("ft::stack has different outputs than std::stack"));
	// std::cout << ftOutput.output << std::endl << std::endl;
	// std::cout << stdOutput.output << std::endl << std::endl;
	std::cout << "ft::stack time: " << ftOutput.time << std::endl;
	std::cout << "std::stack time: " << stdOutput.time << std::endl << std::endl;

	// test map
	stdOutput = testMap("STD", seed);
	ftOutput = testMap("FT", seed);
	if ((ftOutput.time / stdOutput.time) > 20)
		return (error_exit("ft::map is too slow"));
	if (ftOutput.output.compare(stdOutput.output))
		return (error_exit("ft::map has different outputs than std::map"));
	// std::cout << ftOutput.output << std::endl << std::endl;
	// std::cout << stdOutput.output << std::endl << std::endl;
	std::cout << "ft::stack time: " << ftOutput.time << std::endl;
	std::cout << "std::stack time: " << stdOutput.time << std::endl << std::endl;

	// // test set
	// stdOutput = testSet("STD", seed);
	// ftOutput = testSet("FT", seed);
	// if ((ftOutput.time / stdOutput.time) > 20)
	// 	return (error_exit("ft::set is too slow"));
	// if (ftOutput.output.compare(stdOutput.output))
	// 	return (error_exit("ft::set has different outputs than std::set"));

	std::cout << "all tests passed successfully!" << std::endl;

	return (0);
}