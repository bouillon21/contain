#include <iostream>
#include <deque>
#include <stack>
#include <vector>

#include "stack.hpp"
#include "vector.hpp"

void insert()
{
	{
		ft::vector<int> firstVector (3, 100);          // deque with 3 elements
		ft::vector<int> secondVector (2,200);        // vector with 2 elements

		ft::stack<int> first;                    // empty stack
		ft::stack<int> second (firstVector);         // stack initialized to copy of deque

		ft::stack<int, ft::vector<int> > third;  // empty stack using vector
		ft::stack<int, ft::vector<int> > fourth (secondVector);

		std::cout << "size of first: " << first.size() << '\n';
		std::cout << "size of second: " << second.size() << '\n';
		std::cout << "size of third: " << third.size() << '\n';
		std::cout << "size of fourth: " << fourth.size() << '\n';
	}
	std::cout << "==========================================" << std::endl;
	{
		std::deque<int> firstVector (3, 100);          // deque with 3 elements
		std::vector<int> secondVector (2, 200);        // vector with 2 elements

		std::stack<int> first;               				     // empty stack
		std::stack<int> second (firstVector); 			        // stack initialized to copy of deque

		std::stack<int,std::vector<int> > third;  // empty stack using vector
		std::stack<int,std::vector<int> > fourth (secondVector);

		std::cout << "size of first: " << first.size() << '\n';
		std::cout << "size of second: " << second.size() << '\n';
		std::cout << "size of third: " << third.size() << '\n';
		std::cout << "size of fourth: " << fourth.size() << '\n';
	}
}

void pop()
{
	{
		ft::stack<int> stack;

		for (int i = 0; i < 10; i++)
			stack.push(i);
		while (!stack.empty()) {
			std::cout << ' ' << stack.top();
			stack.pop();
		}
		std::cout << std::endl;
	}
	std::cout << "==========================================" << std::endl;
	{
		std::stack<int> stack;

		for (int i = 0; i < 10; i++)
			stack.push(i);
		while (!stack.empty()) {
			std::cout << ' ' << stack.top();
			stack.pop();
		}
		std::cout << std::endl;
	}
}

void top()
{
	{
		ft::stack<int> stack;

		stack.push(10);
		stack.push(20);

		stack.top() -= 5;

		std::cout << stack.top() << std::endl;
	}
	std::cout << "==========================================" << std::endl;
	{
		std::stack<int> stack;

		stack.push(10);
		stack.push(20);

		stack.top() -= 5;

		std::cout << stack.top() << std::endl;
	}
}

void push_back()
{
	{
		ft::stack<int> stack;

		stack.push(21);
		stack.push(42);
		stack.push(1337);
		stack.push(19);
		stack.push(0);
		stack.push(183792);

		ft::stack<int>		stck(stack);

		std::cout << "empty: " << stck.empty() << std::endl;
		std::cout << "size: " << stck.size() << std::endl;

		stck.push(1);
		stck.push(2);
		stck.push(3);
		stck.push(4);
		stck.push(5);
		stck.push(6);

		std::cout << "Added some elements" << std::endl;

		std::cout << "empty: " << stck.empty() << std::endl;
		std::cout << "size: " << stck.empty() << std::endl;

	}
	std::cout << "==========================================" << std::endl;
	{
		std::stack<int> stack;

		stack.push(21);
		stack.push(42);
		stack.push(1337);
		stack.push(19);
		stack.push(0);
		stack.push(183792);

		std::stack<int>		stck(stack);

		std::cout << "empty: " << stck.empty() << std::endl;
		std::cout << "size: " << stck.size() << std::endl;

		stck.push(1);
		stck.push(2);
		stck.push(3);
		stck.push(4);
		stck.push(5);
		stck.push(6);

		std::cout << "Added some elements" << std::endl;

		std::cout << "empty: " << stck.empty() << std::endl;
		std::cout << "size: " << stck.empty() << std::endl;

	}
}

int main()
{
	std::cout << "++++++++++++insert+++++++++++++++" << std::endl;
	insert();
	std::cout << "++++++++++++pop++++++++++++++++++" << std::endl;
	pop();
	std::cout << "++++++++++++top++++++++++++++++++" << std::endl;
	top();
	std::cout << "++++++++++++push_back++++++++++++" << std::endl;
	push_back();
	return (0);
}