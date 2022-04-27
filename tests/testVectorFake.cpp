
#include <vector>
#include <time.h>
#include <sys/time.h>

#include "vector.hpp"
#include "tests.hpp"

template<typename T>
int		ft_compare(const ft::vector<T> &ft, const std::vector<T> &std)
{
	for (unsigned long i = 0; i < std.size() ; i++)
	{
		if (std.at(i) != ft.at(i))
		{
			std::cout << "\033[1;31m\t\tERROR: there are difference: \033[0m\n";
			std::cout << "my data = " << ft.at(i) << " std_data = " << std.at(1) << std::endl;
			exit(EXIT_FAILURE);
		}
	}
	return (0);
}

/**************************************************************************************************
***************************************************************************************************
**************************************************************************************************/
float 	time_diff(struct timeval *start, struct timeval *end)
{
	return ((end->tv_sec - start->tv_sec) + 1e-6*(end->tv_usec - start->tv_usec));
}

/**************************************************************************************************
***************************************************************************************************
**************************************************************************************************/
int		ft_test_at()
{
	std::cout << std::endl;
	std::cout << "\033[1;34mTesting function AT() for vectors:\033[0m\n";

	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
	// FT >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

	struct timeval ft_start;
	struct timeval ft_end;
	gettimeofday(&ft_start, NULL);

	ft::vector<int> my_data;
	for (int i = 0; i < 10; i++)
		my_data.push_back(i);
	my_data.at(1) = 88;
	std::cout << "mydata(2) = " << my_data.at(2) << std::endl;
	std::cout << "size = " << my_data.size() << std::endl;
	try {
		my_data.at(-1) = 666;
	} catch (std::out_of_range const &exc) {
		std::cout << exc.what() << '\n';
	}
	try {
		my_data.at(500) = -666;
	} catch (std::out_of_range const &exc) {
		std::cout << exc.what() << '\n';
	}
	
	gettimeofday(&ft_end, NULL);
	std::cout << std::fixed << "TIME FT= " << time_diff(&ft_start, &ft_end) << std::endl;

	//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	// STD <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	
	struct timeval std_start;
	struct timeval std_end;
	gettimeofday(&std_start, NULL);

	std::vector<int> data;
	for (int i = 0; i < 10; i++)
		data.push_back(i);
	data.at(1) = 88;
	std::cout << "data(2) = " << data.at(2) << std::endl;
	std::cout << "size = " << data.size() << std::endl;
	try {
		data.at(-1) = 666;
	} catch (std::out_of_range const &exc) {
		std::cout << exc.what() << '\n';
	}
	try {
		data.at(500) = -666;
	} catch (std::out_of_range const &exc) {
		std::cout << exc.what() << '\n';
	}
	
	gettimeofday(&std_end, NULL);
	std::cout << std::fixed << "TIME STD= " << time_diff(&std_start, &std_end) << std::endl;
	
	///////////////////////////////////////////////////////
	// COMPARE ////////////////////////////////////////////
	///////////////////////////////////////////////////////

	if (time_diff(&std_start, &std_end) * 20 < time_diff(&ft_start, &ft_end))
	{
		std::cout << "\033[1;31m\t\tERROR: ft is too long: \033[0m\n";
		exit(EXIT_FAILURE);
	}
	else
		std::cout << "\033[1;32m\t\tPERFECT ! ft is not too long.\033[0m" << std::endl;

	ft_compare(my_data, data);
	std::cout << "\033[1;32m\t\tPERFECT ! No difference with AT() function.\033[0m" << std::endl;

	return (0);
}

/**************************************************************************************************
***************************************************************************************************
**************************************************************************************************/
int		ft_test_operator()
{
	std::cout << std::endl;
	std::cout << "\033[1;34mTesting function OPERATOR[] for vectors:\033[0m\n";

	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
	// FT >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

	struct timeval ft_start;
	struct timeval ft_end;
	gettimeofday(&ft_start, NULL);

	ft::vector<int> myvector (10);   // 10 zero-initialized elements
	ft::vector<int>::size_type sz = myvector.size();
	// assign some values:
	for (unsigned i=0; i<sz; i++) myvector[i]=i;
	// reverse vector using operator[]:
	for (unsigned i=0; i<sz/2; i++)
	{
		int temp;
    	temp = myvector[sz-1-i];
    	myvector[sz-1-i]=myvector[i];
    	myvector[i]=temp;
  	}
	std::cout << "myvector contains:";
	for (unsigned i=0; i<sz; i++)
    	std::cout << ' ' << myvector[i];
  	std::cout << '\n';
	 
	gettimeofday(&ft_end, NULL);
	std::cout << std::fixed << "TIME FT= " << time_diff(&ft_start, &ft_end) << std::endl;

	
	struct timeval std_start;
	struct timeval std_end;
	gettimeofday(&std_start, NULL);

	//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	// STD <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

	std::vector<int> std_vector (10);   // 10 zero-initialized elements
	std::vector<int>::size_type std_sz = std_vector.size();
	// assign some values:
	for (unsigned i=0; i<std_sz; i++) std_vector[i]=i;
	// reverse vector using operator[]:
	for (unsigned i=0; i<std_sz/2; i++)
	{
		int temp;
    	temp = std_vector[std_sz-1-i];
    	std_vector[std_sz-1-i]=std_vector[i];
    	std_vector[i]=temp;
  	}
	std::cout << "std_vector contains:";
	for (unsigned i=0; i<std_sz; i++)
    	std::cout << ' ' << std_vector[i];
  	std::cout << '\n';
	 
	gettimeofday(&std_end, NULL);
	std::cout << std::fixed << "TIME STD= " << time_diff(&std_start, &std_end) << std::endl;
	
	///////////////////////////////////////////////////////
	// COMPARE ////////////////////////////////////////////
	///////////////////////////////////////////////////////

	if (time_diff(&std_start, &std_end) * 20 < time_diff(&ft_start, &ft_end))
	{
		std::cout << "\033[1;31m\t\tERROR: ft is too long: \033[0m\n";
		exit(EXIT_FAILURE);
	}
	else
		std::cout << "\033[1;32m\t\tPERFECT ! ft is not too long.\033[0m" << std::endl;

	ft_compare(myvector, std_vector);
	std::cout << "\033[1;32m\t\tPERFECT ! No difference with OPERATOR[] function.\033[0m" << std::endl;
	 
	return (0);
}

/**************************************************************************************************
***************************************************************************************************
**************************************************************************************************/
int		ft_front() 
{
	std::cout << std::endl;
	std::cout << "\033[1;34mTesting function FRONT() for vectors:\033[0m\n";

	 
	struct timeval ft_start;
	struct timeval ft_end;
	gettimeofday(&ft_start, NULL);

	ft::vector<int> myvector;
	myvector.push_back(78);
	myvector.push_back(16);
	// now front equals 78, and back 16
	myvector.front() -= myvector.back();
	std::cout << "myvector.front() is now " << myvector.front() << '\n';

	const std::vector<float> ftvector_const(2, 1.2);
	for (size_t i = 0; i < ftvector_const.size(); i++)
		std::cout << "const ftvector_const.front()" << ftvector_const.front() << std::endl;

	 
	gettimeofday(&ft_end, NULL);
	std::cout << std::fixed << "TIME FT= " << time_diff(&ft_start, &ft_end) << std::endl;

	
	struct timeval std_start;
	struct timeval std_end;
	gettimeofday(&std_start, NULL);
	 

	std::vector<int> stdvector;
	stdvector.push_back(78);
	stdvector.push_back(16);
	// now front equals 78, and back 16
	stdvector.front() -= stdvector.back();
	std::cout << "stdvector.front() is now " << stdvector.front() << '\n';
	
	const std::vector<float> stdvector_const(2, 1.2);
	for (size_t i = 0; i < stdvector_const.size(); i++)
		std::cout << "const std_vector.front()" << stdvector_const.front() << std::endl;
	// END FUNCTION == CHECK TIME AND ERROR
	gettimeofday(&std_end, NULL);
	std::cout << std::fixed << "TIME STD= " << time_diff(&std_start, &std_end) << std::endl;
	if (time_diff(&std_start, &std_end) * 20 < time_diff(&ft_start, &ft_end))
	{
		std::cout << "\033[1;31m\t\tERROR: ft is too long: \033[0m\n";
		exit(EXIT_FAILURE);
	}
	else
		std::cout << "\033[1;32m\t\tPERFECT ! ft is not too long.\033[0m" << std::endl;

	ft_compare(myvector, stdvector);
	std::cout << "\033[1;32m\t\tPERFECT ! No difference with FRONT[] function.\033[0m" << std::endl;
	 
	return (0);
}

