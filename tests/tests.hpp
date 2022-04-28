#pragma once

#include <sstream>
#include <string>

struct testOutput
{
	float time;
	std::string output;
};

testOutput testVector(std::string ns, const int seed);
testOutput testStack(std::string ns, const int seed);
testOutput testMap(std::string ns, const int seed);
testOutput testSet(std::string ns, const int seed);
