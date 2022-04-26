# include <iostream>
# include <stack>
# include <stdlib.h>
# include <vector>
# include <time.h>
# include <sys/time.h>

# include "stack.hpp"
# include "../Vector/vector.hpp"

template<typename T>
int		ft_compare(ft::stack<T> &ft, std::stack<T> &std)
{
	for (unsigned long i = 0; i < std.size();  i++)
	{
		if (std.top() != ft.top())
		{
			std::cout << "\033[1;31m\t\tERROR: there are difference: \033[0m\n";
			std::cout << "my data = " << ft.top() << " std_data = " << std.top() << std::endl;
			exit(EXIT_FAILURE);
		}
		ft.pop();
		std.pop();
	}
	return (0);
}

template<typename T>
int		ft_compare(ft::stack<T> *ft, std::stack<T> *std)
{
	for (unsigned long i = 0; i < std->size();  i++)
	{
		if (std->top() != ft->top())
		{
			std::cout << "\033[1;31m\t\tERROR: there are difference: \033[0m\n";
			std::cout << "my data = " << ft->top() << " std_data = " << std->top() << std::endl;
			exit(EXIT_FAILURE);
		}
		ft->pop();
		std->pop();
	}
	return (0);
}

float time_diff(struct timeval *start, struct timeval *end)
{
	return ((end->tv_sec - start->tv_sec) + 1e-6*(end->tv_usec - start->tv_usec));
}

int		ft_empty( void )
{
	std::cout << std::endl;
	std::cout << "\033[1;34m\t\tTesting function EMPTY() for stack:\033[0m\n";
	struct timeval ft_start;
	struct timeval ft_end;
	gettimeofday(&ft_start, NULL);
	std::cout << std::boolalpha;
    ft::stack<char> ft_stack;
    std::cout << "Initially, ft_stack.empty(): " << ft_stack.empty() << '\n';
    ft_stack.push('a');
    std::cout << "After adding elements, container.empty(): " << ft_stack.empty() << '\n';
	ft::stack<int> ft_stack2;
  	int sum (0);
	for (int i=1;i<=10;i++)
		ft_stack2.push(i);
	while (!ft_stack2.empty())
  	{
     	sum += ft_stack2.top();
     	ft_stack2.pop();
  	}
	std::cout << "total: " << sum << '\n';

	gettimeofday(&ft_end, NULL);
	std::cout << std::fixed << "TIME FT= " << time_diff(&ft_start, &ft_end) << std::endl;

	// STD stack
	struct timeval std_start;
	struct timeval std_end;
	gettimeofday(&std_start, NULL);

	std::cout << std::boolalpha;
    std::stack<char> std_stack;
    std::cout << "Initially, std_stack.empty(): " << std_stack.empty() << '\n';
    std_stack.push('a');
    std::cout << "After adding elements, container.empty(): " << std_stack.empty() << '\n';
	std::stack<int> std_stack2;
  	int sum2 (0);
	for (int i=1;i<=10;i++)
		std_stack2.push(i);
	while (!std_stack2.empty())
  	{
     	sum2 += std_stack2.top();
     	std_stack2.pop();
  	}
	std::cout << "total: " << sum2 << '\n';

	// END FUNCTION == CHECK TIME AND ERROR
	gettimeofday(&std_end, NULL);
	std::cout << "TIME STD= " << time_diff(&std_start, &std_end) << std::endl;
	if (time_diff(&std_start, &std_end) * 20 < time_diff(&ft_start, &ft_end))
	{
		std::cout << "\033[1;31m\t\tERROR: ft is too long: \033[0m\n";
		exit(EXIT_FAILURE);
	}
	else
		std::cout << "\033[1;32m\t\tPERFECT ! ft is not too long.\033[0m" << std::endl;

	ft_compare(ft_stack, std_stack);
	ft_compare(ft_stack2, std_stack2);
	std::cout << "\033[1;32m\t\tPERFECT ! No difference with EMPTY() function.\033[0m" << std::endl;
	 
	return (0);
}