/**************************************************************************************************
***************************************************************************************************
**************************************************************************************************/
int		ft_back()
{
	std::cout << std::endl;
	std::cout << "\033[1;34m\t\tTesting function BACK() for vectors:\033[0m\n";

	 

	struct timeval ft_start;
	struct timeval ft_end;
	gettimeofday(&ft_start, NULL);
	ft::vector<int> myvector;
	myvector.push_back(10);
	while (myvector.back() != 0)
    	myvector.push_back ( myvector.back() -1 );
	std::cout << "myvector contains:";
	for (unsigned i=0; i<myvector.size() ; i++)
    	std::cout << ' ' << myvector[i];
  	std::cout << '\n';

	const ft::vector<float> ftvector_const(2, 1.2);
	for (size_t i = 0; i < ftvector_const.size(); i++)
		std::cout << "const ftvector_const.back()" << ftvector_const.back() << std::endl;

	 
	gettimeofday(&ft_end, NULL);
	std::cout << std::fixed << "TIME FT= " << time_diff(&ft_start, &ft_end) << std::endl;

	
	struct timeval std_start;
	struct timeval std_end;
	gettimeofday(&std_start, NULL);
	 

	std::vector<int> stdvector;
	stdvector.push_back(10);
	while (stdvector.back() != 0)
    	stdvector.push_back ( stdvector.back() -1 );
	std::cout << "stdvector contains:";
	for (unsigned i=0; i<stdvector.size() ; i++)
    	std::cout << ' ' << stdvector[i];
  	std::cout << '\n';

	const std::vector<float> stdvector_const(2, 1.2);
	for (size_t i = 0; i < stdvector_const.size(); i++)
		std::cout << "const std_vector.back()" << stdvector_const.back() << std::endl;

	 
	
	// END FUNCTION == CHECK TIME AND ERROR
	gettimeofday(&std_end, NULL);
	std::cout << std::fixed << "TIME STD= " << time_diff(&std_start, &std_end) << std::endl;
	if (time_diff(&std_start, &std_end) * 20 < time_diff(&ft_start, &ft_end))
	{
		std::cout << "\033[1;31m\t\tERROR: ft is too long: \033[0m\n";
		exit(EXIT_FAILURE);
	}
	else
		std::cout << "\033[1;32m\t\tPERFECT ! ft is not too long.\033[0m" << std::endl;
	ft_compare(myvector, stdvector);
	ft_compare(ftvector_const, stdvector_const);
	std::cout << "\033[1;32m\t\tPERFECT ! No difference with BACK[] function.\033[0m" << std::endl;
	 
	return (0);
}

/**************************************************************************************************
***************************************************************************************************
**************************************************************************************************/
int		ft_assign()
{
	std::cout << std::endl;
	std::cout << "\033[1;34m\t\tTesting function ASSIGN() for vectors:\033[0m\n";

	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
	// FT >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

	struct timeval ft_start;
	struct timeval ft_end;
	gettimeofday(&ft_start, NULL);

	ft::vector<int> ft_first;
	ft::vector<int> ft_second;
  	ft::vector<int> ft_third;
	ft_first.assign (7,100);
	ft::vector<int>::iterator it;
	it=ft_first.begin()+1;
	ft_second.assign (it, ft_first.end()-1); // the 5 central values of first
	int myints[] = {1776,7,4};
	ft_third.assign (myints,myints+3);   // assigning from array.
	std::cout << "Size of first: " << int (ft_first.size()) << '\n';
	std::cout << "Size of second: " << int (ft_second.size()) << '\n';
	std::cout << "Size of third: " << int (ft_third.size()) << '\n';

	gettimeofday(&ft_end, NULL);
	std::cout << std::fixed << "TIME FT= " << time_diff(&ft_start, &ft_end) << std::endl;
	 
	//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	// STD <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	
	struct timeval std_start;
	struct timeval std_end;
	gettimeofday(&std_start, NULL);

	std::vector<int> std_first;
	std::vector<int> std_second;
  	std::vector<int> std_third;
	std_first.assign(7, 100);
	std::vector<int>::iterator it_std;
	it_std=std_first.begin()+1;
	std_second.assign (it_std, std_first.end()-1); // the 5 central values of first
	int stdints[] = {1776,7,4};
	std_third.assign (stdints, stdints + 3);   // assigning from array.
	std::cout << "Size of first: " << int (std_first.size()) << '\n';
	std::cout << "Size of second: " << int (std_second.size()) << '\n';
	std::cout << "Size of third: " << int (std_third.size()) << '\n';

	gettimeofday(&std_end, NULL);
	std::cout << std::fixed << "TIME STD= " << time_diff(&std_start, &std_end) << std::endl;
	
	///////////////////////////////////////////////////////
	// COMPARE ////////////////////////////////////////////
	///////////////////////////////////////////////////////

	if (time_diff(&std_start, &std_end) * 20 < time_diff(&ft_start, &ft_end))
	{
		std::cout << "\033[1;31m\t\tERROR: ft is too long: \033[0m\n";
		exit(EXIT_FAILURE);
	}
	else
		std::cout << "\033[1;32m\t\tPERFECT ! ft is not too long.\033[0m" << std::endl;

	// END
	ft_compare(ft_first, std_first);
	ft_compare(ft_second, std_second);
	ft_compare(ft_third, std_third);
	std::cout << "\033[1;32m\t\tPERFECT ! No difference with ASSIGN() function.\033[0m" << std::endl;
	 
	return (0);
}

/**************************************************************************************************
***************************************************************************************************
**************************************************************************************************/
int		ft_push_back()
{
	std::cout << std::endl;
	std::cout << "\033[1;34m\t\tTesting function PUSH_BACK() for vectors:\033[0m\n";

	struct timeval ft_start;
	struct timeval ft_end;
	gettimeofday(&ft_start, NULL);
	// FT VECTOR
	ft::vector<int> myvector;
	int myint;
	std::cout << "Please enter some integers (enter 0 to end):\n";
	do {
    	std::cin >> myint;
    	myvector.push_back (myint);
  	} while (myint);
	std::cout << "myvector stores " << int(myvector.size()) << " numbers.\n\n";

	 

	ft::vector<std::string> my_letters;
    my_letters.push_back("abc");
    std::string s = "def";
    my_letters.push_back(s);
    std::cout << "vector holds: ";
    for (ft::vector<std::string>::iterator it = my_letters.begin() ; it != my_letters.end(); it++)
		std::cout << *it << std::endl;
    std::cout << "\nMoved-from string holds " << s << '\n';

	
	
	gettimeofday(&ft_end, NULL);
	std::cout << std::fixed << "TIME FT= " << time_diff(&ft_start, &ft_end) << std::endl;

	
	struct timeval std_start;
	struct timeval std_end;
	gettimeofday(&std_start, NULL);
	 

	// STD VECTOR
	std::vector<int> stdvector;
	int stdint;
	std::cout << "Please enter some integers (enter 0 to end):\n";
	do {
    	std::cin >> stdint;
    	stdvector.push_back (stdint);
  	} while (stdint);
	std::cout << "myvector stores " << int(stdvector.size()) << " numbers.\n\n";

	 

	std::vector<std::string> std_letters;
    std_letters.push_back("abc");
    std::string st = "def";
    std_letters.push_back(st);
    std::cout << "vector holds: ";
    for (std::vector<std::string>::iterator it_2 = std_letters.begin() ; it_2 != std_letters.end(); it_2++)
		std::cout << *it_2 << std::endl;
    std::cout << "\nMoved-from string holds " << st << '\n';


	// END FUNCTION == CHECK TIME AND ERROR
	gettimeofday(&std_end, NULL);
	std::cout << std::fixed << "TIME STD= " << time_diff(&std_start, &std_end) << std::endl;
	if (time_diff(&std_start, &std_end) * 20 < time_diff(&ft_start, &ft_end))
	{
		std::cout << "\033[1;31m\t\tERROR: ft is too long: \033[0m\n";
		exit(EXIT_FAILURE);
	}
	else
		std::cout << "\033[1;32m\t\tPERFECT ! ft is not too long.\033[0m" << std::endl;
	 

	// END
	ft_compare(myvector, stdvector);
	ft_compare(my_letters, std_letters);
	std::cout << "\033[1;32m\t\tPERFECT ! No difference with PUSH_BACK() function.\033[0m" << std::endl;
	 
	return (0);
}

