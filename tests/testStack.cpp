#include <string>
#include <deque>
#include <sys/time.h>
#include <fstream>

#include "tests.hpp"

#ifdef USE_STD
	namespace ft = std;
	#include <stack>
	#include <vector>
	#define FILENAME "output_stack_std.txt"
#else
	#include "../containers/stack.hpp"
	#define FILENAME "output_stack_ft.txt"
#endif

template<typename T>
class MutantStack : public ft::stack<T>
{
public:
	MutantStack() {}
	MutantStack(const MutantStack<T>& src) { *this = src; }
	MutantStack<T>& operator=(const MutantStack<T>& rhs) 
	{
		this->c = rhs.c;
		return *this;
	}
	~MutantStack() {}

	typedef typename ft::stack<T>::container_type::iterator iterator;

	iterator begin() { return this->c.begin(); }
	iterator end() { return this->c.end(); }
};

void testStack(const int seed)
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

	ft::stack<int> stack_int(ft::stack<int>::container_type(COUNT, 42));
	ft::stack<int> stack_int_copy(ft::stack<int>::container_type(COUNT, 42));
	ft::stack<std::string, std::deque<std::string> > stack_deq_str;
	MutantStack<char> stack_iter;

	output << (stack_int == stack_int_copy) << std::endl;		// true
	output << (stack_int < stack_int_copy) << std::endl;		// false
	output << (stack_int <= stack_int_copy) << std::endl;		// true
	output << (stack_int >= stack_int_copy) << std::endl;		// true

	for (int i = 0; i < COUNT; ++i)
	{
		stack_iter.push((rand() % 93) + 33);
		stack_int_copy.push(rand());
		stack_deq_str.push("ciao");
	}

	output << (stack_int == stack_int_copy) << std::endl;		// false
	output << (stack_int < stack_int_copy) << std::endl;		// true
	output << (stack_int <= stack_int_copy) << std::endl;		// true
	output << (stack_int >= stack_int_copy) << std::endl;		// false

// print //////////
	for (MutantStack<char>::iterator it = stack_iter.begin(); it != stack_iter.end(); ++it)
	{
		output << *it << std::endl;
	}
	while (stack_deq_str.size())
	{
		output << stack_deq_str.top() << std::endl;
		stack_deq_str.pop();
	}
	
	while (stack_int.size() && stack_int_copy.size())
	{
		output << stack_int.top() << std::endl;
		output << stack_int_copy.top() << std::endl;
		stack_int.pop();
		stack_int_copy.pop();
	}
	output << stack_int.size() << " " << stack_int.empty() << std::endl;
	output << stack_int_copy.size() << " " << stack_int_copy.empty() << std::endl;
	while (stack_int.size() && stack_int_copy.size())
	{
		output << stack_int_copy.top() << std::endl;
		stack_int_copy.pop();
	}
///////////////////

/**************************************************************************************************
 * end tests
**************************************************************************************************/

	gettimeofday(&time_end, NULL);
	output.close();
	output.open("performances/" + filename);
	output << time_end.tv_sec - time_start.tv_sec + 1e-6 * (time_end.tv_usec - time_start.tv_usec);
}