int		ft_size( void )
{
	std::cout << std::endl;
	std::cout << "\033[1;34m\t\tTesting function SIZE() for stack:\033[0m\n";

	struct timeval ft_start;
	struct timeval ft_end;
	gettimeofday(&ft_start, NULL);
	ft::stack<int> ft_stack;
  	std::cout << "0. size: " << ft_stack.size() << '\n';
	for (int i=0; i<5; i++)
		ft_stack.push(i);
  	std::cout << "+5. size: " << ft_stack.size() << '\n';
	ft_stack.pop();
  	std::cout << "+5 - 1. size: " << ft_stack.size() << '\n';
	for (int i=0; i < 5000000; i++)
		ft_stack.push(i);
	std::cout << "+5000000. size: " << ft_stack.size() << '\n';

	gettimeofday(&ft_end, NULL);
	std::cout << std::fixed << "TIME FT= " << time_diff(&ft_start, &ft_end) << std::endl;

	// STD stack
	struct timeval std_start;
	struct timeval std_end;
	gettimeofday(&std_start, NULL);

	std::stack<int> std_stack;
  	std::cout << "0. size: " << std_stack.size() << '\n';
	for (int i=0; i<5; i++)
		std_stack.push(i);
  	std::cout << "+5. size: " << std_stack.size() << '\n';
	std_stack.pop();
  	std::cout << "+5 - 1. size: " << std_stack.size() << '\n';
	for (int i=0; i < 5000000; i++)
		std_stack.push(i);
	std::cout << "+5000000. size: " << std_stack.size() << '\n';
		 
	// END FUNCTION == CHECK TIME AND ERROR
	gettimeofday(&std_end, NULL);
	std::cout << "TIME STD= " << time_diff(&std_start, &std_end) << std::endl;
	if (time_diff(&std_start, &std_end) * 20 < time_diff(&ft_start, &ft_end))
	{
		std::cout << "\033[1;31m\t\tERROR: ft is too long: \033[0m\n";
		exit(EXIT_FAILURE);
	}
	else
		std::cout << "\033[1;32m\t\tPERFECT ! ft is not too long.\033[0m" << std::endl;

	// END
	ft_compare(ft_stack, std_stack);
	std::cout << "\033[1;32m\t\tPERFECT ! No difference with SIZE() function.\033[0m" << std::endl;
	return (0);
}





int		ft_top( void )
{
	std::cout << std::endl;
	std::cout << "\033[1;34m\t\tTesting function TOP() for stack:\033[0m\n";

	struct timeval ft_start;
	struct timeval ft_end;
	gettimeofday(&ft_start, NULL);
	ft::stack<std::string>	ft_stack;
	for (int i = 0; i < 5; i++)
		ft_stack.push("coucou toi =) ");
	ft_stack.top() = "Coucou Pierre =(";
	for (int i = 0; i < 5; i++)
	{
		std::cout << ft_stack.top() << std::endl;
		ft_stack.pop();
	}
	ft::stack<int> ft_stack2;
	ft_stack2.push(10);
	ft_stack2.push(20);
	ft_stack2.top() -= 5;
	std::cout << "ft_stack2.top() is now " << ft_stack2.top() << '\n';

	// STD stack
	gettimeofday(&ft_end, NULL);
	std::cout << std::fixed << "TIME FT= " << time_diff(&ft_start, &ft_end) << std::endl;

	
	struct timeval std_start;
	struct timeval std_end;
	gettimeofday(&std_start, NULL); 

	std::stack<std::string>	std_stack;
	for (int i = 0; i < 5; i++)
		std_stack.push("coucou toi =) ");
	std_stack.top() = "Coucou Pierre =(";
	for (int i = 0; i < 5; i++)
	{
		std::cout << std_stack.top() << std::endl;
		std_stack.pop();
	}
	std::stack<int> std_stack2;
	std_stack2.push(10);
	std_stack2.push(20);
	std_stack2.top() -= 5;
	std::cout << "std_stack2.top() is now " << std_stack2.top() << '\n';

	gettimeofday(&std_end, NULL);
	std::cout << "TIME STD= " << time_diff(&std_start, &std_end) << std::endl;
	if (time_diff(&std_start, &std_end) * 20 < time_diff(&ft_start, &ft_end))
	{
		std::cout << "\033[1;31m\t\tERROR: ft is too long: \033[0m\n";
		exit(EXIT_FAILURE);
	}
	else
		std::cout << "\033[1;32m\t\tPERFECT ! ft is not too long.\033[0m" << std::endl;
	// END
	ft_compare(ft_stack, std_stack);
	ft_compare(ft_stack2, std_stack2);
	std::cout << "\033[1;32m\t\tPERFECT ! No difference with TOP() function.\033[0m" << std::endl;
	return (0);
}