/**************************************************************************************************
***************************************************************************************************
**************************************************************************************************/
int		ft_pop_back()
{
	std::cout << std::endl;
	std::cout << "\033[1;34m\t\tTesting function POP_BACK() for vectors:\033[0m\n";

	 
	struct timeval ft_start;
	struct timeval ft_end;
	gettimeofday(&ft_start, NULL);
	ft::vector<int> myvector;
	int sum (0);
	myvector.push_back (100);
	myvector.push_back (200);
	myvector.push_back (300);
	while (!myvector.empty())
	{
    	sum+=myvector.back();
    	myvector.pop_back();
  	}
	std::cout << "The elements of myvector add up to " << sum << '\n';

	 
	
	gettimeofday(&ft_end, NULL);
	std::cout << std::fixed << "TIME FT= " << time_diff(&ft_start, &ft_end) << std::endl;

	
	struct timeval std_start;
	struct timeval std_end;
	gettimeofday(&std_start, NULL);

	// STD VECTORS
	 

	std::vector<int> stdvector;
	int sum2 (0);
	stdvector.push_back (100);
	stdvector.push_back (200);
	stdvector.push_back (300);
	while (!stdvector.empty())
	{
    	sum2+=stdvector.back();
    	stdvector.pop_back();
  	}
	std::cout << "The elements of stdvector add up to " << sum2 << '\n';	 
	gettimeofday(&std_end, NULL);
	std::cout << std::fixed << "TIME STD= " << time_diff(&std_start, &std_end) << std::endl;
	if (time_diff(&std_start, &std_end) * 20 < time_diff(&ft_start, &ft_end))
	{
		std::cout << "\033[1;31m\t\tERROR: ft is too long: \033[0m\n";
		exit(EXIT_FAILURE);
	}
	else
		std::cout << "\033[1;32m\t\tPERFECT ! ft is not too long.\033[0m" << std::endl;

	// END
	ft_compare(myvector, stdvector);
	std::cout << "\033[1;32m\t\tPERFECT ! No difference with POP_BACK() function.\033[0m" << std::endl;
	 
	return (0);
}

/**************************************************************************************************
***************************************************************************************************
**************************************************************************************************/
int		ft_insert()
{
	std::cout << std::endl;
	std::cout << "\033[1;34m\t\tTesting function INSERT() for vectors:\033[0m\n";

	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
	// FT >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

	struct timeval ft_start;
	struct timeval ft_end;
	gettimeofday(&ft_start, NULL);

	ft::vector<int> ft_vector (3,100);
	ft::vector<int>::iterator it_ft;
	it_ft = ft_vector.begin();
	it_ft = ft_vector.insert ( it_ft , 200 );
	ft_vector.insert(it_ft, 2, 300);
	// "it_std" no longer valid, get a new one:
	it_ft = ft_vector.begin();
	ft::vector<int> anothervector_ft(2,400);
	ft_vector.insert(it_ft + 2, anothervector_ft.begin(), anothervector_ft.end());
	int myarray_ft [] = { 501,502,503 };
	ft_vector.insert(ft_vector.begin(), myarray_ft, myarray_ft+3 );
	std::cout << "ft_vector contains:";
	for (it_ft = ft_vector.begin(); it_ft < ft_vector.end(); it_ft++)
    	std::cout << ' ' << *it_ft;
	std::cout << '\n';
	
	gettimeofday(&ft_end, NULL);
	std::cout << std::fixed << "TIME FT= " << time_diff(&ft_start, &ft_end) << std::endl;

	//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	// STD <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	
	struct timeval std_start;
	struct timeval std_end;
	gettimeofday(&std_start, NULL);

	std::vector<int> std_vector (3,100);
	std::vector<int>::iterator it_std;
	it_std = std_vector.begin();
	it_std = std_vector.insert ( it_std , 200 );
	std_vector.insert (it_std,2,300);
	// "it_std" no longer valid, get a new one:
	it_std = std_vector.begin();
	std::vector<int> anothervector_std (2,400);
	std_vector.insert (it_std + 2, anothervector_std.begin(), anothervector_std.end());
	int myarray [] = { 501,502,503 };
	std_vector.insert (std_vector.begin(), myarray, myarray+3);
	std::cout << "std_vector contains:";
	for (it_std = std_vector.begin(); it_std < std_vector.end(); it_std++)
    	std::cout << ' ' << *it_std;
	std::cout << '\n';

	gettimeofday(&std_end, NULL);
	std::cout << std::fixed << "TIME STD= " << time_diff(&std_start, &std_end) << std::endl;
	
	///////////////////////////////////////////////////////
	// COMPARE ////////////////////////////////////////////
	///////////////////////////////////////////////////////

	if (time_diff(&std_start, &std_end) * 20 < time_diff(&ft_start, &ft_end))
	{
		std::cout << "\033[1;31m\t\tERROR: ft is too long: \033[0m\n";
		exit(EXIT_FAILURE);
	}
	else
		std::cout << "\033[1;32m\t\tPERFECT ! ft is not too long.\033[0m" << std::endl;

	ft_compare(ft_vector, std_vector);
	std::cout << "\033[1;32m\t\tPERFECT ! No difference with INSERT() function.\033[0m" << std::endl;
	 
	return (0);
}

/**************************************************************************************************
***************************************************************************************************
**************************************************************************************************/
int		ft_erase()
{
	std::cout << std::endl;
	std::cout << "\033[1;34m\t\tTesting function ERASE() for vectors:\033[0m\n";

	 
	struct timeval ft_start;
	struct timeval ft_end;
	gettimeofday(&ft_start, NULL);
	ft::vector<int> ft_vector;
	// set some values (from 1 to 10)
	for (int i=1; i<=10; i++) ft_vector.push_back(i);
	// erase the 6th element
	ft_vector.erase (ft_vector.begin()+5);
	// erase the first 3 elements:
	ft_vector.erase (ft_vector.begin(),ft_vector.begin()+3);
	std::cout << "myvector contains:";
	for (unsigned i=0; i<ft_vector.size(); ++i)
    	std::cout << ' ' << ft_vector[i];
	std::cout << '\n';

	 


	// STD VECTORS
	gettimeofday(&ft_end, NULL);
	std::cout << std::fixed << "TIME FT= " << time_diff(&ft_start, &ft_end) << std::endl;

	
	struct timeval std_start;
	struct timeval std_end;
	gettimeofday(&std_start, NULL); 

	std::vector<int> std_vector;
	// set some values (from 1 to 10)
	for (int i=1; i<=10; i++) std_vector.push_back(i);
	// erase the 6th element
	std_vector.erase (std_vector.begin()+5);
	// erase the first 3 elements:
	std_vector.erase (std_vector.begin(),std_vector.begin()+3);
	std::cout << "myvector contains:";
	for (unsigned i=0; i<std_vector.size(); ++i)
    	std::cout << ' ' << std_vector[i];
	std::cout << '\n';

	 
	gettimeofday(&std_end, NULL);
	std::cout << std::fixed << "TIME STD= " << time_diff(&std_start, &std_end) << std::endl;
	if (time_diff(&std_start, &std_end) * 20 < time_diff(&ft_start, &ft_end))
	{
		std::cout << "\033[1;31m\t\tERROR: ft is too long: \033[0m\n";
		exit(EXIT_FAILURE);
	}
	else
		std::cout << "\033[1;32m\t\tPERFECT ! ft is not too long.\033[0m" << std::endl;

	// END
	ft_compare(ft_vector, std_vector);
	std::cout << "\033[1;32m\t\tPERFECT ! No difference with ERASE() function.\033[0m" << std::endl;
	 
	return (0);
}

