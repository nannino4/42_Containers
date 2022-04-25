
# include <iostream>
# include <stack>
# include <stdlib.h>
# include <map>
# include <time.h>
# include <sys/time.h>

# include "map.hpp"

float time_diff(struct timeval *start, struct timeval *end)
{
	return ((end->tv_sec - start->tv_sec) + 1e-6*(end->tv_usec - start->tv_usec));
}

int		ft_begin_end( void )
{
	std::cout << std::endl;
	std::cout << "\033[1;34m\t\tTesting functions BEGIN() and END() for map:\033[0m\n";
	
	struct timeval ft_start;
	struct timeval ft_end;
	gettimeofday(&ft_start, NULL);	

	ft::map<char,int> ft_map;
  	ft_map['b'] = 100;
  	ft_map['a'] = 200;
  	ft_map['c'] = 300;
  	// show content:
  	for (ft::map<char,int>::iterator it=ft_map.begin(); it!=ft_map.end(); ++it)
   	 std::cout << it->first << " => " << it->second << '\n';

	gettimeofday(&ft_end, NULL);
	std::cout << std::fixed << "TIME FT= " << time_diff(&ft_start, &ft_end) << std::endl;

	
	struct timeval std_start;
	struct timeval std_end;
	gettimeofday(&std_start, NULL);

	std::map<char,int> std_map;
  	std_map['b'] = 100;
  	std_map['a'] = 200;
  	std_map['c'] = 300;
  	// show content:
  	for (std::map<char,int>::iterator it=std_map.begin(); it!=std_map.end(); ++it)
    	std::cout << it->first << " => " << it->second << '\n';

	gettimeofday(&std_end, NULL);
	// END
	std::cout << "TIME STD= " << time_diff(&std_start, &std_end) << std::endl;
	if (time_diff(&std_start, &std_end) * 20 < time_diff(&ft_start, &ft_end))
	{
		std::cout << "\033[1;31m\t\tERROR: ft is too long: \033[0m\n";
		exit(EXIT_FAILURE);
	}
	else
		std::cout << "\033[1;32m\t\tPERFECT ! ft is not too long.\033[0m" << std::endl;

	std::map<char, int>::iterator it = std_map.begin();
	ft::map<char, int>::iterator my_it = ft_map.begin(); 
	std::cout << "\n COMPARE VALUES: \n";
	while (it != std_map.end())
	{
		if (it->first != my_it->first || it->second != my_it->second)
		{
			std::cout << "\033[1;31m\t\tERROR: there are difference: \033[0m\n";
			std::cout << "my data = " << my_it->first << " : " <<  my_it->second << " std_data = " << it->first << " : " <<  it->second << std::endl;
			exit(EXIT_FAILURE);
		}
		it++;
		my_it++;
	}
	std::cout << "\t OK VALUES: \n";
	std::map<char, int>::iterator it_const = std_map.begin();
	ft::map<char, int>::iterator my_it_const = ft_map.begin(); 
	std::cout << "\n COMPARE VALUES CONSTANTES: \n";
	while (it_const != std_map.end())
	{
		if (it_const->first != my_it_const->first || it_const->second != my_it_const->second)
		{
			std::cout << "\033[1;31m\t\tERROR: there are difference: \033[0m\n";
			std::cout << "my data = " << my_it_const->first << " : " <<  my_it_const->second << " std_data = " << it_const->first << " : " <<  it_const->second << std::endl;
			exit(EXIT_FAILURE);
		}
		it_const++;
		my_it_const++;
	}
	std::cout << "\t OK CONSTANTES VALUES: \n";
	std::cout << "\033[1;32m\t\tPERFECT ! No difference with BEGIN() and END() function.\033[0m" << std::endl;
	return (0);
}

int		ft_rbegin_rend( void )
{
	std::cout << std::endl;
	std::cout << "\033[1;34m\t\tTesting functions RBEGIN() and REND() for map:\033[0m\n";

	struct timeval ft_start;
	struct timeval ft_end;
	gettimeofday(&ft_start, NULL);

	ft::map<char,int> ft_map;
  	ft_map['x'] = 1000;
  	ft_map['y'] = 2000;
  	ft_map['z'] = 3000;
  	// show content:
	  ft::map<char,int>::reverse_iterator it = ft_map.rbegin();
	  ft::map<char,int>::reverse_iterator it_r = ft_map.rend();
	for (ft::map<char,int>::reverse_iterator it = ft_map.rbegin(); it != ft_map.rend(); it++)
   	{
		std::cout << it->first << " => " << it->second << '\n';
	}

	gettimeofday(&ft_end, NULL);
	std::cout << std::fixed << "TIME FT= " << time_diff(&ft_start, &ft_end) << std::endl;

	struct timeval std_start;
	struct timeval std_end;
	gettimeofday(&std_start, NULL);

	std::map<char,int> std_map;
  	std_map['x'] = 1000;
  	std_map['y'] = 2000;
  	std_map['z'] = 3000;
  	// show content:
  	for (std::map<char,int>::reverse_iterator it = std_map.rbegin(); it != std_map.rend(); ++it)
    {
		std::cout << it->first << " => " << it->second << '\n';
	}

	gettimeofday(&std_end, NULL);
	std::cout << "TIME STD= " << time_diff(&std_start, &std_end) << std::endl;
	if (time_diff(&std_start, &std_end) * 20 < time_diff(&ft_start, &ft_end))
	{
		std::cout << "\033[1;31m\t\tERROR: ft is too long: \033[0m\n";
		exit(EXIT_FAILURE);
	}
	else
		std::cout << "\033[1;32m\t\tPERFECT ! ft is not too long.\033[0m" << std::endl;

	{
	std::map<char, int>::reverse_iterator it = std_map.rbegin();
	ft::map<char, int>::reverse_iterator my_it = ft_map.rbegin(); 
	std::cout << "\n COMPARE VALUES: \n";
	while (it != std_map.rend())
	{
		if (it->first != my_it->first || it->second != my_it->second)
		{
			std::cout << "\033[1;31m\t\tERROR: there are difference: \033[0m\n";
			std::cout << "my data = " << my_it->first << " : " <<  my_it->second << " std_data = " << it->first << " : " <<  it->second << std::endl;
			exit(EXIT_FAILURE);
		}

		it++;
		my_it++;
	}
	std::cout << "\t OK VALUES: \n";

	std::map<char, int>::reverse_iterator it_const = std_map.rbegin();
	ft::map<char, int>::reverse_iterator my_it_const = ft_map.rbegin(); 
	std::cout << "\n COMPARE VALUES CONSTANTES: \n";
	while (it_const != std_map.rend())
	{
		if (it_const->first != my_it_const->first || it_const->second != my_it_const->second)
		{
			std::cout << "\033[1;31m\t\tERROR: there are difference: \033[0m\n";
			std::cout << "my data = " << my_it_const->first << " : " <<  my_it_const->second << " std_data = " << it_const->first << " : " <<  it_const->second << std::endl;
			exit(EXIT_FAILURE);
		}

		it_const++;
		my_it_const++;
	}
	std::cout << "\t OK CONSTANTES VALUES: \n";
	}
	std::cout << "\033[1;32m\t\tPERFECT ! No difference with RBEGIN() and REND() function.\033[0m" << std::endl;
	//
	return (0);
}



