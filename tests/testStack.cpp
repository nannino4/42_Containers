#include <string>
#include <stack>
#include <sys/time.h>

#include "tests.hpp"
#include "../containers/stack.hpp"

#define COUNT 10

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

testOutput testStack(std::string ns, const int seed)
{
	if (ns.compare("STD"))
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

	ft::stack<int> stack_int(ft::vector<int>(COUNT, 42));
	ft::stack<int> stack_int_copy(ft::vector<int>(COUNT, 42));
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
	ret.time = time_end.tv_sec - time_start.tv_sec + 1e-6 * (time_end.tv_usec - time_start.tv_usec);
	ret.output = output.str();
	return ret;
}