/**************************************************************************************************
***************************************************************************************************
**************************************************************************************************/
int		ft_swap()
{
		std::cout << std::endl;
	std::cout << "\033[1;34m\t\tTesting function SWAP() for vectors:\033[0m\n";

	 
	struct timeval ft_start;
	struct timeval ft_end;
	gettimeofday(&ft_start, NULL);

	ft::vector<int> ft_foo (3,100);   // three ints with a value of 100
	ft::vector<int> ft_bar (5,200);   // five ints with a value of 200
	ft_foo.swap(ft_bar);
  	std::cout << "foo contains:";
	for (unsigned i=0; i<ft_foo.size(); i++)
    	std::cout << ' ' << ft_foo[i];
	std::cout << '\n';
	std::cout << "bar contains:";
	for (unsigned i=0; i<ft_bar.size(); i++)
    	std::cout << ' ' << ft_bar[i];
	std::cout << '\n';

	 


	// STD VECTORS
	 
	gettimeofday(&ft_end, NULL);
	std::cout << std::fixed << "TIME FT= " << time_diff(&ft_start, &ft_end) << std::endl;

	
	struct timeval std_start;
	struct timeval std_end;
	gettimeofday(&std_start, NULL);
	std::vector<int> std_foo (3,100);   // three ints with a value of 100
	std::vector<int> std_bar (5,200);   // five ints with a value of 200
	std_foo.swap(std_bar);
  	std::cout << "foo contains:";
	for (unsigned i=0; i<std_foo.size(); i++)
    	std::cout << ' ' << std_foo[i];
	std::cout << '\n';
	std::cout << "bar contains:";
	for (unsigned i=0; i<std_bar.size(); i++)
    	std::cout << ' ' << std_bar[i];
	std::cout << '\n';
	gettimeofday(&std_end, NULL);
	std::cout << std::fixed << "TIME STD= " << time_diff(&std_start, &std_end) << std::endl;
	if (time_diff(&std_start, &std_end) * 20 < time_diff(&ft_start, &ft_end))
	{
		std::cout << "\033[1;31m\t\tERROR: ft is too long: \033[0m\n";
		exit(EXIT_FAILURE);
	}
	else
		std::cout << "\033[1;32m\t\tPERFECT ! ft is not too long.\033[0m" << std::endl;

	 

	// END
	ft_compare(ft_foo, std_foo);
	ft_compare(ft_bar, std_bar);
	std::cout << "\033[1;32m\t\tPERFECT ! No difference with SWAP() function.\033[0m" << std::endl;
	 
	return (0);
}

/**************************************************************************************************
***************************************************************************************************
**************************************************************************************************/
int		ft_clear()
{
	std::cout << std::endl;
	std::cout << "\033[1;34m\t\tTesting function CLEAR() for vectors:\033[0m\n";

	 
	struct timeval ft_start;
	struct timeval ft_end;
	gettimeofday(&ft_start, NULL);
	ft::vector<int> ft_vector;
	ft_vector.push_back (100);
	ft_vector.push_back (200);
	ft_vector.push_back (300);
	std::cout << "ft_vector contains:";
	for (unsigned i=0; i<ft_vector.size(); i++)
	    std::cout << ' ' << ft_vector[i];
	std::cout << '\n';
	std::cout << "ft_vector size: " << ft_vector.size() << std::endl;
	ft_vector.clear();
	std::cout << "ft_vector size: " << ft_vector.size() << std::endl;
	ft_vector.push_back (1101);
	ft_vector.push_back (2202);
	std::cout << "ft_vector contains:";
	for (unsigned i=0; i<ft_vector.size(); i++)
    	std::cout << ' ' << ft_vector[i];
	std::cout << '\n';	 
	gettimeofday(&ft_end, NULL);
	std::cout << std::fixed << "TIME FT= " << time_diff(&ft_start, &ft_end) << std::endl;

	
	struct timeval std_start;
	struct timeval std_end;
	gettimeofday(&std_start, NULL);

	// STD VECTORS
	 

	std::vector<int> std_vector;
	std_vector.push_back (100);
	std_vector.push_back (200);
	std_vector.push_back (300);
	std::cout << "std_vector contains:";
	for (unsigned i=0; i<std_vector.size(); i++)
	    std::cout << ' ' << std_vector[i];
	std::cout << '\n';
	std::cout << "std_vector size: " << std_vector.size() << std::endl;
	std_vector.clear();
	std::cout << "std_vector size: " << std_vector.size() << std::endl;
	std_vector.push_back (1101);
	std_vector.push_back (2202);
	std::cout << "std_vector contains:";
	for (unsigned i=0; i<std_vector.size(); i++)
    	std::cout << ' ' << std_vector[i];
	std::cout << '\n';


	gettimeofday(&std_end, NULL);
	std::cout << std::fixed << "TIME STD= " << time_diff(&std_start, &std_end) << std::endl;
	if (time_diff(&std_start, &std_end) * 20 < time_diff(&ft_start, &ft_end))
	{
		std::cout << "\033[1;31m\t\tERROR: ft is too long: \033[0m\n";
		exit(EXIT_FAILURE);
	}
	else
		std::cout << "\033[1;32m\t\tPERFECT ! ft is not too long.\033[0m" << std::endl;

 

	// END
	ft_compare(ft_vector, std_vector);
	std::cout << "\033[1;32m\t\tPERFECT ! No difference with CLEAR() function.\033[0m" << std::endl;
	 
	return (0);
}

/**************************************************************************************************
***************************************************************************************************
**************************************************************************************************/
int		ft_get_allocator()
{
	std::cout << std::endl;
	std::cout << "\033[1;34m\t\tTesting function GET_ALLOCATOR() for vectors:\033[0m\n";

	 
	struct timeval ft_start;
	struct timeval ft_end;
	gettimeofday(&ft_start, NULL);
  	ft::vector<int> ft_vector;
  	int * p;
  	unsigned int i;
  	// allocate an array with space for 5 elements using vector's allocator:
  	p = ft_vector.get_allocator().allocate(5);
  	// construct values in-place on the array:
  	for (i=0; i<5; i++) ft_vector.get_allocator().construct(&p[i],i);
  	std::cout << "The allocated array  ft_vector contains:";
  	for (i=0; i<5; i++) std::cout << ' ' << p[i];
		std::cout << '\n';
	// destroy and deallocate:
	for (i=0; i<5; i++) ft_vector.get_allocator().destroy(&p[i]);
		ft_vector.get_allocator().deallocate(p,5);	 
	gettimeofday(&ft_end, NULL);
	std::cout << std::fixed << "TIME FT= " << time_diff(&ft_start, &ft_end) << std::endl;

	
	struct timeval std_start;
	struct timeval std_end;
	gettimeofday(&std_start, NULL);

	// STD VECTORS
	 

  	std::vector<int> std_vector;
  	int * pt;
  	unsigned int i_s;
  	// allocate an array with space for 5 elements using vector's allocator:
  	pt = std_vector.get_allocator().allocate(5);
  	// construct values in-place on the array:
  	for (i_s=0; i_s<5; i_s++) std_vector.get_allocator().construct(&pt[i_s],i_s);
  	std::cout << "The allocated array std_vector contains:";
  	for (i_s=0; i_s<5; i_s++) std::cout << ' ' << pt[i_s];
		std::cout << '\n';
	// destroy and deallocate:
	for (i_s=0; i_s<5; i_s++) std_vector.get_allocator().destroy(&pt[i_s]);
		std_vector.get_allocator().deallocate(pt,5);

		gettimeofday(&std_end, NULL);
	std::cout << std::fixed << "TIME STD= " << time_diff(&std_start, &std_end) << std::endl;
	if (time_diff(&std_start, &std_end) * 20 < time_diff(&ft_start, &ft_end))
	{
		std::cout << "\033[1;31m\t\tERROR: ft is too long: \033[0m\n";
		exit(EXIT_FAILURE);
	}
	else
		std::cout << "\033[1;32m\t\tPERFECT ! ft is not too long.\033[0m" << std::endl;



	// END
	ft_compare(ft_vector, std_vector);
	std::cout << "\033[1;32m\t\tPERFECT ! No difference with GET_ALLOCATOR() function.\033[0m" << std::endl;
	 
	return (0);
}

/**************************************************************************************************
***************************************************************************************************
**************************************************************************************************/
int		ft_size()
{
	std::cout << std::endl;
	std::cout << "\033[1;34m\t\tTesting function SIZE() for vectors:\033[0m\n";

	 

	struct timeval ft_start;
	struct timeval ft_end;
	gettimeofday(&ft_start, NULL);

	ft::vector<int> ft_vector;
  	std::cout << "0. size: " << ft_vector.size() << '\n';
  	for (int i=0; i<10; i++) ft_vector.push_back(i);
	  	std::cout << "1. size: " << ft_vector.size() << '\n';
  	ft_vector.insert (ft_vector.end(),10,100);
  	std::cout << "2. size: " << ft_vector.size() << '\n';
  	ft_vector.pop_back();
  	std::cout << "3. size: " << ft_vector.size() << '\n';

		 


	// STD VECTORS
	 	gettimeofday(&ft_end, NULL);
	std::cout << std::fixed << "TIME FT= " << time_diff(&ft_start, &ft_end) << std::endl;

	
	struct timeval std_start;
	struct timeval std_end;
	gettimeofday(&std_start, NULL);


	std::vector<int> std_vector;
  	std::cout << "0. size: " << std_vector.size() << '\n';
  	for (int i=0; i<10; i++) std_vector.push_back(i);
	  	std::cout << "1. size: " << std_vector.size() << '\n';
  	std_vector.insert (std_vector.end(),10,100);
  	std::cout << "2. size: " << std_vector.size() << '\n';
  	std_vector.pop_back();
  	std::cout << "3. size: " << std_vector.size() << '\n';

		gettimeofday(&std_end, NULL);
	std::cout << std::fixed << "TIME STD= " << time_diff(&std_start, &std_end) << std::endl;
	if (time_diff(&std_start, &std_end) * 20 < time_diff(&ft_start, &ft_end))
	{
		std::cout << "\033[1;31m\t\tERROR: ft is too long: \033[0m\n";
		exit(EXIT_FAILURE);
	}
	else
		std::cout << "\033[1;32m\t\tPERFECT ! ft is not too long.\033[0m" << std::endl;
	 

	// END
	ft_compare(ft_vector, std_vector);
	std::cout << "\033[1;32m\t\tPERFECT ! No difference with SIZE() function.\033[0m" << std::endl;
	 
	return (0);
}