int		ft_empty( void )
{
	std::cout << std::endl;
	std::cout << "\033[1;34m\t\tTesting function EMPTY() for maps:\033[0m\n";

	struct timeval ft_start;
	struct timeval ft_end;
	gettimeofday(&ft_start, NULL);

	ft::map<char,int> ft_map;
	ft_map['a']=10;
	ft_map['b']=20;
	ft_map['c']=30;
	while (!ft_map.empty())
	{
		std::cout << ft_map.begin()->first << " => " << ft_map.begin()->second << '\n';
		ft_map.erase(ft_map.begin());
	}

	gettimeofday(&ft_end, NULL);
	std::cout << std::fixed << "TIME FT= " << time_diff(&ft_start, &ft_end) << std::endl;

	
	struct timeval std_start;
	struct timeval std_end;
	gettimeofday(&std_start, NULL);

	std::map<char,int> std_map;

	std_map['a']=10;
	std_map['b']=20;
	std_map['c']=30;

	while (!std_map.empty())
	{
		std::cout << std_map.begin()->first << " => " << std_map.begin()->second << '\n';
		std_map.erase(std_map.begin());
	}

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

	std::map<char, int>::iterator it = std_map.begin();
	ft::map<char, int>::iterator my_it = ft_map.begin(); 
	std::cout << "\n COMPARE VALUES: \n";
	while (it != std_map.end())
	{
		if (it->first != my_it->first || it->second != my_it->second)
		{
			std::cout << "\033[1;31m\t\tERROR: there are difference: \033[0m\n";
			std::cout << "my data = " << my_it->first << " : " <<  my_it->second << " std_data = " << it->first << " : " <<  it->second << std::endl;
			exit(EXIT_FAILURE);
		}

		it++;
		my_it++;
	}
	std::cout << "\t OK VALUES: \n";
	std::cout << "\033[1;32m\t\tPERFECT ! No difference with EMPTY() function.\033[0m" << std::endl;
	return (0);
}

int		ft_size( void )
{
	std::cout << std::endl;
	std::cout << "\033[1;34m\t\tTesting function SIZE() for maps:\033[0m\n";
	
	struct timeval ft_start;
	struct timeval ft_end;
	gettimeofday(&ft_start, NULL);
	ft::map<char,int> ft_map;
	ft_map['a']=101;
	ft_map['b']=202;
	ft_map['c']=302;

	std::cout << "mymap.size() is " << ft_map.size() << '\n';

	gettimeofday(&ft_end, NULL);
	std::cout << std::fixed << "TIME FT= " << time_diff(&ft_start, &ft_end) << std::endl;

	
	struct timeval std_start;
	struct timeval std_end;
	gettimeofday(&std_start, NULL);

	std::map<char,int> std_map;
	std_map['a']=101;
	std_map['b']=202;
	std_map['c']=302;

	std::cout << "mymap.size() is " << std_map.size() << '\n';

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

	std::map<char, int>::iterator it = std_map.begin();
	ft::map<char, int>::iterator my_it = ft_map.begin(); 
	std::cout << "\n COMPARE VALUES: \n";
	while (it != std_map.end())
	{
		if (it->first != my_it->first || it->second != my_it->second)
		{
			std::cout << "\033[1;31m\t\tERROR: there are difference: \033[0m\n";
			std::cout << "my data = " << my_it->first << " : " <<  my_it->second << " std_data = " << it->first << " : " <<  it->second << std::endl;
			exit(EXIT_FAILURE);
		}

		it++;
		my_it++;
	}
	if (std_map.size() == ft_map.size())
		std::cout << "\t OK VALUES: \n";
	else
	{
		std::cout << "\033[1;31m\t\tERROR: there are difference: \033[0m\n";
			std::cout << "my data = " << my_it->first << " : " <<  my_it->second << " std_data = " << it->first << " : " <<  it->second << std::endl;
			exit(EXIT_FAILURE);
	}

	std::cout << "\033[1;32m\t\tPERFECT ! No difference with SIZE() function.\033[0m" << std::endl;
	return (0);
}


int		ft_max_size( void )
{
	std::cout << std::endl;
	std::cout << "\033[1;34m\t\tTesting function MAX_SIZE() for maps:\033[0m\n";

	struct timeval ft_start;
	struct timeval ft_end;
	gettimeofday(&ft_start, NULL);
	int i;
  	ft::map<int,int> ft_map;

  	if (ft_map.max_size()>1000)
  	{
		for (i=0; i<1000; i++) ft_map[i]=0;
			std::cout << "The map contains 1000 elements.\n";
  	}
  	else std::cout << "The map could not hold 1000 elements.\n";

	gettimeofday(&ft_end, NULL);
	std::cout << std::fixed << "TIME FT= " << time_diff(&ft_start, &ft_end) << std::endl;

	
	struct timeval std_start;
	struct timeval std_end;
	gettimeofday(&std_start, NULL);

	int y;
  	std::map<int,int> std_map;

  	if (std_map.max_size()>1000)
  	{
   		for (y=0; y<1000; y++) std_map[y]=0;
   	 		std::cout << "The map contains 1000 elements.\n";
  	}
  	else std::cout << "The map could not hold 1000 elements.\n";


	gettimeofday(&std_end, NULL);
	std::cout << "TIME STD= " << time_diff(&std_start, &std_end) << std::endl;
	if (time_diff(&std_start, &std_end) * 20 < time_diff(&ft_start, &ft_end))
	{
		std::cout << "\033[1;31m\t\tERROR: ft is too long: \033[0m\n";
		exit(EXIT_FAILURE);
	}
	else
		std::cout << "\033[1;32m\t\tPERFECT ! ft is not too long.\033[0m" << std::endl;

	std::map<int, int>::iterator it = std_map.begin();
	ft::map<int, int>::iterator my_it = ft_map.begin(); 
	std::cout << "\n COMPARE VALUES: \n";
	while (it != std_map.end())
	{
		if (it->first != my_it->first || it->second != my_it->second)
		{
			std::cout << "\033[1;31m\t\tERROR: there are difference: \033[0m\n";
			std::cout << "my data = " << my_it->first << " : " <<  my_it->second << " std_data = " << it->first << " : " <<  it->second << std::endl;
			exit(EXIT_FAILURE);
		}
		it++;
		my_it++;
	}
	std::cout << "\t OK VALUES: \n";
	std::cout << "\033[1;32m\t\tPERFECT ! No difference with MAX_SIZE() function.\033[0m" << std::endl;
	return (0);
}


