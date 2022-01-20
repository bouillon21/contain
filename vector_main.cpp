#include <iostream>
#include <vector>
#include "vector.hpp"


void print_std_vector(std::vector<int> &vector)
{
	std::cout << "size: " << vector.size() << std::endl;
	for (std::vector<int>::iterator it = vector.begin(); it != vector.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << std::endl;
}

void print_ft_vector(ft::vector<int> &vector)
{
	std::cout << "size: " << vector.size() << std::endl;
	for (ft::vector<int>::iterator it = vector.begin(); it != vector.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << std::endl;
}

void construct()
{
	//https://www.cplusplus.com/reference/vector/vector/vector/
	{
		// constructors used in the same order as described above:
		std::vector<int> first;                                // empty vector of ints
		std::vector<int> second (4,100);                       // four ints with value 100
		std::vector<int> third (second.begin(),second.end());  // iterating through second
		std::vector<int> fourth (third);                       // a copy of third

		// the iterator constructor can also be used to construct from arrays:
		int myints[] = {16,2,77,29};
		std::vector<int> fifth (myints, myints + sizeof(myints) / sizeof(int) );

		std::cout << "The contents of fifth are:";
		for (std::vector<int>::iterator it = fifth.begin(); it != fifth.end(); ++it)
			std::cout << ' ' << *it;
		std::cout << '\n';
	}
	std::cout << "===================================" << std::endl;
	{
		// constructors used in the same order as described above:
		ft::vector<int> first;                                // empty vector of ints
		ft::vector<int> second (4,100);                       // four ints with value 100
		ft::vector<int> third (second.begin(),second.end());  // iterating through second
		ft::vector<int> fourth (third);                       // a copy of third

		// the iterator constructor can also be used to construct from arrays:
		int myints[] = {16,2,77,29};
		ft::vector<int> fifth (myints, myints + sizeof(myints) / sizeof(int) );

		std::cout << "The contents of fifth are:";
		for (ft::vector<int>::iterator it = fifth.begin(); it != fifth.end(); ++it)
			std::cout << ' ' << *it;
		std::cout << '\n';

	}
}

void iterators()
{
	{
		std::vector<int> vector;
		std::vector<int>::iterator it;
		std::vector<int> v;
		for (int i = 0; i < 10; ++i)
			vector.push_back(i);
		it = vector.begin();
		v.push_back(*(++it));
		print_std_vector(v);
		v.push_back(*(--it));
		print_std_vector(v);
		v.push_back(*(it + 1));
		print_std_vector(v);
		it += 1;
		v.push_back(*(it - 1));
		print_std_vector(v);
		it -= 1;
		v.push_back(*it);
		print_std_vector(v);
	}
	std::cout << "===================================" << std::endl;
	{
		ft::vector<int> vector;
		ft::vector<int>::iterator it;
		ft::vector<int> v;
		for (int i = 0; i < 10; ++i)
			vector.push_back(i);
		it = vector.begin();
		v.push_back(*(++it));
		print_ft_vector(v);
		v.push_back(*(--it));
		print_ft_vector(v);
		v.push_back(*(it + 1));
		print_ft_vector(v);
		it += 1;
		v.push_back(*(it - 1));
		print_ft_vector(v);
		it -= 1;
		v.push_back(*it);
		print_ft_vector(v);
	}
}

void rev_begin_end()
{
	{
		std::vector<int> vector;
		std::vector<int> v;
		vector.push_back(1);
		vector.push_back(2);
		vector.push_back(3);
		vector.push_back(4);
		vector.push_back(5);
		v.push_back(*vector.rbegin());
		print_std_vector(v);
		v.push_back(*(vector.rbegin() + 1));
		print_std_vector(v);
		v.push_back(*(vector.rend() - 1));
		print_std_vector(v);
		v.push_back(*(vector.rend() - 2));
		print_std_vector(v);
	}
	std::cout << "===================================" << std::endl;
	{
		ft::vector<int> vector;
		ft::vector<int> v;
		vector.push_back(1);
		vector.push_back(2);
		vector.push_back(3);
		vector.push_back(4);
		vector.push_back(5);
		v.push_back(*vector.rbegin());
		print_ft_vector(v);
		v.push_back(*(vector.rbegin() + 1));
		print_ft_vector(v);
		v.push_back(*(vector.rend() - 1));
		print_ft_vector(v);
		v.push_back(*(vector.rend() - 2));
		print_ft_vector(v);
	}
}

void size()
{
	{
		std::vector<int> vector;
		std::cout << "size: " << vector.size() << std::endl;

		for (int i = 0; i < 100; i++) vector.push_back(i);
		std::cout << "size: " << vector.size() << std::endl;

		vector.insert (vector.end(), 100, 200);
		std::cout << "size: " << vector.size() << std::endl;

		vector.pop_back();
		std::cout << "size: " << vector.size() << std::endl;

		vector.assign(12000000, 1);
		std::cout << "size: " << vector.size() << std::endl;

		vector.push_back(vector.size());
		std::cout << "size: " << vector.size() << std::endl;
	}
	std::cout << "===================================" << std::endl;
	{
		std::vector<int> vector;
		std::cout << "size: " << vector.size() << std::endl;

		for (int i = 0; i < 100; i++) vector.push_back(i);
		std::cout << "size: " << vector.size() << std::endl;

		vector.insert (vector.end(), 100, 200);
		std::cout << "size: " << vector.size() << std::endl;

		vector.pop_back();
		std::cout << "size: " << vector.size() << std::endl;

		vector.assign(12000000, 1);
		std::cout << "size: " << vector.size() << std::endl;

		vector.push_back(vector.size());
		std::cout << "size: " << vector.size() << std::endl;
	}
}

void resize()
{
	{
		std::vector<int> vector;
		std::vector<int> v;
		vector.assign(100, 1);
		vector.resize(20);
		vector.reserve(20);
		std::cout << "size: " << vector.size() << std::endl;
		vector.resize(200);
		std::cout << "size: " << vector.size() << std::endl;
		vector.resize(8,100);
		std::cout << "size: " << vector.size() << std::endl;
	}
	std::cout << "===================================" << std::endl;
	{
		ft::vector<int> vector;
		ft::vector<int> v;
		vector.assign(100, 1);
		vector.resize(20);
		vector.reserve(20);
		std::cout << "size: " << vector.size() << std::endl;
		vector.resize(200);
		std::cout << "size: " << vector.size() << std::endl;
		vector.resize(8,100);
		std::cout << "size: " << vector.size() << std::endl;
	}
}

void at()
{
	{
		ft::vector<int> vector;
		vector.push_back(1);
		vector.push_back(2);
		vector.push_back(3);
		vector.push_back(4);
		vector.push_back(5);
		std::cout << "1: " << vector.at(0) << std::endl;
		std::cout << "3: " << vector.at(2) << std::endl;
		std::cout << "4: " << vector.at(3) << std::endl;
	}
	std::cout << "===================================" << std::endl;
	{
		std::vector<int> vector;
		vector.push_back(1);
		vector.push_back(2);
		vector.push_back(3);
		vector.push_back(4);
		vector.push_back(5);
		std::cout << "1: " << vector.at(0) << std::endl;
		std::cout << "3: " << vector.at(2) << std::endl;
		std::cout << "4: " << vector.at(3) << std::endl;
	}
}

void front_back()
{
	{
		ft::vector<int> vector;
		vector.push_back(1);
		vector.push_back(2);
		vector.push_back(3);
		vector.push_back(4);
		vector.push_back(5);
		std::cout << "front: " << vector.front() << std::endl;
		std::cout << "back: " << vector.back() << std::endl;
	}
	std::cout << "===================================" << std::endl;
	{
		std::vector<int> vector;
		vector.push_back(1);
		vector.push_back(2);
		vector.push_back(3);
		vector.push_back(4);
		vector.push_back(5);
		std::cout << "front: " << vector.front() << std::endl;
		std::cout << "back: " << vector.back() << std::endl;
	}
}

int main()
{
	std::cout << "++++++++++++construct++++++++++++" << std::endl;
	construct();
	std::cout << "++++++++++++iterators++++++++++++" << std::endl;
	iterators();
	std::cout << "++++++++++++rev_begin_end++++++++" << std::endl;
	rev_begin_end();
	std::cout << "++++++++++++size+++++++++++++++++" << std::endl;
	size();
	std::cout << "++++++++++++resize+++++++++++++++" << std::endl;
	resize();
	std::cout << "++++++++++++at+++++++++++++++++++" << std::endl;
	at();
	std::cout << "++++++++++++front_back+++++++++++" << std::endl;
	front_back();

	return (0);
}