/**************************************************************************************************
***************************************************************************************************
**************************************************************************************************/
int		ft_max_size()
{
	std::cout << std::endl;
	std::cout << "\033[1;34m\t\tTesting function MAX_SIZE() for vectors:\033[0m\n";

	 

	struct timeval ft_start;
	struct timeval ft_end;
	gettimeofday(&ft_start, NULL);
	ft::vector<float> ft_vector;
	// set some content in the vector:
  	for (int i=0; i<100; i++) ft_vector.push_back(i);
	std::cout << "ft_vector size: " << ft_vector.size() << "\n";
  	std::cout << "ft_vector capacity: " << ft_vector.capacity() << "\n";
  	std::cout << "ft_vector max_size: " << ft_vector.max_size() << "\n";


		 
	gettimeofday(&ft_end, NULL);
	std::cout << std::fixed << "TIME FT= " << time_diff(&ft_start, &ft_end) << std::endl;

	
	struct timeval std_start;
	struct timeval std_end;
	gettimeofday(&std_start, NULL);

	// STD VECTORS
	 

	std::vector<float> std_vector;
	// set some content in the vector:
  	for (int i=0; i<100; i++) std_vector.push_back(i);
	std::cout << "std_vector size: " << std_vector.size() << "\n";
  	std::cout << "std_vector capacity: " << std_vector.capacity() << "\n";
  	std::cout << "std_vector max_size: " << std_vector.max_size() << "\n";

		 
	gettimeofday(&std_end, NULL);
	std::cout << std::fixed << "TIME STD= " << time_diff(&std_start, &std_end) << std::endl;
	if (time_diff(&std_start, &std_end) * 20 < time_diff(&ft_start, &ft_end))
	{
		std::cout << "\033[1;31m\t\tERROR: ft is too long: \033[0m\n";
		exit(EXIT_FAILURE);
	}
	else
		std::cout << "\033[1;32m\t\tPERFECT ! ft is not too long.\033[0m" << std::endl;

	// END
	ft_compare(ft_vector, std_vector);
	std::cout << "\033[1;32m\t\tPERFECT ! No difference with MAX_SIZE() function.\033[0m" << std::endl;
	 
	return (0);
}

/**************************************************************************************************
***************************************************************************************************
**************************************************************************************************/
int		ft_resize()
{
	std::cout << std::endl;
	std::cout << "\033[1;34m\t\tTesting function RESIZE() for vectors:\033[0m\n";

	 
	struct timeval ft_start;
	struct timeval ft_end;
	gettimeofday(&ft_start, NULL);
	ft::vector<int> ft_vector;
	ft_vector.push_back(1);
	ft_vector.push_back(2);
	ft_vector.push_back(3);
    std::cout << "The ft_vector holds: ";
    for (ft::vector<int>::iterator it = ft_vector.begin(); it != ft_vector.end(); ++it)
		std::cout << "it =" << *it << std::endl;
    ft_vector.resize(5);
    std::cout << "After resize up to 5: ";
    for (ft::vector<int>::iterator it = ft_vector.begin(); it != ft_vector.end(); ++it)
		std::cout << "it =" << *it << std::endl;
    std::cout << '\n';
    ft_vector.resize(2);
    std::cout << "After resize down to 2: ";
   for (ft::vector<int>::iterator it = ft_vector.begin(); it != ft_vector.end(); ++it)
		std::cout << "it =" << *it << std::endl;
    std::cout << '\n';
	ft_vector.resize(6, 4);
    std::cout << "After resize up to 6 (initializer = 4): ";
    for (ft::vector<int>::iterator it = ft_vector.begin(); it != ft_vector.end(); ++it)
		std::cout << "it =" << *it << std::endl;
    std::cout << '\n';


	ft::vector<int> ft_vector2;
	// set some initial content:
  	for (int i=1; i < 100;i++) ft_vector2.push_back(i);
	ft_vector2.resize(5);
	ft_vector2.resize(50,100);
  	ft_vector2.resize(25);
	std::cout << "ft_vector2 contains:";
  	for (size_t i=0;i< ft_vector2.size();i++)
    	std::cout << ' ' << ft_vector2[i];
  	std::cout << '\n';

		 
	gettimeofday(&ft_end, NULL);
	std::cout << std::fixed << "TIME FT= " << time_diff(&ft_start, &ft_end) << std::endl;

	
	struct timeval std_start;
	struct timeval std_end;
	gettimeofday(&std_start, NULL);


	// STD VECTORS
	 

	std::vector<int> std_vector;
	std_vector.push_back(1);
	std_vector.push_back(2);
	std_vector.push_back(3);
    std::cout << "The std_vector holds: ";
    for (std::vector<int>::iterator it_2 = std_vector.begin(); it_2 != std_vector.end(); ++it_2)
		std::cout << "it =" << *it_2 << std::endl;
    std::cout << '\n';
    std_vector.resize(5);
    std::cout << "After resize up to 5: ";
    for (std::vector<int>::iterator it_2 = std_vector.begin(); it_2 != std_vector.end(); ++it_2)
		std::cout << "it =" << *it_2 << std::endl;
    std::cout << '\n';
    std_vector.resize(2);
    std::cout << "After resize down to 2: ";
    for (std::vector<int>::iterator it_2 = std_vector.begin(); it_2 != std_vector.end(); ++it_2)
		std::cout << "it =" << *it_2 << std::endl;
    std::cout << '\n';
	std_vector.resize(6, 4);
	std::cout << "After resize up to 6 (initializer = 4): ";
    for (std::vector<int>::iterator it_2 = std_vector.begin(); it_2 != std_vector.end(); ++it_2)
		std::cout << "it =" << *it_2 << std::endl;
    std::cout << '\n';


	std::vector<int> std_vector2;
	// set some initial content:
  	for (int i=1; i < 100;i++) std_vector2.push_back(i);
	std_vector2.resize(5);
	std_vector2.resize(50,100);
  	std_vector2.resize(25);
	std::cout << "std_vector2 contains:";
  	for (size_t i=0;i< std_vector2.size();i++)
    	std::cout << ' ' << std_vector2[i];
  	std::cout << '\n';

		 
	// END FUNCTION == CHECK TIME AND ERROR
	gettimeofday(&std_end, NULL);
	std::cout << std::fixed << "TIME STD= " << time_diff(&std_start, &std_end) << std::endl;
	if (time_diff(&std_start, &std_end) * 20 < time_diff(&ft_start, &ft_end))
	{
		std::cout << "\033[1;31m\t\tERROR: ft is too long: \033[0m\n";
		exit(EXIT_FAILURE);
	}
	else
		std::cout << "\033[1;32m\t\tPERFECT ! ft is not too long.\033[0m" << std::endl;

	// END
	ft_compare(ft_vector, std_vector);
	ft_compare(ft_vector2, std_vector2);
	std::cout << "\033[1;32m\t\tPERFECT ! No difference with RESIZE() function.\033[0m" << std::endl;
	 
	return (0);
}

