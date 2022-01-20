#include <iostream>
#include <deque>

#include <map>
#include <vector>

#include "map.hpp"
#include "vector.hpp"

bool fncomp (char lhs, char rhs) {return lhs<rhs;}

struct classcomp {
	bool operator() (const char& lhs, const char& rhs) const
	{return lhs<rhs;}
};

void print_std_map(std::map<char, int> &map)
{
	std::cout << "size: " << map.size() << std::endl;

	for (std::map<char, int>::iterator it = map.begin(); it != map.end(); it++)
		std::cout << "(" << it->first << ", " << it->second << ") ";
	if (map.empty() == 1)
		std::cout << "empty map";

	std::cout << std::endl;
}

void print_ft_map(ft::map<char, int> &map)
{
	std::cout << "size: " << map.size() << std::endl;

	for (ft::map<char, int>::iterator it = map.begin(); it != map.end(); it++)
		std::cout << "(" << it->first << ", " << it->second << ") ";
	if (map.empty() == 1)
		std::cout << "empty map";

	std::cout << std::endl;
}

void insert()
{
	{
		std::map<char, int> firstMap;

		std::cout << "insert single parameter:" << std::endl;
		for (int i = 0; i < 7; ++i) {
			firstMap.insert(std::pair<char, int>('a' + i, i * 100));
		}
		print_std_map(firstMap);
		std::pair<std::map<char, int>::iterator, bool> ret;
		firstMap.insert(std::pair<char, int>('z', 900));
		ret = firstMap.insert(std::pair<char, int>('z', 500));
		if (!ret.second)
			std::cout << "element 'z' already existed with a value of " << ret.first->second << std::endl;

		std::cout << "insert with position:" << std::endl;
		std::map<char, int>::iterator it = firstMap.begin();
		firstMap.insert(it, std::pair<char, int>('b', 300)); // max efficiency inserting
		firstMap.insert(it, std::pair<char, int>('c', 400)); // no max efficiency inserting
		print_std_map(firstMap);

		std::cout << "range insertion:" << std::endl;
		std::map<char, int> secondMap;
		secondMap.insert(firstMap.begin(), firstMap.find('c'));

		std::cout << "firstMap contains:\n";
		print_std_map(firstMap);
		std::cout << "secondMap contains:\n";
		print_std_map(secondMap);
	}
	std::cout << "========================================" << std::endl;
	{
		ft::map<char, int> firstMap;

		std::cout << "insert single parameter:" << std::endl;
		for (int i = 0; i < 7; ++i) {
			firstMap.insert(ft::pair<char, int>('a' + i, i * 100));
		}
		print_ft_map(firstMap);
		ft::pair<ft::map<char, int>::iterator, bool> ret;
		firstMap.insert(ft::pair<char, int>('z', 900));
		ret = firstMap.insert(ft::pair<char, int>('z', 500));
		if (!ret.second)
			std::cout << "element 'z' already existed with a value of " << ret.first->second << std::endl;

		std::cout << "insert with position:" << std::endl;
		ft::map<char, int>::iterator it = firstMap.begin();
		firstMap.insert(it, ft::pair<char, int>('b', 300)); // max efficiency inserting
		firstMap.insert(it, ft::pair<char, int>('c', 400)); // no max efficiency inserting
		print_ft_map(firstMap);

		std::cout << "range insertion:" << std::endl;
		ft::map<char, int> secondMap;
		secondMap.insert(firstMap.begin(), firstMap.find('c'));

		std::cout << "firstMap contains:\n";
		print_ft_map(firstMap);
		std::cout << "secondMap contains:\n";
		print_ft_map(secondMap);
	}
}

void swap()
{
	{
		ft::map<char,int> first, second;

		for (int i = 0; i < 7; ++i) first['a' + i] = i * 10;
		for (int i = 0; i < 7; ++i) second['f' + i] = i * 100;

		first.swap(second);

		std::cout << "first contains:\n";
		print_ft_map(first);

		std::cout << "second contains:\n";
		print_ft_map(second);
	}
	std::cout << "========================================" << std::endl;
	{
		std::map<char,int> first, second;

		for (int i = 0; i < 7; ++i) first['a' + i] = i * 10;
		for (int i = 0; i < 7; ++i) second['f' + i] = i * 100;

		first.swap(second);

		std::cout << "first contains:\n";
		print_std_map(first);

		std::cout << "second contains:\n";
		print_std_map(second);
	}
}

