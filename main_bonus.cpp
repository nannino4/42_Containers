
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

	// // test vector
	// ftOutput = testVector(seed);
	// {
	// 	namespace ft = std;
	// 	stdOutput = testVector(seed);
	// }
	// // std::cout << ftOutput.output << std::endl << std::endl;
	// // std::cout << stdOutput.output << std::endl << std::endl;
	// if ((ftOutput.time / stdOutput.time) > 20)
	// 	return (error_exit("ft::vector is too slow"));
	// if (ftOutput.output.compare(stdOutput.output))
	// 	return (error_exit("ft::vector has different outputs than std::vector"));
	// std::cout << "ft::vector time: " << ftOutput.time << std::endl;
	// std::cout << "std::vector time: " << stdOutput.time << std::endl << std::endl;

	// test stack
	ftOutput = testStackFT(seed);
	stdOutput = testStackSTD(seed);
	// std::cout << "FT OUTPUT\n" << ftOutput.output << std::endl << std::endl;
	// std::cout << "STD OUTPUT\n" << stdOutput.output << std::endl << std::endl;
	std::cout << "ft::stack time: " << ftOutput.time << std::endl;
	std::cout << "std::stack time: " << stdOutput.time << std::endl << std::endl;
	if ((ftOutput.time / stdOutput.time) > 20)
		return (error_exit("ft::stack is too slow"));
	if (ftOutput.output.compare(stdOutput.output))
		return (error_exit("ft::stack has different outputs than std::stack"));

	// // test map
	// ftOutput = testMap(seed);
	// {
	// 	namespace ft = std;
	// 	stdOutput = testMap(seed);
	// }
	// // std::cout << ftOutput.output << std::endl << std::endl;
	// // std::cout << stdOutput.output << std::endl << std::endl;
	// if ((ftOutput.time / stdOutput.time) > 20)
	// 	return (error_exit("ft::map is too slow"));
	// if (ftOutput.output.compare(stdOutput.output))
	// 	return (error_exit("ft::map has different outputs than std::map"));
	// std::cout << "ft::stack time: " << ftOutput.time << std::endl;
	// std::cout << "std::stack time: " << stdOutput.time << std::endl << std::endl;

	std::cout << "all tests passed successfully!" << std::endl;

	return (0);
}