/**************************************************************************************************
***************************************************************************************************
**************************************************************************************************/
int		ft_capacity()
{
	std::cout << std::endl;
	std::cout << "\033[1;34m\t\tTesting function CAPACITY() for vectors:\033[0m\n";

	 
	struct timeval ft_start;
	struct timeval ft_end;
	gettimeofday(&ft_start, NULL);
	ft::vector<int> ft_vector;
  	// set some content in the vector:
  	for (int i=0; i<100; i++) ft_vector.push_back(i);
  	std::cout << "capacity: " << (int) ft_vector.capacity() << '\n';
  	int sz = 200;
    ft::vector<int> ft_vector2;
    size_t cap = ft_vector2.capacity();
    std::cout << "ft_vector2 capacity = " << cap << '\n';
    for (int n = 0; n < sz; ++n) {
        ft_vector2.push_back(n);
        if (cap != ft_vector2.capacity()) {
            cap = ft_vector2.capacity();
            std::cout << "new capacity = " << cap << '\n';
        }
    }
    std::cout << "final size = " << ft_vector2.size() << '\n';
    std::cout << "final capacity = " << ft_vector2.capacity() << '\n';

	 

	gettimeofday(&ft_end, NULL);
	std::cout << std::fixed << "TIME FT= " << time_diff(&ft_start, &ft_end) << std::endl;

	
	struct timeval std_start;
	struct timeval std_end;
	gettimeofday(&std_start, NULL);
	// STD VECTORS
	 

	std::vector<int> std_vector;
  	// set some content in the vector:
  	for (int i=0; i<100; i++) std_vector.push_back(i);
  	std::cout << "capacity: " << (int) std_vector.capacity() << '\n';
  	int i = 200;
    std::vector<int> std_vector2;
    size_t cap2 = std_vector2.capacity();
    std::cout << "std_vector2 capacity = " << cap2 << '\n';
    for (int n = 0; n < i; ++n) {
        std_vector2.push_back(n);
        if (cap2 != std_vector2.capacity()) {
            cap2 = std_vector2.capacity();
            std::cout << "new capacity = " << cap2 << '\n';
        }
    }
    std::cout << "final size = " << std_vector2.size() << '\n';
    std::cout << "final capacity = " << std_vector2.capacity() << '\n';

		 
	// END FUNCTION == CHECK TIME AND ERROR
	gettimeofday(&std_end, NULL);
	std::cout << std::fixed << "TIME STD= " << time_diff(&std_start, &std_end) << std::endl;
	if (time_diff(&std_start, &std_end) * 20 < time_diff(&ft_start, &ft_end))
	{
		std::cout << "\033[1;31m\t\tERROR: ft is too long: \033[0m\n";
		exit(EXIT_FAILURE);
	}
	else
		std::cout << "\033[1;32m\t\tPERFECT ! ft is not too long.\033[0m" << std::endl;


	// END
	ft_compare(ft_vector, std_vector);
	ft_compare(ft_vector2, std_vector2);
	std::cout << "\033[1;32m\t\tPERFECT ! No difference with CAPACITY() function.\033[0m" << std::endl;
	 
	return (0);
}

/**************************************************************************************************
***************************************************************************************************
**************************************************************************************************/
int		ft_empty()
{
	std::cout << std::endl;
	std::cout << "\033[1;34m\t\tTesting function EMPTY() for vectors:\033[0m\n";

	struct timeval ft_start;
	struct timeval ft_end;
	gettimeofday(&ft_start, NULL);

    std::cout << std::boolalpha;
    ft::vector<char> ft_vector;
    std::cout << "ft_vector, numbers.empty(): " << ft_vector.empty() << '\n';
    ft_vector.push_back('a');
    std::cout << "After adding elements, numbers.empty(): " << ft_vector.empty() << '\n';
	ft::vector<int> ft_vector2;
  	int sum (0);
	for (int i=1;i<=10;i++)
		ft_vector2.push_back(i);
	while (!ft_vector2.empty())
  	{
     	sum += ft_vector2.back();
     	ft_vector2.pop_back();
  	}
  	std::cout << "total: " << sum << '\n';

		 

	gettimeofday(&ft_end, NULL);
	std::cout << std::fixed << "TIME FT= " << time_diff(&ft_start, &ft_end) << std::endl;

	
	struct timeval std_start;
	struct timeval std_end;
	gettimeofday(&std_start, NULL);
	// STD VECTORS
	 

	std::cout << std::boolalpha;
    std::vector<char> std_vector;
    std::cout << "std_vector, numbers.empty(): " << std_vector.empty() << '\n';
    std_vector.push_back('a');
    std::cout << "After adding elements, numbers.empty(): " << std_vector.empty() << '\n';
	std::vector<int> std_vector2;
  	int sum2 (0);
	for (int i=1;i<=10;i++)
		std_vector2.push_back(i);
	while (!std_vector2.empty())
  	{
     	sum2 += std_vector2.back();
     	std_vector2.pop_back();
  	}
  	std::cout << "total: " << sum2 << '\n';

		 
	gettimeofday(&std_end, NULL);
	std::cout << std::fixed << "TIME STD= " << time_diff(&std_start, &std_end) << std::endl;
	if (time_diff(&std_start, &std_end) * 20 < time_diff(&ft_start, &ft_end))
	{
		std::cout << "\033[1;31m\t\tERROR: ft is too long: \033[0m\n";
		exit(EXIT_FAILURE);
	}
	else
		std::cout << "\033[1;32m\t\tPERFECT ! ft is not too long.\033[0m" << std::endl;



	// END
	ft_compare(ft_vector, std_vector);
	ft_compare(ft_vector2, std_vector2);
	std::cout << "\033[1;32m\t\tPERFECT ! No difference with EMPTY() function.\033[0m" << std::endl;
	 
	return (0);
}

/**************************************************************************************************
***************************************************************************************************
**************************************************************************************************/
int		ft_reserve()
{
	std::cout << std::endl;
	std::cout << "\033[1;34m\t\tTesting function RESERVE() for vectors:\033[0m\n";

	 

	struct timeval ft_start;
	struct timeval ft_end;
	gettimeofday(&ft_start, NULL);
  	ft::vector<int>::size_type ft_size;
  	ft::vector<int> ft_vector;
  	ft_size = ft_vector.capacity();
  	std::cout << "making foo grow:\n";
  	for (int i=0; i<100; ++i)
	{
    	ft_vector.push_back(i);
    	if (ft_size!=ft_vector.capacity())
		{
      		ft_size = ft_vector.capacity();
      		std::cout << "capacity changed: " << ft_size << '\n';
   		}
  	}
	ft::vector<int> ft_vector2;
  	ft_size = ft_vector2.capacity();
  	ft_vector2.reserve(100);   // this is the only difference with foo above
  	std::cout << "making ft_vector2 grow:\n";
  	for (int i=0; i<100; ++i)
	{
    	ft_vector2.push_back(i);
    	if (ft_size != ft_vector2.capacity())
		{
      		ft_size = ft_vector2.capacity();
      		std::cout << "capacity changed: " << ft_size << '\n';
    	}
  	}
   
		 
	gettimeofday(&ft_end, NULL);
	std::cout << std::fixed << "TIME FT= " << time_diff(&ft_start, &ft_end) << std::endl;

	
	struct timeval std_start;
	struct timeval std_end;
	gettimeofday(&std_start, NULL);


	// STD VECTORS
	 

  	std::vector<int>::size_type std_size;
  	std::vector<int> std_vector;
  	std_size = std_vector.capacity();
  	std::cout << "making foo grow:\n";
  	for (int i=0; i<100; ++i)
	{
    	std_vector.push_back(i);
    	if (std_size!=std_vector.capacity())
		{
      		std_size = std_vector.capacity();
      		std::cout << "capacity changed: " << std_size << '\n';
   		}
  	}
	std::vector<int> std_vector2;
  	std_size = std_vector2.capacity();
  	std_vector2.reserve(100);   // this is the only difference with foo above
  	std::cout << "making std_vector2 grow:\n";
  	for (int i=0; i<100; ++i)
	{
    	std_vector2.push_back(i);
    	if (std_size != std_vector2.capacity())
		{
      		std_size = std_vector2.capacity();
      		std::cout << "capacity changed: " << std_size << '\n';
    	}
  	}
	gettimeofday(&std_end, NULL);
	std::cout << std::fixed << "TIME STD= " << time_diff(&std_start, &std_end) << std::endl;
	if (time_diff(&std_start, &std_end) * 20 < time_diff(&ft_start, &ft_end))
	{
		std::cout << "\033[1;31m\t\tERROR: ft is too long: \033[0m\n";
		exit(EXIT_FAILURE);
	}
	else
		std::cout << "\033[1;32m\t\tPERFECT ! ft is not too long.\033[0m" << std::endl;



	

	// END
	ft_compare(ft_vector, std_vector);
	ft_compare(ft_vector2, std_vector2);
	std::cout << "\033[1;32m\t\tPERFECT ! No difference with RESERVE() function.\033[0m" << std::endl;
	 
	return (0);
}