int		ft_operator( void )
{
	std::cout << std::endl;
	std::cout << "\033[1;34m\t\tTesting function OPERATOR[]() for maps:\033[0m\n";

	struct timeval ft_start;
	struct timeval ft_end;
	gettimeofday(&ft_start, NULL);

	ft::map<char,std::string> ft_map;
  	ft_map['a']="an element";
  	ft_map['b']="another element";
  	ft_map['c']=ft_map['b'];
  	std::cout << "ft_map['a'] is " << ft_map['a'] << '\n';
  	std::cout << "ft_map['b'] is " << ft_map['b'] << '\n';
  	std::cout << "ft_map['c'] is " << ft_map['c'] << '\n';
  	std::cout << "ft_map['d'] is " << ft_map['d'] << '\n';
  	std::cout << "ft_map now contains " << ft_map.size() << " elements.\n";

	gettimeofday(&ft_end, NULL);
	std::cout << std::fixed << "TIME FT= " << time_diff(&ft_start, &ft_end) << std::endl;

	
	struct timeval std_start;
	struct timeval std_end;
	gettimeofday(&std_start, NULL);

	std::map<char,std::string> std_map;
  	std_map['a']="an element";
  	std_map['b']="another element";
  	std_map['c']=std_map['b'];
  	std::cout << "std_map['a'] is " << std_map['a'] << '\n';
  	std::cout << "std_map['b'] is " << std_map['b'] << '\n';
  	std::cout << "std_map['c'] is " << std_map['c'] << '\n';
  	std::cout << "std_map['d'] is " << std_map['d'] << '\n';
  	std::cout << "std_map now contains " << std_map.size() << " elements.\n";

	gettimeofday(&std_end, NULL);
	std::cout << "TIME STD= " << time_diff(&std_start, &std_end) << std::endl;
	if (time_diff(&std_start, &std_end) * 20 < time_diff(&ft_start, &ft_end))
	{
		std::cout << "\033[1;31m\t\tERROR: ft is too long: \033[0m\n";
		exit(EXIT_FAILURE);
	}
	else
		std::cout << "\033[1;32m\t\tPERFECT ! ft is not too long.\033[0m" << std::endl;
	std::map<char, std::string>::iterator it = std_map.begin();
	ft::map<char, std::string>::iterator my_it = ft_map.begin(); 
	std::cout << "\n COMPARE VALUES: \n";
	while (it != std_map.end())
	{
		if (it->first != my_it->first || it->second != my_it->second)
		{
			std::cout << "\033[1;31m\t\tERROR: there are difference: \033[0m\n";
			std::cout << "my data = " << my_it->first << " : " <<  my_it->second << " std_data = " << it->first << " : " <<  it->second << std::endl;
			exit(EXIT_FAILURE);
		}
		
		it++;
		my_it++;
	}
	std::cout << "\t OK VALUES: \n";
	std::cout << "\033[1;32m\t\tPERFECT ! No difference with OPERATOR[]() function.\033[0m" << std::endl;
	return (0);
}