int		ft_push( void )
{
	std::cout << std::endl;
	std::cout << "\033[1;34m\t\tTesting function PUSH() for stack:\033[0m\n";

	struct timeval ft_start;
	struct timeval ft_end;
	gettimeofday(&ft_start, NULL);
 	ft::stack<int> ft_stack;
	std::cout << "Pushing in 527 int  elements...";
  	for (int i=0; i < 527; ++i)
	  	ft_stack.push(i);
	std::cout << "Popping out elements...";
  	while (!ft_stack.empty())
  	{
    	std::cout << ' ' << ft_stack.top();
     	ft_stack.pop();
  	}
  	std::cout << '\n';

	ft::stack<char> ft_stack2;
	char letter = 'a';
	std::cout << "Pushing in the letters...";
  	for (int i=0; i < 26; ++i)
	{
	  	ft_stack2.push(letter);
		letter++;
	}
	std::cout << "Popping out  10 elements...";
	int y = 0;
  	while (y < 10)
  	{
    	std::cout << ' ' << ft_stack2.top();
     	ft_stack2.pop();
		 y++;
  	}
  	std::cout << '\n';
	
	// STD stack
	gettimeofday(&ft_end, NULL);
	std::cout << std::fixed << "TIME FT= " << time_diff(&ft_start, &ft_end) << std::endl;

	struct timeval std_start;
	struct timeval std_end;
	gettimeofday(&std_start, NULL);

	std::stack<int> std_stack;
	std::cout << "Pushing in 527 int  elements...";
  	for (int i=0; i < 527; ++i)
	  	std_stack.push(i);
	std::cout << "Popping out elements...";
  	while (!std_stack.empty())
  	{
    	std::cout << ' ' << std_stack.top();
     	std_stack.pop();
  	}
  	std::cout << '\n';

	std::stack<char> std_stack2;
	char letter2 = 'a';
	std::cout << "Pushing in the letters...";
  	for (int i=0; i < 26; ++i)
	{
	  	std_stack2.push(letter2);
		letter2++;
	}
	std::cout << "Popping out  10 elements...";
	int i = 0;
  	while (i < 10)
  	{
    	std::cout << ' ' << std_stack2.top();
     	std_stack2.pop();
		 i++;
  	}
  	std::cout << '\n';

	// END FUNCTION == CHECK TIME AND ERROR
	gettimeofday(&std_end, NULL);
	std::cout << "TIME STD= " << time_diff(&std_start, &std_end) << std::endl;
	if (time_diff(&std_start, &std_end) * 20 < time_diff(&ft_start, &ft_end))
	{
		std::cout << "\033[1;31m\t\tERROR: ft is too long: \033[0m\n";
		exit(EXIT_FAILURE);
	}
	else
		std::cout << "\033[1;32m\t\tPERFECT ! ft is not too long.\033[0m" << std::endl;
	// END
	ft_compare(ft_stack, std_stack);
	ft_compare(ft_stack2, std_stack2);
	std::cout << "\033[1;32m\t\tPERFECT ! No difference with PUSH() function.\033[0m" << std::endl;
	return (0);
}