/**************************************************************************************************
***************************************************************************************************
**************************************************************************************************/
int		ft_begin_end()
{
	std::cout << std::endl;
	std::cout << "\033[1;34m\t\tTesting functions BEGIN() and END() for vectors:\033[0m\n";

	 struct timeval ft_start;
	struct timeval ft_end;
	gettimeofday(&ft_start, NULL);

  	ft::vector<int> ft_vector;
  	for (int i=1; i<=5; i++)
	  	ft_vector.push_back(i);
	std::cout << "ft_vector contains with begin and end:";
  	for (ft::vector<int>::iterator it = ft_vector.begin() ; it != ft_vector.end(); ++it)
    	std::cout << ' ' << *it;
  	std::cout << '\n';
	// std::cout << "ft_vector contains without =" << ft_vector << std::endl;
	int sum = 0;
	for (ft::vector<int>::iterator it = ft_vector.begin(); it != ft_vector.end(); it++)
		sum += *it;
	std::cout << "Sum = " << sum << std::endl;

	std::cout << "Testing const begin and const end: " << std::endl;
	const ft::vector<int> ft_vector2(5, 42);
	for (ft::vector<int>::const_iterator it_const = ft_vector2.begin() ; it_const != ft_vector2.end(); ++it_const)
    	std::cout << ' ' << *it_const;
	std::cout << std::endl;
	
	// std::cout << std::endl;
		 


	// STD VECTORS
	 
	gettimeofday(&ft_end, NULL);
	std::cout << std::fixed<< "TIME FT= " << time_diff(&ft_start, &ft_end) << std::endl;

	
	struct timeval std_start;
	struct timeval std_end;
	gettimeofday(&std_start, NULL);
	std::vector<int> std_vector;
  	for (int i=1; i<=5; i++)
	  	std_vector.push_back(i);
	std::cout << "std_vector contains with begin and end:";
  	for (std::vector<int>::iterator it = std_vector.begin() ; it != std_vector.end(); ++it)
    	std::cout << ' ' << *it;
  	std::cout << '\n';
	// std::cout << "std_vector contains without =" << std_vector << std::endl;
	int sum2 = 0;
	for (std::vector<int>::iterator it = std_vector.begin(); it != std_vector.end(); it++)
		sum2 += *it;
	std::cout << "sum2 = " << sum2 << std::endl;

	std::cout << "Testing const begin and const end: " << std::endl;
	const std::vector<int> std_vector2(5, 42);
	for (std::vector<int>::const_iterator it_const2 = std_vector2.begin() ; it_const2 != std_vector2.end(); ++it_const2)
    	std::cout << ' ' << *it_const2;
	std::cout << std::endl;
	gettimeofday(&std_end, NULL);
	std::cout << std::fixed << "TIME STD= " << time_diff(&std_start, &std_end) << std::endl;
	if (time_diff(&std_start, &std_end) * 20 < time_diff(&ft_start, &ft_end))
	{
		std::cout << "\033[1;31m\t\tERROR: ft is too long: \033[0m\n";
		exit(EXIT_FAILURE);
	}
	else
		std::cout << "\033[1;32m\t\tPERFECT ! ft is not too long.\033[0m" << std::endl;




		 

	// END
	ft_compare(ft_vector, std_vector);
	ft_compare(ft_vector2, std_vector2);
	std::cout << "\033[1;32m\t\tPERFECT ! No difference with BEGIN() and END() functions.\033[0m" << std::endl;
	 
	return (0);
}

/**************************************************************************************************
***************************************************************************************************
**************************************************************************************************/
int		ft_rbegin_rend()
{
	std::cout << std::endl;
	std::cout << "\033[1;34m\t\tTesting function RBEGIN() and REND() for vectors:\033[0m\n";

		struct timeval ft_start;
	struct timeval ft_end;
	gettimeofday(&ft_start, NULL);
 

	ft::vector<int> ft_vector(5);  // 5 default-constructed ints
	// std::cout << "Apres init = " << ft_vector << std::endl;
	ft::vector<int>::reverse_iterator rit = ft_vector.rbegin();
	for (int y = 1; y <= 5; y++)
	{
		*rit = y;
		rit++;
	}
	std::cout << "ft_vector contains:";
  	for (ft::vector<int>::iterator it = ft_vector.begin(); it != ft_vector.end(); ++it)
    	std::cout << ' ' << *it;
	
  	std::cout << '\n';
	std::cout << "Testing const begin and const end: " << std::endl;
	ft::vector<int> ft_vector2(5, 42);
	for (ft::vector<int>::reverse_iterator it_const = ft_vector2.rbegin() ; it_const != ft_vector2.rend(); ++it_const)
    	std::cout << ' ' << *it_const;
	std::cout << std::endl;

	 


	// STD VECTORS
	 
	gettimeofday(&ft_end, NULL);
	std::cout << std::fixed << "TIME FT= " << time_diff(&ft_start, &ft_end) << std::endl;

	
	struct timeval std_start;
	struct timeval std_end;
	gettimeofday(&std_start, NULL);

	std::vector<int> std_vector(5);  // 5 default-constructed ints
	int i_std = 0;
	std::vector<int>::reverse_iterator reverse_std = std_vector.rbegin();
  	for (; reverse_std!= std_vector.rend(); ++reverse_std)
    	*reverse_std = ++i_std;
	std::cout << "std_vector contains:";
  	for (std::vector<int>::iterator it = std_vector.begin(); it != std_vector.end(); ++it)
    	std::cout << ' ' << *it;
  	std::cout << '\n';
	std::cout << "Testing const begin and const end: " << std::endl;
	std::vector<int> std_vector2(5, 42);
	for (std::vector<int>::reverse_iterator it_const2 = std_vector2.rbegin() ; it_const2 != std_vector2.rend(); ++it_const2)
    	std::cout << ' ' << *it_const2;
	std::cout << std::endl;
	// END FUNCTION == CHECK TIME AND ERROR
	gettimeofday(&std_end, NULL);
	std::cout << std::fixed << "TIME STD= " << time_diff(&std_start, &std_end) << std::endl;
	if (time_diff(&std_start, &std_end) * 20 < time_diff(&ft_start, &ft_end))
	{
		std::cout << "\033[1;31m\t\tERROR: ft is too long: \033[0m\n";
		exit(EXIT_FAILURE);
	}
	else
		std::cout << "\033[1;32m\t\tPERFECT ! ft is not too long.\033[0m" << std::endl;

	 

	// END
	ft_compare(ft_vector, std_vector);
	ft_compare(ft_vector2, std_vector2);
	std::cout << "\033[1;32m\t\tPERFECT ! No difference with RBEGIN() and REND() function.\033[0m" << std::endl;
	 
	return (0);
}