void construct()
{
	{
		std::map<char,int> first;

		first['a']=10;
		first['b']=30;
		first['c']=50;
		first['d']=70;

		std::map<char,int> second (first.begin(),first.end());
		std::map<char,int> third (second);
		std::map<char,int,classcomp> fourth;                 // class as Compare
		bool(*fn_pt)(char,char) = fncomp;
		std::map<char,int,bool(*)(char,char)> fifth (fn_pt); // function pointer as Compare
		print_std_map(first);
		print_std_map(second);
		print_std_map(third);
	}
	std::cout << "========================================" << std::endl;
	{
		ft::map<char,int> first;

		first['a']=10;
		first['b']=30;
		first['c']=50;
		first['d']=70;

		ft::map<char,int> second (first.begin(),first.end());
		ft::map<char,int> third (second);
		ft::map<char,int, classcomp> fourth;                 // class as Compare
		bool(*fn_pt)(char,char) = fncomp;
		ft::map<char,int,bool(*)(char,char)> fifth (fn_pt); // function pointer as Compare
		print_ft_map(first);
		print_ft_map(second);
		print_ft_map(third);
	}
}

void erase()
{
	{
		ft::map<char,int> first;
		ft::map<char,int>::iterator it;

		first['a'] = 1;
		first['b'] = 2;
		first['c'] = 3;
		first['d'] = 4;
		first['e'] = 5;
		first['f'] = 6;

		it = first.find('b');
		first.erase (it);

		first.erase ('c');

		it = first.find ('e');
		first.erase(it, first.end() );

		print_ft_map(first);
	}
	std::cout << "========================================" << std::endl;
	{
		std::map<char,int> first;
		std::map<char,int>::iterator it;

		first['a'] = 1;
		first['b'] = 2;
		first['c'] = 3;
		first['d'] = 4;
		first['e'] = 5;
		first['f'] = 6;

		it = first.find('b');
		first.erase (it);

		first.erase ('c');

		it = first.find ('e');
		first.erase(it, first.end() );

		print_std_map(first);
	}
}

void lower_bound()
{
	{
		ft::map<int, int> map;
		map.insert(ft::make_pair(10, 10));
		map.insert(ft::make_pair(20, 20));
		map.insert(ft::make_pair(30, 30));
		map.insert(ft::make_pair(40, 40));
		map.insert(ft::make_pair(50, 50));
		map.insert(ft::make_pair(60, 60));
		ft::map<int, int>::iterator it;
		for (int i = 1; i < 60; i += 10) {
			it = map.lower_bound(i);
			std::cout << it->first << " -> " << it->second << std::endl;
		}
	}
	std::cout << "========================================" << std::endl;
	{
		std::map<int, int> map;
		map.insert(std::make_pair(10, 10));
		map.insert(std::make_pair(20, 20));
		map.insert(std::make_pair(30, 30));
		map.insert(std::make_pair(40, 40));
		map.insert(std::make_pair(50, 50));
		map.insert(std::make_pair(60, 60));
		std::map<int, int>::iterator it;
		for (int i = 1; i < 60; i += 10) {
			it = map.lower_bound(i);
			std::cout << it->first << " -> " << it->second << std::endl;
		}
	}
}

void equal_range()
{
	{
		ft::map<char,int> map;

		map['a']=20;
		map['b']=40;
		map['c']=60;
		map['d']=80;
		map['e']=100;

		ft::pair<ft::map<char, int>::iterator, ft::map<char, int>::iterator> eq;
		eq = map.equal_range('a');

		std::cout << "lower bound points to: ";
		std::cout << eq.first->first << " => " << eq.first->second << std::endl;

		std::cout << "upper bound points to: ";
		std::cout << eq.second->first << " => " << eq.second->second << std::endl;
	}
	std::cout << "========================================" << std::endl;
	{
		std::map<char,int> map;

		map['a']=20;
		map['b']=40;
		map['c']=60;
		map['d']=80;
		map['e']=100;

		std::pair<std::map<char, int>::iterator, std::map<char, int>::iterator> eq;
		eq = map.equal_range('a');

		std::cout << "lower bound points to: ";
		std::cout << eq.first->first << " => " << eq.first->second << std::endl;

		std::cout << "upper bound points to: ";
		std::cout << eq.second->first << " => " << eq.second->second << std::endl;
	}
}

int main()
{
	insert();
	swap();
	construct();
	erase();
	lower_bound();
	equal_range();
	return (0);
}