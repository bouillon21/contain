#pragma once

#ifndef STACK_HPP
#define STACK_HPP

#include "vector.hpp"

namespace ft
{
    template <class T, class Container = ft::vector<T> >
    class stack
    {
    public:
        typedef T						value_type;
        typedef Container				container_type;
        typedef size_t					size_type;
        typedef value_type &			reference;
        typedef const value_type &		const_reference;
        typedef value_type *			pointer;
        typedef const value_type *		const_pointer;

        stack(const stack &src) : c(src.c){};
        stack &operator=(const stack &other)
        {
            if (this == &other)
                return *this;
			c = other.c;
            return *this;
        };

        explicit stack(const container_type &cont = container_type()) : c(cont){};
        ~stack(){};

        size_type size() const { return c.size(); };
        bool empty() const { return c.empty(); };

        reference top() { return c.back(); };
        const_reference top() const { return c.back(); };

        void push(const value_type &val) { c.push_back(val); };
        void pop() { c.pop_back(); };

        container_type getCont() const { return c; }

        friend bool operator==(const stack<T, Container> &lhs, const stack<T, Container> &rhs) { return (lhs.getCont() == rhs.getCont()); }
        friend bool operator<(const stack<T, Container> &lhs, const stack<T, Container> &rhs) { return (lhs.getCont() < rhs.getCont()); }

	protected:
        container_type c;
    };

    template <class T, class Container>
    bool operator!=(const stack<T, Container> &lhs, const stack<T, Container> &rhs) { return !(lhs == rhs); }
    template <class T, class Container>
    bool operator>=(const stack<T, Container> &lhs, const stack<T, Container> &rhs) { return !(lhs < rhs); }
    template <class T, class Container>
    bool operator>(const stack<T, Container> &lhs, const stack<T, Container> &rhs) { return (rhs < lhs); }
    template <class T, class Container>
    bool operator<=(const stack<T, Container> &lhs, const stack<T, Container> &rhs) { return !(rhs < lhs); }
}

#endif