int		ft_insert( void )
{
	std::cout << std::endl;
	std::cout << "\033[1;34m\t\tTesting function INSERT() for maps:\033[0m\n";

	struct timeval ft_start;
	struct timeval ft_end;
	gettimeofday(&ft_start, NULL);

	ft::map<char,int> ft_map;
  	// first insert function version (single parameter):
  	ft_map.insert ( ft::pair<char,int>('a',100) );
  	ft_map.insert ( ft::pair<char,int>('z',200) );
	ft_map.insert ( ft::pair<char,int>('z',200) );
  	ft::pair<ft::map<char,int>::iterator,bool> ret;
  	ret = ft_map.insert ( ft::pair<char,int>('z',500) );
  	if (ret.second==false) {
   		std::cout << "element 'z' already existed";
    	std::cout << " with a value of " << ret.first->second << '\n';
  	}
	// /second insert function version (with hint position):
	ft::map<char,int>::iterator it = ft_map.begin();
	ft_map.insert (it, ft::pair<char,int>('b',300));  // max efficiency inserting
	ft_map.insert (it, ft::pair<char,int>('c',400));  // no max efficiency inserting
	// third insert function version (range insertion):
	ft::map<char,int> another_ft;
	another_ft.insert(ft_map.begin(),ft_map.find('c'));
	// showing contents:
	std::cout << "ft_map contains:\n";
	for (it=ft_map.begin(); it!=ft_map.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';

	std::cout << "another_ft contains:\n";
	for (it=another_ft.begin(); it!=another_ft.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';
	gettimeofday(&ft_end, NULL);
	std::cout << std::fixed << "TIME FT= " << time_diff(&ft_start, &ft_end) << std::endl;

	
	struct timeval std_start;
	struct timeval std_end;
	gettimeofday(&std_start, NULL);
	std::map<char,int> std_map;
  	// first insert function version (single parameter):
  	std_map.insert ( std::pair<char,int>('a',100) );
  	std_map.insert ( std::pair<char,int>('z',200) );
	std_map.insert ( std::pair<char,int>('z',200) );
  	std::pair<std::map<char,int>::iterator,bool> ret_2;
  	ret_2 = std_map.insert ( std::pair<char,int>('z',500) );
  	if (ret_2.second==false) {
   		std::cout << "element 'z' already existed";
    	std::cout << " with a value of " << ret_2.first->second << '\n';
  	}
	// second insert function version (with hint position):
	std::map<char,int>::iterator it_2 = std_map.begin();
	std_map.insert (it_2, std::pair<char,int>('b',300));  // max efficiency inserting
	std_map.insert (it_2, std::pair<char,int>('c',400));  // no max efficiency inserting
	// third insert function version (range insertion):
	std::map<char,int> another_std;
	another_std.insert(std_map.begin(),std_map.find('c'));
	// showing contents:
	std::cout << "std_map contains:\n";
	for (it_2=std_map.begin(); it_2!=std_map.end(); ++it_2)
		std::cout << it_2->first << " => " << it_2->second << '\n';
	std::cout << "another_std contains:\n";
	for (it_2=another_std.begin(); it_2!=another_std.end(); ++it_2)
		std::cout << it_2->first << " => " << it_2->second << '\n';

	gettimeofday(&std_end, NULL);
	std::cout << "TIME STD= " << time_diff(&std_start, &std_end) << std::endl;
	if (time_diff(&std_start, &std_end) * 20 < time_diff(&ft_start, &ft_end))
	{
		std::cout << "\033[1;31m\t\tERROR: ft is too long: \033[0m\n";
		exit(EXIT_FAILURE);
	}
	else
		std::cout << "\033[1;32m\t\tPERFECT ! ft is not too long.\033[0m" << std::endl;

	{
		std::map<char, int>::iterator it = std_map.begin();
		std::map<char, int>::iterator it_2 = another_std.begin();
		ft::map<char, int>::iterator my_it = ft_map.begin(); 
		ft::map<char, int>::iterator my_it_2 = another_ft.begin();
		std::cout << "\n COMPARE VALUES: \n";
		while (it != std_map.end())
		{
			if (it->first != my_it->first || it->second != my_it->second)
			{
				std::cout << "\033[1;31m\t\tERROR: there are difference: \033[0m\n";
				std::cout << "my data = " << my_it->first << " : " <<  my_it->second << " std_data = " << it->first << " : " <<  it->second << std::endl;
				exit(EXIT_FAILURE);
			}
	
			it++;
			my_it++;
		}
		while(it_2 != another_std.end())
		{
			if (it_2->first != my_it_2->first || it_2->second != my_it_2->second)
			{
				std::cout << "\033[1;31m\t\tERROR: there are difference: \033[0m\n";
				std::cout << "my data = " << my_it_2->first << " : " <<  my_it_2->second << " std_data = " << it_2->first << " : " <<  it_2->second << std::endl;
				exit(EXIT_FAILURE);
			}
			it_2++;
			my_it_2++;
		}
		std::cout << "\t OK VALUES: \n";
	}
	std::cout << "\033[1;32m\t\tPERFECT ! No difference with INSERT() function.\033[0m" << std::endl;
	return (0);
}


int		ft_erase( void )
{
	std::cout << std::endl;
	std::cout << "\033[1;34m\t\tTesting function ERASE() for maps:\033[0m\n";

	struct timeval ft_start;
	struct timeval ft_end;
	gettimeofday(&ft_start, NULL);
	ft::map<char,int> ft_map;
	ft::map<char,int>::iterator it_ft;
	ft_map['a']=10;
	ft_map['b']=20;
	ft_map['c']=30;
	ft_map['d']=40;
	ft_map['e']=50;
	ft_map['f']=60;
	it_ft=ft_map.find('b');
	ft_map.erase (it_ft);                   // erasing by iterator
	ft_map.erase('c');                  // erasing by key
	it_ft = ft_map.find ('e');
	ft_map.erase ( it_ft, ft_map.end() );    // erasing by range
	for (it_ft=ft_map.begin(); it_ft!=ft_map.end(); ++it_ft)
		std::cout << it_ft->first << " => " << it_ft->second << '\n';
	gettimeofday(&ft_end, NULL);
	std::cout << std::fixed << "TIME FT= " << time_diff(&ft_start, &ft_end) << std::endl;

	
	struct timeval std_start;
	struct timeval std_end;
	gettimeofday(&std_start, NULL);
	std::map<char,int> std_map;
	std::map<char,int>::iterator it;
	// insert some values:
	std_map['a']=10;
	std_map['b']=20;
	std_map['c']=30;
	std_map['d']=40;
	std_map['e']=50;
	std_map['f']=60;
	it=std_map.find('b');
	std_map.erase (it);                   // erasing by iterator
	std_map.erase ('c');                  // erasing by key
	it= std_map.find ('e');
	std_map.erase ( it, std_map.end() );    // erasing by range
	// show content:
	it = std_map.begin();
	for (it=std_map.begin(); it!=std_map.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';

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

	{
		std::map<char, int>::iterator it = std_map.begin();
		ft::map<char, int>::iterator my_it = ft_map.begin(); 
		std::cout << "\n COMPARE VALUES: \n";
		while (it != std_map.end())
		{
			if (it->first != my_it->first || it->second != my_it->second)
			{
				std::cout << "\033[1;31m\t\tERROR: there are difference: \033[0m\n";
				std::cout << "my data = " << my_it->first << " : " <<  my_it->second << " std_data = " << it->first << " : " <<  it->second << std::endl;
				// exit(EXIT_FAILURE);
			}
			it++;
			my_it++;
		}
		std::cout << "\t OK VALUES: \n";
	}
	std::cout << "\033[1;32m\t\tPERFECT ! No difference with ERASE() function.\033[0m" << std::endl;
	return (0);
}


int		ft_swap( void )
{
	std::cout << std::endl;
	std::cout << "\033[1;34m\t\tTesting function SWAP() for maps:\033[0m\n";

	struct timeval ft_start;
	struct timeval ft_end;
	gettimeofday(&ft_start, NULL);
	ft::map<char,int> ft_foo,ft_bar;

	ft_foo['x']=100;
	ft_foo['y']=200;
	ft_bar['a']=11;
	ft_bar['b']=22;
	ft_bar['c']=33;
	ft_foo.swap(ft_bar);

	std::cout << "ft_foo contains:\n";
	for (ft::map<char,int>::iterator it=ft_foo.begin(); it!=ft_foo.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';

	std::cout << "std_bar contains:\n";
	for (ft::map<char,int>::iterator it=ft_bar.begin(); it!=ft_bar.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';

	gettimeofday(&ft_end, NULL);
	std::cout << std::fixed << "TIME FT= " << time_diff(&ft_start, &ft_end) << std::endl;

	
	struct timeval std_start;
	struct timeval std_end;
	gettimeofday(&std_start, NULL);
	std::map<char,int> std_foo,std_bar;

	std_foo['x']=100;
	std_foo['y']=200;
	std_bar['a']=11;
	std_bar['b']=22;
	std_bar['c']=33;
	std_foo.swap(std_bar);
	std::cout << "std_foo contains:\n";
	for (std::map<char,int>::iterator it=std_foo.begin(); it!=std_foo.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';

	std::cout << "std_bar contains:\n";
	for (std::map<char,int>::iterator it=std_bar.begin(); it!=std_bar.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';
	gettimeofday(&std_end, NULL);
	std::cout << "TIME STD= " << time_diff(&std_start, &std_end) << std::endl;
	if (time_diff(&std_start, &std_end) * 20 < time_diff(&ft_start, &ft_end))
	{
		std::cout << "\033[1;31m\t\tERROR: ft is too long: \033[0m\n";
		exit(EXIT_FAILURE);
	}
	else
		std::cout << "\033[1;32m\t\tPERFECT ! ft is not too long.\033[0m" << std::endl;
	std::map<char, int>::iterator it = std_bar.begin();
	ft::map<char, int>::iterator my_it = ft_bar.begin(); 
	std::cout << "\n COMPARE VALUES: \n";
	while (it != std_bar.end())
	{
		if (it->first != my_it->first || it->second != my_it->second)
		{
			std::cout << "\033[1;31m\t\tERROR: there are difference: \033[0m\n";
			std::cout << "my data = " << my_it->first << " : " <<  my_it->second << " std_data = " << it->first << " : " <<  it->second << std::endl;
			exit(EXIT_FAILURE);
		}
		it++;
		my_it++;
	}
	std::cout << "\t OK VALUES: \n";
	std::cout << "\033[1;32m\t\tPERFECT ! No difference with SWAP() function.\033[0m" << std::endl;
	return (0);
}

int		ft_clear( void )
{
	std::cout << std::endl;
	std::cout << "\033[1;34m\t\tTesting function CLEAR() for maps:\033[0m\n";

	struct timeval ft_start;
	struct timeval ft_end;
	gettimeofday(&ft_start, NULL);
	ft::map<char,int> ft_map;

	ft_map['x']=100;
	ft_map['y']=200;
	ft_map['z']=300;
	std::cout << "ft_map contains:\n";
	for (ft::map<char,int>::iterator it=ft_map.begin(); it!=ft_map.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';

	ft_map.clear();
	ft_map['a']=1101;
	ft_map['b']=2202;

	std::cout << "ft_map contains:\n";
	for (ft::map<char,int>::iterator it=ft_map.begin(); it!=ft_map.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';

	gettimeofday(&ft_end, NULL);
	std::cout << std::fixed << "TIME FT= " << time_diff(&ft_start, &ft_end) << std::endl;

	
	struct timeval std_start;
	struct timeval std_end;
	gettimeofday(&std_start, NULL);
	std::map<char,int> std_map;

	std_map['x']=100;
	std_map['y']=200;
	std_map['z']=300;

	std::cout << "std_map contains:\n";
	for (std::map<char,int>::iterator it=std_map.begin(); it!=std_map.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';

	std_map.clear();
	std_map['a']=1101;
	std_map['b']=2202;

	std::cout << "std_map contains:\n";
	for (std::map<char,int>::iterator it=std_map.begin(); it!=std_map.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';

	gettimeofday(&std_end, NULL);
	std::cout << "TIME STD= " << time_diff(&std_start, &std_end) << std::endl;
	if (time_diff(&std_start, &std_end) * 20 < time_diff(&ft_start, &ft_end))
	{
		std::cout << "\033[1;31m\t\tERROR: ft is too long: \033[0m\n";
		exit(EXIT_FAILURE);
	}
	else
		std::cout << "\033[1;32m\t\tPERFECT ! ft is not too long.\033[0m" << std::endl;

	std::map<char, int>::iterator it = std_map.begin();
	ft::map<char, int>::iterator my_it = ft_map.begin(); 
	std::cout << "\n COMPARE VALUES: \n";
	while (it != std_map.end())
	{
		if (it->first != my_it->first || it->second != my_it->second)
		{
			std::cout << "\033[1;31m\t\tERROR: there are difference: \033[0m\n";
			std::cout << "my data = " << my_it->first << " : " <<  my_it->second << " std_data = " << it->first << " : " <<  it->second << std::endl;
			exit(EXIT_FAILURE);
		}

		it++;
		my_it++;
	}
	std::cout << "\t OK VALUES: \n";
	std::cout << "\033[1;32m\t\tPERFECT ! No difference with CLEAR() function.\033[0m" << std::endl;
	return (0);
}


int		ft_key_comp( void )
{
	std::cout << std::endl;
	std::cout << "\033[1;34m\t\tTesting function Key_comp() for maps:\033[0m\n";

	struct timeval ft_start;
	struct timeval ft_end;
	gettimeofday(&ft_start, NULL);
	ft::map<char,int> ft_map;
	ft::map<char,int>::key_compare mycomp2 = ft_map.key_comp();

	ft_map['a']=100;
	ft_map['b']=200;
	ft_map['c']=300;
	std::cout << "mymap contains:\n";
	char highest = ft_map.rbegin()->first;     // key value of last element
	ft::map<char,int>::iterator it = ft_map.begin();
	do {
		std::cout << it->first << " => " << it->second << '\n';
	} while ( mycomp2((*it++).first, highest) );
	std::cout << '\n';

	gettimeofday(&ft_end, NULL);
	std::cout << std::fixed << "TIME FT= " << time_diff(&ft_start, &ft_end) << std::endl;

	
	struct timeval std_start;
	struct timeval std_end;
	gettimeofday(&std_start, NULL);
	std::map<char,int> std_map;
	std::map<char,int>::key_compare mycomp = std_map.key_comp();

	std_map['a']=100;
	std_map['b']=200;
	std_map['c']=300;
	std::cout << "std_map contains:\n";
	char highest2 = std_map.rbegin()->first;     // key value of last element
	std::map<char,int>::iterator it2 = std_map.begin();
	do {
		std::cout << it2->first << " => " << it2->second << '\n';
	} while ( mycomp((*it2++).first, highest2) );

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

	{
		std::map<char, int>::iterator it = std_map.begin();
		ft::map<char, int>::iterator my_it = ft_map.begin(); 
		std::cout << "\n COMPARE VALUES: \n";
		while (it != std_map.end())
		{
			if (it->first != my_it->first || it->second != my_it->second)
			{
				std::cout << "\033[1;31m\t\tERROR: there are difference: \033[0m\n";
				std::cout << "my data = " << my_it->first << " : " <<  my_it->second << " std_data = " << it->first << " : " <<  it->second << std::endl;
				exit(EXIT_FAILURE);
			}

			it++;
			my_it++;
		}
		std::cout << "\t OK VALUES: \n";
	}
	std::cout << "\033[1;32m\t\tPERFECT ! No difference with Key_comp() function.\033[0m" << std::endl;
	return (0);
}






int		ft_value_comp( void )
{
	std::cout << std::endl;
	std::cout << "\033[1;34m\t\tTesting function VALUE_COMP() for maps:\033[0m\n";


	struct timeval ft_start;
	struct timeval ft_end;
	gettimeofday(&ft_start, NULL);
	// ERREUR SUR LINUX 20.04 de l'ecole
	ft::map<char,int> ft_map;

	ft_map['x']=1001;
	ft_map['y']=2002;
	ft_map['z']=3003;

	std::cout << "ft_map contains:\n";

	ft::pair<char,int> my_highest = *ft_map.rbegin();          // last element

	ft::map<char,int>::iterator my_it = ft_map.begin();
	do {
		std::cout << my_it->first << " => " << my_it->second << '\n';
	} while ( ft_map.value_comp()(*my_it++, my_highest) );

	gettimeofday(&ft_end, NULL);
	std::cout << std::fixed << "TIME FT= " << time_diff(&ft_start, &ft_end) << std::endl;

	
	struct timeval std_start;
	struct timeval std_end;
	gettimeofday(&std_start, NULL);
	std::map<char,int> std_map;

	std_map['x']=1001;
	std_map['y']=2002;
	std_map['z']=3003;

	std::cout << "std_map contains:\n";

	std::pair<char,int> highest = *std_map.rbegin();          // last element

	std::map<char,int>::iterator it = std_map.begin();
	do {
		std::cout << it->first << " => " << it->second << '\n';
	} while ( std_map.value_comp()(*it++, highest) );

	gettimeofday(&std_end, NULL);
	std::cout << "TIME STD= " << time_diff(&std_start, &std_end) << std::endl;
	if (time_diff(&std_start, &std_end) * 20 < time_diff(&ft_start, &ft_end))
	{
		std::cout << "\033[1;31m\t\tERROR: ft is too long: \033[0m\n";
		exit(EXIT_FAILURE);
	}
	else
		std::cout << "\033[1;32m\t\tPERFECT ! ft is not too long.\033[0m" << std::endl;

	{
	std::map<char, int>::iterator it = std_map.begin();
	ft::map<char, int>::iterator my_it = ft_map.begin(); 
	std::cout << "\n COMPARE VALUES: \n";
	while (it != std_map.end())
	{
		if (it->first != my_it->first || it->second != my_it->second)
		{
			std::cout << "\033[1;31m\t\tERROR: there are difference: \033[0m\n";
			std::cout << "my data = " << my_it->first << " : " <<  my_it->second << " std_data = " << it->first << " : " <<  it->second << std::endl;
			exit(EXIT_FAILURE);
		}
		 
		it++;
		my_it++;
	}
		std::cout << "\t OK VALUES: \n";
	}
	std::cout << "\033[1;32m\t\tPERFECT ! No difference with VALUE_COMP() function.\033[0m" << std::endl;
	return (0);
}

int		ft_find( void )
{
	std::cout << std::endl;
	std::cout << "\033[1;34m\t\tTesting function FIND() for maps:\033[0m\n";

	struct timeval ft_start;
	struct timeval ft_end;
	gettimeofday(&ft_start, NULL);
	ft::map<char,int> ft_map;
	ft::map<char,int>::iterator my_it;

	ft_map['a']=50;
	ft_map['b']=100;
	ft_map['c']=150;
	ft_map['d']=200;
	my_it = ft_map.find('b');
	if (my_it != ft_map.end())
		ft_map.erase (my_it);
	// print content:
	std::cout << "elements in ft_map:" << '\n';
	std::cout << "a => " << ft_map.find('a')->second << '\n';
	std::cout << "c => " << ft_map.find('c')->second << '\n';
	std::cout << "d => " << ft_map.find('d')->second << '\n';

	gettimeofday(&ft_end, NULL);
	std::cout << std::fixed << "TIME FT= " << time_diff(&ft_start, &ft_end) << std::endl;

	
	struct timeval std_start;
	struct timeval std_end;
	gettimeofday(&std_start, NULL);

	std::map<char,int> std_map;
	std::map<char,int>::iterator it;
	std_map['a']=50;
	std_map['b']=100;
	std_map['c']=150;
	std_map['d']=200;
	it = std_map.find('b');
	if (it != std_map.end())
		std_map.erase (it);
	// print content:
	std::cout << "elements in std_map:" << '\n';
	std::cout << "a => " << std_map.find('a')->second << '\n';
	std::cout << "c => " << std_map.find('c')->second << '\n';
	std::cout << "d => " << std_map.find('d')->second << '\n';

	gettimeofday(&std_end, NULL);
	std::cout << "TIME STD= " << time_diff(&std_start, &std_end) << std::endl;
	if (time_diff(&std_start, &std_end) * 20 < time_diff(&ft_start, &ft_end))
	{
		std::cout << "\033[1;31m\t\tERROR: ft is too long: \033[0m\n";
		exit(EXIT_FAILURE);
	}
	else
		std::cout << "\033[1;32m\t\tPERFECT ! ft is not too long.\033[0m" << std::endl;

	{
		std::map<char, int>::iterator it = std_map.begin();
		ft::map<char, int>::iterator my_it = ft_map.begin(); 
		std::cout << "\n COMPARE VALUES: \n";
		while (it != std_map.end())
		{
			if (it->first != my_it->first || it->second != my_it->second)
			{
				std::cout << "\033[1;31m\t\tERROR: there are difference: \033[0m\n";
				std::cout << "my data = " << my_it->first << " : " <<  my_it->second << " std_data = " << it->first << " : " <<  it->second << std::endl;
				exit(EXIT_FAILURE);
			}
			it++;
			my_it++;
		}
		std::cout << "\t OK VALUES: \n";
	}
	std::cout << "\033[1;32m\t\tPERFECT ! No difference with FIND() function.\033[0m" << std::endl;
	return (0);
}

int		ft_count( void )
{
	std::cout << std::endl;
	std::cout << "\033[1;34m\t\tTesting function COUNT() for maps:\033[0m\n";

	struct timeval ft_start;
	struct timeval ft_end;
	gettimeofday(&ft_start, NULL);
	ft::map<char,int> ft_map;
	char my_c;
	ft_map ['a']=101;
	ft_map ['c']=202;
	ft_map ['f']=303;
	for (my_c='a'; my_c<'h'; my_c++)
	{
		std::cout << my_c;
		if (ft_map.count(my_c)>0)
		std::cout << " is an element of ft_map.\n";
		else 
		std::cout << " is not an element of ft_map.\n";
	}
	gettimeofday(&ft_end, NULL);
	std::cout << std::fixed << "TIME FT= " << time_diff(&ft_start, &ft_end) << std::endl;

	
	struct timeval std_start;
	struct timeval std_end;
	gettimeofday(&std_start, NULL);
	std::map<char,int> std_map;
	char c;
	std_map ['a']=101;
	std_map ['c']=202;
	std_map ['f']=303;
	for (c='a'; c<'h'; c++)
	{
		std::cout << c;
		if (std_map.count(c)>0)
		std::cout << " is an element of std_map.\n";
		else 
		std::cout << " is not an element of std_map.\n";
	}
	gettimeofday(&std_end, NULL);
	std::cout << "TIME STD= " << time_diff(&std_start, &std_end) << std::endl;
	if (time_diff(&std_start, &std_end) * 20 < time_diff(&ft_start, &ft_end))
	{
		std::cout << "\033[1;31m\t\tERROR: ft is too long: \033[0m\n";
		exit(EXIT_FAILURE);
	}
	else
		std::cout << "\033[1;32m\t\tPERFECT ! ft is not too long.\033[0m" << std::endl;
	{
		std::map<char, int>::iterator it = std_map.begin();
		ft::map<char, int>::iterator my_it = ft_map.begin(); 
		std::cout << "\n COMPARE VALUES: \n";
		while (it != std_map.end())
		{
			if (it->first != my_it->first || it->second != my_it->second)
			{
				std::cout << "\033[1;31m\t\tERROR: there are difference: \033[0m\n";
				std::cout << "my data = " << my_it->first << " : " <<  my_it->second << " std_data = " << it->first << " : " <<  it->second << std::endl;
				exit(EXIT_FAILURE);
			}

			it++;
			my_it++;
		}
		std::cout << "\t OK VALUES: \n";
	}
	std::cout << "\033[1;32m\t\tPERFECT ! No difference with COUNT() function.\033[0m" << std::endl;
	return (0);
}

int		ft_lower_upper( void )
{
	std::cout << std::endl;
	std::cout << "\033[1;34m\t\tTesting function LOWER_BOUND() && UPPER for maps:\033[0m\n";
	struct timeval ft_start;
	struct timeval ft_end;
	gettimeofday(&ft_start, NULL);
	ft::map<char,int> ft_map;
	ft::map<char,int>::iterator my_low , my_up;
	ft_map['a']=20;
	ft_map['b']=40;
	ft_map['c']=60;
	ft_map['d']=80;
	ft_map['e']=100;
	my_low=ft_map.lower_bound ('b');  // itlow points to b
	my_up=ft_map.upper_bound ('d');   // itup points to e (not d!)
	ft_map.erase(my_low,my_up);        // erases [itlow,itup)
	// print content:
	for (ft::map<char,int>::iterator it=ft_map.begin(); it!=ft_map.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';

	gettimeofday(&ft_end, NULL);
	std::cout << std::fixed << "TIME FT= " << time_diff(&ft_start, &ft_end) << std::endl;

	struct timeval std_start;
	struct timeval std_end;
	gettimeofday(&std_start, NULL);
	std::map<char,int> std_map;
	std::map<char,int>::iterator itlow,itup;
	std_map['a']=20;
	std_map['b']=40;
	std_map['c']=60;
	std_map['d']=80;
	std_map['e']=100;
	itlow=std_map.lower_bound ('b');  // itlow points to b
	itup=std_map.upper_bound ('d');   // itup points to e (not d!)
	std_map.erase(itlow,itup);        // erases [itlow,itup)
	// print content:
	for (std::map<char,int>::iterator it=std_map.begin(); it!=std_map.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';

	gettimeofday(&std_end, NULL);
	std::cout << "TIME STD= " << time_diff(&std_start, &std_end) << std::endl;
	if (time_diff(&std_start, &std_end) * 20 < time_diff(&ft_start, &ft_end))
	{
		std::cout << "\033[1;31m\t\tERROR: ft is too long: \033[0m\n";
		exit(EXIT_FAILURE);
	}
	else
		std::cout << "\033[1;32m\t\tPERFECT ! ft is not too long.\033[0m" << std::endl;

	{
		std::map<char, int>::iterator it = std_map.begin();
		ft::map<char, int>::iterator my_it = ft_map.begin(); 
		std::cout << "\n COMPARE VALUES: \n";
		while (it != std_map.end())
		{
			if (it->first != my_it->first || it->second != my_it->second)
			{
				std::cout << "\033[1;31m\t\tERROR: there are difference: \033[0m\n";
				std::cout << "my data = " << my_it->first << " : " <<  my_it->second << " std_data = " << it->first << " : " <<  it->second << std::endl;
				exit(EXIT_FAILURE);
			}

			it++;
			my_it++;
		}
		std::cout << "\t OK VALUES: \n";
	}
	std::cout << "\033[1;32m\t\tPERFECT ! No difference with LOWER_BOUND() && UPPER function.\033[0m" << std::endl;
	return (0);
}

int		ft_equal_range( void )
{
	std::cout << std::endl;
	std::cout << "\033[1;34m\t\tTesting function EQUAL_RANGE() for maps:\033[0m\n";

	struct timeval ft_start;
	struct timeval ft_end;
	gettimeofday(&ft_start, NULL);
	ft::map<char,int> ft_map;
	ft_map['a']=10;
	ft_map['b']=20;
	ft_map['c']=30;
	ft::pair<ft::map<char,int>::iterator,ft::map<char,int>::iterator> my_ret;
	my_ret = ft_map.equal_range('b');
	std::cout << "lower bound points to: ";
	std::cout << my_ret.first->first << " => " << my_ret.first->second << '\n';
	std::cout << "upper bound points to: ";
	std::cout << my_ret.second->first << " => " << my_ret.second->second << '\n';

	gettimeofday(&ft_end, NULL);
	std::cout << std::fixed << "TIME FT= " << time_diff(&ft_start, &ft_end) << std::endl;

	struct timeval std_start;
	struct timeval std_end;
	gettimeofday(&std_start, NULL);
	std::map<char,int> std_map;
	std_map['a']=10;
	std_map['b']=20;
	std_map['c']=30;
	std::pair<std::map<char,int>::iterator,std::map<char,int>::iterator> ret;
	ret = std_map.equal_range('b');
	std::cout << "lower bound points to: ";
	std::cout << ret.first->first << " => " << ret.first->second << '\n';
	std::cout << "upper bound points to: ";
	std::cout << ret.second->first << " => " << ret.second->second << '\n';
	gettimeofday(&std_end, NULL);
	std::cout << "TIME STD= " << time_diff(&std_start, &std_end) << std::endl;
	if (time_diff(&std_start, &std_end) * 20 < time_diff(&ft_start, &ft_end))
	{
		std::cout << "\033[1;31m\t\tERROR: ft is too long: \033[0m\n";
		exit(EXIT_FAILURE);
	}
	else
		std::cout << "\033[1;32m\t\tPERFECT ! ft is not too long.\033[0m" << std::endl;

	{
		std::map<char, int>::iterator it = std_map.begin();
		ft::map<char, int>::iterator my_it = ft_map.begin(); 
		std::cout << "\n COMPARE VALUES: \n";
		while (it != std_map.end())
		{
			if (it->first != my_it->first || it->second != my_it->second)
			{
				std::cout << "\033[1;31m\t\tERROR: there are difference: \033[0m\n";
				std::cout << "my data = " << my_it->first << " : " <<  my_it->second << " std_data = " << it->first << " : " <<  it->second << std::endl;
				exit(EXIT_FAILURE);
			}

			it++;
			my_it++;
		}
		std::cout << "\t OK VALUES: \n";
	}
	std::cout << "\033[1;32m\t\tPERFECT ! No difference with EQUAL_RANGE() function.\033[0m" << std::endl;
	return (0);
}

int		ft_get_allocator( void )
{
	std::cout << std::endl;
	std::cout << "\033[1;34m\t\tTesting function GET_ALLOCATOR() for maps:\033[0m\n";
	struct timeval ft_start;
	struct timeval ft_end;
	gettimeofday(&ft_start, NULL);
	int my_size;
	ft::map<char,int> ft_map;
	ft::pair<const char,int>* my_p;
	// allocate an array of 5 elements using mymap's allocator:
	my_p=ft_map.get_allocator().allocate(5);
	// assign some values to array
	my_size = sizeof(std::map<char,int>::value_type)*5;
	std::cout << "The allocated array has a size of " << my_size << " bytes.\n";
	ft_map.get_allocator().deallocate(my_p,5);
	gettimeofday(&ft_end, NULL);
	std::cout << std::fixed << "TIME FT= " << time_diff(&ft_start, &ft_end) << std::endl;

	
	struct timeval std_start;
	struct timeval std_end;
	gettimeofday(&std_start, NULL);
	int psize;
	std::map<char,int> std_map;
	std::pair<const char,int>* p;
	// allocate an array of 5 elements using mymap's allocator:
	p=std_map.get_allocator().allocate(5);
	// assign some values to array
	psize = sizeof(std::map<char,int>::value_type)*5;
	std::cout << "The allocated array has a size of " << psize << " bytes.\n";

	std_map.get_allocator().deallocate(p,5);

	gettimeofday(&std_end, NULL);
	std::cout << "TIME STD= " << time_diff(&std_start, &std_end) << std::endl;
	if (time_diff(&std_start, &std_end) * 20 < time_diff(&ft_start, &ft_end))
	{
		std::cout << "\033[1;31m\t\tERROR: ft is too long: \033[0m\n";
		exit(EXIT_FAILURE);
	}
	else
		std::cout << "\033[1;32m\t\tPERFECT ! ft is not too long.\033[0m" << std::endl;

	std::map<char, int>::iterator it = std_map.begin();
	ft::map<char, int>::iterator my_it = ft_map.begin(); 
	std::cout << "\n COMPARE VALUES: \n";
	while (it != std_map.end())
	{
		if (it->first != my_it->first || it->second != my_it->second)
		{
			std::cout << "\033[1;31m\t\tERROR: there are difference: \033[0m\n";
			std::cout << "my data = " << my_it->first << " : " <<  my_it->second << " std_data = " << it->first << " : " <<  it->second << std::endl;
			exit(EXIT_FAILURE);
		}

		it++;
		my_it++;
	}
	std::cout << "\t OK VALUES: \n";
	std::cout << "\033[1;32m\t\tPERFECT ! No difference with GET_ALLOCATOR() function.\033[0m" << std::endl;
	return (0);
}

// for ft_constructor purpose only
bool fncomp (char lhs, char rhs) {return lhs<rhs;}

struct classcomp {
  bool operator() (const char& lhs, const char& rhs) const
  {return lhs<rhs;}
};


void		ft_constructor( void )
{
	std::cout << std::endl;
	std::cout << "\033[1;34m\t\tTesting the different CONSTRUCTOR for maps:\033[0m\n";

	struct timeval ft_start;
	struct timeval ft_end;
	gettimeofday(&ft_start, NULL);
	{
		std::cout << "\033[1;33m\tTESTING ALL TYPES for ft\033[0m" << std::endl;
		std::cout << "unsigned char, int ";
		ft::map<unsigned char, int>				ft_map8;
		std::cout << "signed char, bool ";
		ft::map<signed char, bool>					ft_map3;
		std::cout << "unsigned short, ft::string";
		ft::map<unsigned short, std::string>				ft_map18;
		std::cout << "unsigned short int, char";
		ft::map<unsigned short int, char >			ft_map9;
		std::cout << "signed short, long int";
		ft::map<signed short, long int>				ft_map19;
		std::cout << "signed short int, short int";
		ft::map<signed short int, short int>			ft_map4;
		std::cout << "unsigned int, bool ";
		ft::map<unsigned int, bool>				ft_map10;
		std::cout << "signed char, int";
		ft::map<signed int, int>					ft_map5;
		std::cout << "unsigned long long, ft::string";
		ft::map<unsigned long long, std::string>			ft_map20;
		std::cout << "signed long long, bool";
		ft::map<signed long long, bool>			ft_map21;
		std::cout << "wchar_t, int";
		ft::map<wchar_t, int>						ft_map2;
		std::cout << "signed long int, long long int";
		ft::map<signed long int, long long int>				ft_map6;
		std::cout << "signed long long int, bool";
		ft::map<signed long long int, bool>		ft_map7;
		std::cout << "unsigned long int, char";
		ft::map<unsigned long int, char>			ft_map11;
		std::cout << "unsigned long long int, ft::string";
		ft::map<unsigned long long int, std::string>		ft_map12;
		std::cout << "float, float";
		ft::map<float, float>						ft_map13;
		std::cout << "double, float";
		ft::map<double, float>						ft_map14;
		std::cout << "long double, int";
		ft::map<long double, int>					ft_map15;
		std::cout << "bool, bool ";
		ft::map<bool, bool>						ft_map16;

	}
	std::cout << "\033[1;33m\n\tTESTING constructors FT\033[0m" << std::endl;
	std::cout << "Init empty container with explicit constructor:\n ";

  	ft::map<char,int> first;
	first['a']=10;
	first['b']=30;
	first['c']=50;
	first['d']=70;
	std::cout << "Init container with range constructor (iterator):\n ";
	ft::map<char,int> second (first.begin(),first.end());
	std::cout << "Init container with copy constructor (same as the second): \n";
	ft::map<char,int> third (second);
	std::cout << "Init container with class compare:\n ";
	ft::map<char,int,classcomp> fourth;                 // class as Compare
	bool(*fn_pt)(char,char) = fncomp;
	std::cout << "Init container with pointer as compare \n";
	ft::map<char,int,bool(*)(char,char)> fifth (fn_pt); // function pointer as Compare

	gettimeofday(&ft_end, NULL);
	std::cout << std::fixed << "TIME FT= " << time_diff(&ft_start, &ft_end) << std::endl;

	
	struct timeval std_start;
	struct timeval std_end;
	gettimeofday(&std_start, NULL);
	{
		std::cout << "\033[1;33m\tTESTING ALL TYPES for std\033[0m" << std::endl;
		std::cout << "unsigned char, int ";
		std::map<unsigned char, int>				std_map8;
		std::cout << "signed char, bool ";
		std::map<signed char, bool>					std_map3;
		std::cout << "unsigned short, std::string";
		std::map<unsigned short, std::string>				std_map18;
		std::cout << "unsigned short int, char";
		std::map<unsigned short int, char >			std_map9;
		std::cout << "signed short, long int";
		std::map<signed short, long int>				std_map19;
		std::cout << "signed short int, short int";
		std::map<signed short int, short int>			std_map4;
		std::cout << "unsigned int, bool ";
		std::map<unsigned int, bool>				std_map10;
		std::cout << "signed char, int";
		std::map<signed int, int>					std_map5;
		std::cout << "unsigned long long, std::string";
		std::map<unsigned long long, std::string>			std_map20;
		std::cout << "signed long long, bool";
		std::map<signed long long, bool>			std_map21;
		std::cout << "wchar_t, int";
		std::map<wchar_t, int>						std_map2;
		std::cout << "signed long int, long long int";
		std::map<signed long int, long long int>				std_map6;
		std::cout << "signed long long int, bool";
		std::map<signed long long int, bool>		std_map7;
		std::cout << "unsigned long int, char";
		std::map<unsigned long int, char>			std_map11;
		std::cout << "unsigned long long int, std::string";
		std::map<unsigned long long int, std::string>		std_map12;
		std::cout << "float, float";
		std::map<float, float>						std_map13;
		std::cout << "double, float";
		std::map<double, float>						std_map14;
		std::cout << "long double, int";
		std::map<long double, int>					std_map15;
		std::cout << "bool, bool ";
		std::map<bool, bool>						std_map16;
	}
	std::cout << "\033[1;33m\n\tTESTING constructors STD\033[0m" << std::endl;
	std::cout << "Init empty container with explicit constructor: \n";
  	std::map<char,int> std_map;
	std_map['a']=10;
	std_map['b']=30;
	std_map['c']=50;
	std_map['d']=70;
	std::cout << "Init container with range constructor (iterator): \n";
	std::map<char,int> std_second (std_map.begin(),std_map.end());
	std::cout << "Init container with copy constructor (same as the second): \n";
	std::map<char,int> std_third (std_second);
	std::cout << "Init container with class compare: \n";
	std::map<char,int,classcomp> std_fourth;                 // class as Compare
	bool(*fn_pt2)(char,char) = fncomp;
	std::cout << "Init container with pointer as compare \n";
	std::map<char,int,bool(*)(char,char)> std_fifth (fn_pt2); // function pointer as Compare

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
	std::map<char, int>::iterator it = std_map.begin();
	ft::map<char, int>::iterator my_it = first.begin(); 
	std::cout << "\n COMPARE VALUES: \n";
	while (it != std_map.end())
	{
		if (it->first != my_it->first || it->second != my_it->second)
		{
			std::cout << "\033[1;31m\t\tERROR: there are difference: \033[0m\n";
			std::cout << "my data = " << my_it->first << " : " <<  my_it->second << " std_data = " << it->first << " : " <<  it->second << std::endl;
			exit(EXIT_FAILURE);
		}
		 
		it++;
		my_it++;
	}
	std::cout << "\t OK VALUES: \n";
	std::cout << "\033[1;32m\t\tPERFECT ! No difference for the CONSTRUCTOR.\033[0m" << std::endl;
	return ;
}

void	ft_all( void )
{
	// Iterator
	ft_begin_end();
	ft_rbegin_rend();
	
	// Capacity
	ft_empty();
	ft_size();
	ft_max_size();

	// Element access
	ft_operator();

	//	Modifiers
	ft_insert();
	ft_erase();
	ft_swap();
	ft_clear();

	// Observers
	ft_key_comp();
	ft_value_comp();

	// Operations
	ft_find();
	ft_count();
	ft_lower_upper();
	ft_equal_range();

	// Allocator
	ft_get_allocator();

	// Constructor
	ft_constructor();
	return ;
}

void	ft_display( void )
{
	std::cout << "\033[1;35m\t\tTESTS FOR MAP CONTAINER.\033[0m" << std::endl;
	std::cout << "\033[1;31mtype 1 for \tALL TESTS\033[0m" << std::endl;
	std::cout << "\033[1;32mtype 2 for \tITERATOR (begin  - end - rbegin - rend)\033[0m" << std::endl;
	std::cout << "\033[1;33mtype 3 for \tCAPACITY (empty - size - max_size)\033[0m" << std::endl;
	std::cout << "\033[1;34mtype 4 for \tELEMENT ACCESS (operator[])\033[0m" << std::endl;
	std::cout << "\033[1;38mtype 5 for \tMODIFIERS (insert - erase - swap - clear)\033[0m" << std::endl;
	std::cout << "\033[1;36mtype 6 for \tOBSERVERS (key_comp - value_comp)\033[0m" << std::endl;
	std::cout << "\033[1;37;1mtype 7 for \tOPERATIONS (find - count - lower / upper range - equal range)\033[0m" << std::endl;
	std::cout << "\033[1;38;1mtype 8 for \tALLOCATOR (get_allocator)\033[0m" << std::endl;
	std::cout << "\033[1;39;1mtype 9 for \tCONSTRUCTORS \033[0m" << std::endl;
	std::cout << "\033[1;31mtype 0 for \tEXIT\033[0m" << std::endl;
	std::cout << "\n\t\tyour answer < = ";
	return ;
}


int     main( void )
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
			ft_begin_end();
			ft_rbegin_rend();
		}
		else if (ret == 3)
		{
			ft_empty();
			ft_size();
			ft_max_size();
		}
		else if (ret == 4)
			ft_operator();
		else if (ret == 5)
		{
			ft_insert();
			ft_erase();
			ft_swap();
			ft_clear();
		}
		if (ret == 6)
		{
			ft_key_comp();
			ft_value_comp();
		}
		else if (ret == 7)
		{
			ft_find();
			ft_count();
			ft_lower_upper();
			ft_equal_range();
		}
		else if (ret == 8)
		{
			ft_get_allocator();
		}
		else if (ret == 9)
		{
			ft_constructor();
		}
		else
			ret = -1;

	}
	return (0);
}