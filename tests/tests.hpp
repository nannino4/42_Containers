#pragma once

#include <sstream>
#include <string>

struct testOutput
{
	float time;
	std::string output;
};

testOutput testVector(bool isSTD, const int seed);
testOutput testStack(bool isSTD, const int seed);
testOutput testMap(bool isSTD, const int seed);
testOutput testSet(bool isSTD, const int seed);