int		ft_pop( void )
{
	std::cout << std::endl;
	std::cout << "\033[1;34m\t\tTesting function POP() for stack:\033[0m\n";

	struct timeval ft_start;
	struct timeval ft_end;
	gettimeofday(&ft_start, NULL);
	ft::stack<float> ft_stack;
	std::cout << "Pushing in 50 elements...";
	for (float i = 0.5; i < 50; ++i)
		ft_stack.push(i);
  	std::cout << "Popping out 27 elements...";
	int i = 0;
	while (i < 27)
	{
		std::cout << ' ' << ft_stack.top();
		ft_stack.pop();
		i++;
	}
  	std::cout << '\n';
	std::cout << "Popping out 3 elements...";
	i = 0;
	while (i < 3)
	{
		std::cout << ' ' << ft_stack.top();
		ft_stack.pop();
		i++;
	}
  	std::cout << '\n';
	std::cout << "Popping out the last 20 elements...";
	i = 0;
	while (i < 20)
	{
		std::cout << ' ' << ft_stack.top();
		ft_stack.pop();
		i++;
	}
  	std::cout << '\n';	
		 
	// STD stack
	gettimeofday(&ft_end, NULL);
	std::cout << std::fixed << "TIME FT= " << time_diff(&ft_start, &ft_end) << std::endl;

	struct timeval std_start;
	struct timeval std_end;
	gettimeofday(&std_start, NULL);
	std::stack<float> std_stack;
	std::cout << "Pushing in 50 elements...";
	for (float i = 0.5; i < 50; ++i)
		std_stack.push(i);
  	std::cout << "Popping out 27 elements...";
	int y = 0;
	while (y < 27)
	{
		std::cout << ' ' << std_stack.top();
		std_stack.pop();
		y++;
	}
  	std::cout << '\n';
	  std::cout << '\n';
	std::cout << "Popping out 3 elements...";
	i = 0;
	while (i < 3)
	{
		std::cout << ' ' << std_stack.top();
		std_stack.pop();
		i++;
	}
  	std::cout << '\n';
	std::cout << "Popping out the last 20 elements...";
	i = 0;
	while (i < 20)
	{
		std::cout << ' ' << std_stack.top();
		std_stack.pop();
		i++;
	}
  	std::cout << '\n';
	
	gettimeofday(&std_end, NULL);
	std::cout << "TIME STD= " << time_diff(&std_start, &std_end) << std::endl;
	if (time_diff(&std_start, &std_end) * 20 < time_diff(&ft_start, &ft_end))
	{
		std::cout << "\033[1;31m\t\tERROR: ft is too long: \033[0m\n";
		exit(EXIT_FAILURE);
	}
	else
		std::cout << "\033[1;32m\t\tPERFECT ! ft is not too long.\033[0m" << std::endl;

	// END
	ft_compare(ft_stack, std_stack);
	std::cout << "\033[1;32m\t\tPERFECT ! No difference with POP() function.\033[0m" << std::endl; 
	return (0);
}

