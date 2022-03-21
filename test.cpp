#include <vector>
#include <iostream>

int main()
{
	std::vector<int> vec;

	for (int i = 0; i < 10; i++)
	{
		vec.push_back(i);
		// std::cout << vec.at(i) << std::endl;
	}
	try
	{
		vec.insert(vec.end(), -2, int());
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
}