/**************************************************************************************************
***************************************************************************************************
**************************************************************************************************/
int		ft_construc_operator()
{
	std::cout << std::endl;
	std::cout << "\033[1;34m\t\tTesting CONSTRUCTOR() COPY CONSTRUCTOR() ASSIGNMENT OPERATOR() and DESTRUCTOR() for vectors:\033[0m\n";

	struct timeval ft_start;
	struct timeval ft_end;
	gettimeofday(&ft_start, NULL);
	{
		std::cout << "\033[1;33m\tTESTING ALL TYPES for FT\033[0m" << std::endl;
		std::cout << "unsigned char, ";
		ft::vector<unsigned char>				ft_vector8;
		std::cout << "signed char, ";
		ft::vector<signed char>					ft_vector3;
		std::cout << "unsigned short, ";
		ft::vector<unsigned short>				ft_vector18;
		std::cout << "unsigned short int, ";
		ft::vector<unsigned short int>			ft_vector9;
		std::cout << "signed short, ";
		ft::vector<signed short>				ft_vector19;
		std::cout << "signed short int, ";
		ft::vector<signed short int>			ft_vector4;
		std::cout << "unsigned int, ";
		ft::vector<unsigned int>				ft_vector10;
		std::cout << "signed char, ";
		ft::vector<signed int>					ft_vector5;
		std::cout << "unsigned long long, ";
		ft::vector<unsigned long long>			ft_vector20;
		std::cout << "signed long long, ";
		ft::vector<signed long long>			ft_vector21;
		std::cout << "wchar_t, ";
		ft::vector<wchar_t>						ft_vector2;
		std::cout << "signed long int, ";
		ft::vector<signed long int>				ft_vector6;
		std::cout << "signed long long int, ";
		ft::vector<signed long long int>		ft_vector7;
		std::cout << "unsigned long int, ";
		ft::vector<unsigned long int>			ft_vector11;
		std::cout << "unsigned long long int, ";
		ft::vector<unsigned long long int>		ft_vector12;
		std::cout << "float, ";
		ft::vector<float>						ft_vector13;
		std::cout << "double, ";
		ft::vector<double>						ft_vector14;
		std::cout << "long double, ";
		ft::vector<long double>					ft_vector15;
		std::cout << "bool, ";
		ft::vector<bool>						ft_vector16;
	}
	std::cout << "\033[1;33m\tTESTING constructors FT\033[0m" << std::endl;
	std::cout << "Init empty container with explicit constructor: ";
	ft::vector<std::string> words1;
	words1.push_back("the");
	words1.push_back("frogurt");
	words1.push_back("is");
	words1.push_back("also");
	words1.push_back("cursed");

 	std::cout << "Init container with range constructor (iterator): ";
    ft::vector<std::string> words2(words1.begin(), words1.end());

	std::cout << "Init container with copy constructor (same as the first one): ";
    ft::vector<std::string> words3(words1);

	std::cout << "Init container with fill constructor (5 times MO): ";
    ft::vector<std::string> words4(5, "Mo");

	std::cout << "Init container with operator =: ";
	ft::vector<std::string> words5;
	words5 = words4;

	std::cout << "Init container with new: ";
	std::vector<int> *words6 = new std::vector<int>;
	words6->push_back(-1);
	words6->push_back(-9);
	words6->push_back(-36);
	
	gettimeofday(&ft_end, NULL);
	std::cout << std::fixed << "TIME FT= " << time_diff(&ft_start, &ft_end) << std::endl;

	struct timeval std_start;
	struct timeval std_end;
	gettimeofday(&std_start, NULL);
	// STD VECTORS
	 
	{
		std::cout << "\033[1;33m\tTESTING ALL TYPES for STD\033[0m" << std::endl;
		std::cout << "unsigned char, ";
		std::vector<unsigned char>				std_vector8;
		std::cout << "signed char, ";
		std::vector<signed char>					std_vector3;
		std::cout << "unsigned short, ";
		std::vector<unsigned short>				std_vector18;
		std::cout << "unsigned short int, ";
		std::vector<unsigned short int>			std_vector9;
		std::cout << "signed short, ";
		std::vector<signed short>				std_vector19;
		std::cout << "signed short int, ";
		std::vector<signed short int>			std_vector4;
		std::cout << "unsigned int, ";
		std::vector<unsigned int>				std_vector10;
		std::cout << "signed char, ";
		std::vector<signed int>					std_vector5;
		std::cout << "unsigned long long, ";
		std::vector<unsigned long long>			std_vector20;
		std::cout << "signed long long, ";
		std::vector<signed long long>			std_vector21;
		std::cout << "wchar_t, ";
		std::vector<wchar_t>						std_vector2;
		std::cout << "signed long int, ";
		std::vector<signed long int>				std_vector6;
		std::cout << "signed long long int, ";
		std::vector<signed long long int>		std_vector7;
		std::cout << "unsigned long int, ";
		std::vector<unsigned long int>			std_vector11;
		std::cout << "unsigned long long int, ";
		std::vector<unsigned long long int>		std_vector12;
		std::cout << "float, ";
		std::vector<float>						std_vector13;
		std::cout << "double, ";
		std::vector<double>						std_vector14;
		std::cout << "long double, ";
		std::vector<long double>					std_vector15;
		std::cout << "bool, ";
		std::vector<bool>						std_vector16;
	}
	std::cout << std::endl;
	std::cout << "\033[1;33m\tTESTING constructors std\033[0m" << std::endl;
	std::cout << "Init empty container with explicit constructor: ";
	std::vector<std::string> std_words1;
	std_words1.push_back("the");
	std_words1.push_back("frogurt");
	std_words1.push_back("is");
	std_words1.push_back("also");
	std_words1.push_back("cursed");

 	std::cout << "Init container with range constructor (iterator): ";
    std::vector<std::string> std_words2(std_words1.begin(), std_words1.end());

	std::cout << "Init container with copy constructor (same as the first one): ";
    std::vector<std::string> std_words3(std_words1);

	std::cout << "Init container with fill constructor (5 times MO): ";
    std::vector<std::string> std_words4(5, "Mo");

	std::cout << "Init container with operator =: ";
	std::vector<std::string> std_words5;
	std_words5 = std_words4;

	std::cout << "Init container with new: ";
	std::vector<int> *std_words6 = new std::vector<int>;
	std_words6->push_back(-1);
	std_words6->push_back(-9);
	std_words6->push_back(-36);
	 
	gettimeofday(&std_end, NULL);
	std::cout << std::fixed << "TIME STD= " << time_diff(&std_start, &std_end) << std::endl;
	if (time_diff(&std_start, &std_end) * 20 < time_diff(&ft_start, &ft_end))
	{
		std::cout << "\033[1;31m\t\tERROR: ft is too long: \033[0m\n";
		exit(EXIT_FAILURE);
	}
	else
		std::cout << "\033[1;32m\t\tPERFECT ! ft is not too long.\033[0m" << std::endl;

	std::cout << std::endl;
	// END
	ft_compare(words1, std_words1);
	ft_compare(words2, std_words2);
	ft_compare(words3, std_words3);
	ft_compare(words4, std_words4);
	ft_compare(words5, std_words5);
	//ft_compare(words6, std_words6);
	for (int i = 0; i < 3 ; i++)
	{
		if (std_words6->at(i) != words6->at(i))
		{
			std::cout << "\033[1;31m\t\tERROR: there are difference: \033[0m\n";
			std::cout << "my data = " << words6->at(i) << " std_data = " << std_words6->at(1) << std::endl;
			exit(EXIT_FAILURE);
		}
	}
	std::cout << "\033[1;32m\t\tPERFECT ! No difference with CONSTRUCTOR() COPY CONSTRUCTOR() ASSIGNMENT OPERATOR() and DESTRUCTOR() function.\033[0m" << std::endl;

	delete std_words6;
	delete words6;
	return (0);
}

/**************************************************************************************************
***************************************************************************************************
**************************************************************************************************/
void 	ft_all()
{
	// Element access
	ft_test_at();
	ft_test_operator();
	ft_front();
	ft_back();

	// Modifiers
	ft_assign();
	ft_push_back();
	ft_pop_back();
	ft_insert();
	ft_erase();
	ft_swap();
	ft_clear();

	// Allocator
	ft_get_allocator();

	// Capacity
	ft_size();
	ft_max_size();
	ft_resize();
	ft_capacity();
	ft_empty();
	ft_reserve();

	// Iterators
	ft_begin_end();
	ft_rbegin_rend();

	//	Member functions
	ft_construc_operator();
	return ;
}

/**************************************************************************************************
***************************************************************************************************
**************************************************************************************************/
void	ft_display()
{
	std::cout << "\033[1;35m\t\tTESTS FOR VECTOR CONTAINER.\033[0m" << std::endl;
	std::cout << "\033[1;31mtype 1 for \tALL TESTS\033[0m" << std::endl;
	std::cout << "\033[1;32mtype 2 for \tELEMENT ACCESS (at - operator[] - front - back)\033[0m" << std::endl;
	std::cout << "\033[1;33mtype 3 for \tMODIFIERS (assign - push_back - pop_back - insert - erase - swap - clear)\033[0m" << std::endl;
	std::cout << "\033[1;34mtype 4 for \tALLOCATOR (get_allocator)\033[0m" << std::endl;
	std::cout << "\033[1;38mtype 5 for \tCAPACITY (size - max_size - resize - capacity - empty - reserve)\033[0m" << std::endl;
	std::cout << "\033[1;36mtype 6 for \tITERATOR (begin / end - rbegin / rend)\033[0m" << std::endl;
	std::cout << "\033[1;37;1mtype 7 for \tMEMBER FUNCTIONS (constructors - operator = ...)\033[0m" << std::endl;
	std::cout << "\033[1;31mtype 0 for \tEXIT\033[0m" << std::endl;
	std::cout << "\n\t\tyour answer < = ";
	return ;
}

/**************************************************************************************************
***************************************************************************************************
**************************************************************************************************/
int		main() 
{
	int		ret = 0;
	while (ret != -1)
	{
		std::cout << std::endl;
		ft_display();
		std::cin >> ret;
		if (ret == 1)
			ft_all();
		else if (ret == 2)
		{
			ft_test_at();
			ft_test_operator();
			ft_front();
			ft_back();
		}
		else if (ret == 3)
		{
			ft_assign();
			ft_push_back();
			ft_pop_back();
			ft_insert();
			ft_erase();
			ft_swap();
			ft_clear();
		}
		else if (ret == 4)
			ft_get_allocator();
		else if (ret == 5)
		{
			ft_size();
			ft_max_size();
			ft_resize();
			ft_capacity();
			ft_empty();
			ft_reserve();
		}
		else if (ret == 6)
		{
			ft_begin_end();
			ft_rbegin_rend();
		}
		else if (ret == 7)
			ft_construc_operator();
		else
			ret = -1;
	}
	return (0);
}