int		ft_constructor( void )
{
	std::cout << std::endl;
	std::cout << "\033[1;34m\t\tTesting constructor() for stack:\033[0m\n";

	struct timeval ft_start;
	struct timeval ft_end;
	gettimeofday(&ft_start, NULL);
	{
		std::cout << "\033[1;33m\tTESTING ALL TYPES for FT\033[0m" << std::endl;
		std::cout << "unsigned char, ";
		ft::stack<unsigned char>				ft_stack8;
		std::cout << "signed char, ";
		ft::stack<signed char>					ft_stack3;
		std::cout << "unsigned short, ";
		ft::stack<unsigned short>				ft_stack18;
		std::cout << "unsigned short int, ";
		ft::stack<unsigned short int>			ft_stack9;
		std::cout << "signed short, ";
		ft::stack<signed short>				ft_stack19;
		std::cout << "signed short int, ";
		ft::stack<signed short int>			ft_stack4;
		std::cout << "unsigned int, ";
		ft::stack<unsigned int>				ft_stack10;
		std::cout << "signed char, ";
		ft::stack<signed int>					ft_stack5;
		std::cout << "unsigned long long, ";
		ft::stack<unsigned long long>			ft_stack20;
		std::cout << "signed long long, ";
		ft::stack<signed long long>			ft_stack21;
		std::cout << "wchar_t, ";
		ft::stack<wchar_t>						ft_stack2;
		std::cout << "signed long int, ";
		ft::stack<signed long int>				ft_stack6;
		std::cout << "signed long long int, ";
		ft::stack<signed long long int>		ft_stack7;
		std::cout << "unsigned long int, ";
		ft::stack<unsigned long int>			ft_stack11;
		std::cout << "unsigned long long int, ";
		ft::stack<unsigned long long int>		ft_stack12;
		std::cout << "float, ";
		ft::stack<float>						ft_stack13;
		std::cout << "double, ";
		ft::stack<double>						ft_stack14;
		std::cout << "long double, ";
		ft::stack<long double>					ft_stack15;
		std::cout << "bool, ";
		ft::stack<bool>						ft_stack16;	
	}
	std::cout << "\033[1;33m\tTESTING constructors FT\033[0m" << std::endl;
	std::cout << "Init empty container with constructor: ";
	ft::stack<int> ft_first;                    // empty stack
	std::cout << "pushing severals int..." << std::endl;
	for (int i = 0; i < 5; i++)
		ft_first.push(i);
	std::cout << "size of ft_first: " << ft_first.size() << '\n';
	std::cout << "Init Copy constructor with stack: " << std::endl;
	ft::stack<int,ft::stack<int> > ft_copy(ft_first);
	std::cout << "size of ft_copy: " << ft_copy.size() << '\n';
	
	std::cout << "Init Copy constructor with vector 2 elements: " << std::endl;
	ft::vector<int> ft_vector (2,200);        // vector with 2 elements
	ft::stack<int,ft::vector<int> > ft_copy_vector(ft_vector);
	std::cout << "size of ft_copy_vector: " << ft_copy_vector.size() << '\n';

	std::cout << "Init operator assignement: " << std::endl;
	ft::stack<int> ft_assign;
	ft_assign = ft_first;
	std::cout << "size of ft_assign: " << ft_assign.size() << '\n';

	std::cout << "Init container with new: ";
	ft::stack<int> *ft_new = new ft::stack<int>;
	ft_new->push(1);
	ft_new->push(5);
	std::cout << "size of ft_new: " << ft_new->size() << '\n';

	// STD stack
	gettimeofday(&ft_end, NULL);
	std::cout << std::fixed << "TIME FT= " << time_diff(&ft_start, &ft_end) << std::endl;
	struct timeval std_start;
	struct timeval std_end;
	gettimeofday(&std_start, NULL);

	{
		std::cout << "\033[1;33m\tTESTING ALL TYPES for STD\033[0m" << std::endl;
		std::cout << "unsigned char, ";
		std::stack<unsigned char>				std_vector8;
		std::cout << "signed char, ";
		std::stack<signed char>					std_vector3;
		std::cout << "unsigned short, ";
		std::stack<unsigned short>				std_vector18;
		std::cout << "unsigned short int, ";
		std::stack<unsigned short int>			std_vector9;
		std::cout << "signed short, ";
		std::stack<signed short>				std_vector19;
		std::cout << "signed short int, ";
		std::stack<signed short int>			std_vector4;
		std::cout << "unsigned int, ";
		std::stack<unsigned int>				std_vector10;
		std::cout << "signed char, ";
		std::stack<signed int>					std_vector5;
		std::cout << "unsigned long long, ";
		std::stack<unsigned long long>			std_vector20;
		std::cout << "signed long long, ";
		std::stack<signed long long>			std_vector21;
		std::cout << "wchar_t, ";
		std::stack<wchar_t>						std_vector2;
		std::cout << "signed long int, ";
		std::stack<signed long int>				std_vector6;
		std::cout << "signed long long int, ";
		std::stack<signed long long int>		std_vector7;
		std::cout << "unsigned long int, ";
		std::stack<unsigned long int>			std_vector11;
		std::cout << "unsigned long long int, ";
		std::stack<unsigned long long int>		std_vector12;
		std::cout << "float, ";
		std::stack<float>						std_vector13;
		std::cout << "double, ";
		std::stack<double>						std_vector14;
		std::cout << "long double, ";
		std::stack<long double>					std_vector15;
		std::cout << "bool, ";
		std::stack<bool>						std_vector16;
	}
	std::cout << std::endl;
	std::cout << "\033[1;33m\tTESTING constructors STD\033[0m" << std::endl;
	std::cout << "Init empty container with constructor: ";
	std::stack<int> std_first;                    // empty stack
	std::cout << "pushing severals int..." << std::endl;
	for (int i = 0; i < 5; i++)
		std_first.push(i);
	std::cout << "size of std_first: " << std_first.size() << '\n';
	std::cout << "Init Copy constructor with stack: " << std::endl;
	std::stack<int,std::stack<int> > std_copy(std_first);
	std::cout << "size of std_copy: " << std_copy.size() << '\n';
	
	std::cout << "Init Copy constructor with vector 2 elements: " << std::endl;
	std::vector<int> std_vector (2,200);        // vector with 2 elements
	std::stack<int,std::vector<int> > std_copy_vector(std_vector);
	std::cout << "size of std_copy_vector: " << std_copy_vector.size() << '\n';

	std::cout << "Init operator assignement: " << std::endl;
	std::stack<int> std_assign;
	std_assign = std_first;
	std::cout << "size of ft_assign: " << std_assign.size() << '\n';

	std::cout << "Init container with new: ";
	std::stack<int> *std_new = new std::stack<int>;
	std_new->push(1);
	std_new->push(5);
	std::cout << "size of std_new: " << std_new->size() << '\n';
 
	gettimeofday(&std_end, NULL);
	std::cout << "TIME STD= " << time_diff(&std_start, &std_end) << std::endl;
	if (time_diff(&std_start, &std_end) * 20 < time_diff(&ft_start, &ft_end))
	{
		std::cout << "\033[1;31m\t\tERROR: ft is too long: \033[0m\n";
		exit(EXIT_FAILURE);
	}
	else
		std::cout << "\033[1;32m\t\tPERFECT ! ft is not too long.\033[0m" << std::endl;

	// END
	ft_compare(ft_first, std_first);
	ft_compare(ft_assign, std_assign);
	ft_compare(ft_new, std_new);
	delete std_new;
	delete ft_new;
	std::cout << "\033[1;32m\t\tPERFECT ! No difference with constructor() function.\033[0m" << std::endl;
	return (0);
}

void	ft_display( void )
{
	std::cout << "\033[1;35m\t\tTESTS FOR STACK CONTAINER.\033[0m" << std::endl;
	std::cout << "\033[1;31mtype 1 for \tALL TESTS\033[0m" << std::endl;
	std::cout << "\033[1;32mtype 2 for \tCAPACITY (empty - size)\033[0m" << std::endl;
	std::cout << "\033[1;33mtype 3 for \tELEMENT ACCESS (top)\033[0m" << std::endl;
	std::cout << "\033[1;34mtype 4 for \tMODIFIERS (push - pop)\033[0m" << std::endl;
	std::cout << "\033[1;37;1mtype 5 for \tMEMBER FUNCTIONS (constructors)\033[0m" << std::endl;
	std::cout << "\033[1;31mtype 0 for \tEXIT\033[0m" << std::endl;
	std::cout << "\n\t\tyour answer < = ";
	return ;
}


void		ft_all( void )
{
	// Capacity
	ft_empty();
	ft_size();

	// Element access
	ft_top();

	// Modifiers
	ft_push();
	ft_pop();

	// Constructor
	ft_constructor();
	return ;
}

int main() 
{
	int ret = 0;
	while ( ret != -1 )
	{
		std::cout << std::endl;
		ft_display();
		std::cin >> ret;
		if (ret == 1)
			ft_all();
		else if (ret == 2)
		{
			ft_empty();
			ft_size();
		}
		else if (ret == 3)
		{
			ft_top();
		}
		else if (ret == 4)
		{
			ft_push();
			ft_pop();
		}
		else if (ret == 5)
		{
			ft_constructor();
		}
		else
			ret = -1;

	}
	return (0);
}

