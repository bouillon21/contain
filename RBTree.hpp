#pragma once

#include "ft.hpp"

#define RED true
#define BLACK false

namespace ft
{
    template <class value_type>
    struct rb_node
    {
        rb_node							                            *_begin;
        rb_node							                            *_left;
        rb_node							                            *_right;
        rb_node							                            *_parent;
        bool							                            _color;
        bool							                            _nil;
        value_type	                                                *pair;

        rb_node() : _begin(NULL), _left(nullptr), _right(nullptr), _parent(nullptr), _color(RED), _nil(true), pair(new value_type()) {}
        explicit rb_node(const value_type &p) : _begin(NULL), _left(nullptr), _right(nullptr), _parent(nullptr), _color(RED), _nil(false), pair(new value_type(p)) {}
        ~rb_node() { delete pair; }
    };

    template <class T, class Compare = ft::less<typename T::first_type>, class Alloc = std::allocator<T> >
    class RBTree // http://algolist.manual.ru/ds/rbtree.php
    {
    public:
        typedef typename T::first_type								key_type;
        typedef typename T::second_type								mapped_type;
        typedef T													value_type;
        typedef Compare												key_compare;
        typedef Alloc												allocator_type;
        typedef value_type&											reference;
        typedef const value_type&									const_reference;
        typedef value_type*											pointer;
        typedef const value_type*									const_pointer;
        typedef size_t												size_type;

        typedef rb_node<value_type>									node;
        typedef rb_node<value_type>*								node_pointer;

        typedef ft::node_iterator<node_pointer, value_type>			iterator;
        typedef ft::node_iterator<const node_pointer, value_type>	const_iterator;
        typedef ft::reverse_iterator<iterator>						reverse_iterator;
        typedef ft::reverse_iterator<const_iterator>				const_reverse_iterator;

        typedef typename allocator_type::template rebind<node>::other allocator_rebind_node;

        node					_sentinel;
        node_pointer			_root;
        size_t					_size;
        allocator_rebind_node	_allocator_rebind_node;
        Compare					_comp;

        RBTree() : _root(NULL), _size(0) {
            createNil();
        }

        RBTree(RBTree &other) : _size(0), _allocator_rebind_node(other._allocator_rebind_node), _comp(other._comp) {
            createNil();
        }

        ~RBTree(){};

        void createNil()
        {
            _sentinel._left = &_sentinel;
            _sentinel._right = &_sentinel;
            _sentinel._begin = &_sentinel;
            _sentinel._parent = &_sentinel;
            _sentinel._color = BLACK;
            _sentinel._nil = true;
            _root = &_sentinel;
        }

        RBTree &operator=(const node &other)
        {
            if (this == &other)
                return *this;
            _root = other._root;
            _sentinel = other.sentinel;
            _size = other.m_size;
            return *this;
        };

        void rotateLeft(node_pointer x)
        {
            node_pointer y = x->_right;

            x->_right = y->_left;
			if (y->_left != &_sentinel)
				y->_left->_parent = x;
			if (y != &_sentinel)
				y->_parent = x->_parent;
			if (x->_parent) {
				if (x == x->_parent->_left)
					x->_parent->_left = y;
				else {
					x->_parent->_right = y;
				}
			} else
				_root = y;
            y->_left = x;
			if (x != &_sentinel)
				x->_parent = y;
        }

        void rotateRight(node_pointer x)
        {
            node_pointer y = x->_left;

            x->_left = y->_right;
			if (y->_right != &_sentinel)
				y->_right->_parent = x;
			if (y != &_sentinel)
				y->_parent = x->_parent;
			if (x->_parent) {
				if (x == x->_parent->_right)
					x->_parent->_right = y;
				else {
					x->_parent->_left = y;
				}
			} else
				_root = y;
            y->_right = x;
			if (x != &_sentinel)
				x->_parent = y;
        }

        void insertFixup(node_pointer x)
        {
            while (x != _root && x->_parent->_color == RED)
                x = getNode(x, x->_parent == x->_parent->_parent->_left);
            _root->_color = BLACK;
        }

        node_pointer getNode(node_pointer x, bool type)
        {
            node_pointer y = x->_parent->_parent->_left;
            if (y->_color == RED)
            {
                x->_parent->_color = BLACK;
                y->_color = BLACK;
                x->_parent->_parent->_color = RED;
                x = x->_parent->_parent;
            }
            else
            {
                if (type && x == x->_parent->_right)
                {
                    x = x->_parent;
                    rotateLeft(x);
                }
                if (!type && x == x->_parent->_left)
                {
                    x = x->_parent;
                    rotateRight(x);
                }
                x->_parent->_color = BLACK;
                x->_parent->_parent->_color = RED;
                type ? rotateRight(x->_parent->_parent) : rotateLeft(x->_parent->_parent);
            }
            return x;
        }

        void deleteFixup(node_pointer x)
        {
            while (x != _root && x->_color == BLACK)
            {
                if (x == x->_parent->_left)
                {
                    node_pointer w = x->_parent->_right;
                    if (w->_color == RED)
                    {
                        w->_color = BLACK;
                        x->_parent->_color = RED;
                        rotateLeft(x->_parent);
                        w = x->_parent->_right;
                    }
                    if (w->_left->_color == BLACK && w->_right->_color == BLACK)
                    {
                        w->_color = RED;
                        x = x->_parent;
                    }
                    else
                    {
                        if (w->_right->_color == BLACK)
                        {
                            w->_left->_color = BLACK;
                            w->_color = RED;
                            rotateRight(w);
                            w = x->_parent->_right;
                        }
                        w->_color = x->_parent->_color;
                        x->_parent->_color = BLACK;
                        w->_right->_color = BLACK;
                        rotateLeft(x->_parent);
                        x = _root;
                    }
                }
                else
                {
                    node_pointer w = x->_parent->_left;
                    if (w->_color == RED)
                    {
                        w->_color = BLACK;
                        x->_parent->_color = RED;
                        rotateRight(x->_parent);
                        w = x->_parent->_left;
                    }
                    if (w->_right->_color == BLACK && w->_left->_color == BLACK)
                    {
                        w->_color = RED;
                        x = x->_parent;
                    }
                    else
                    {
                        if (w->_left->_color == BLACK)
                        {
                            w->_right->_color = BLACK;
                            w->_color = RED;
                            rotateLeft(w);
                            w = x->_parent->_left;
                        }
                        w->_color = x->_parent->_color;
                        x->_parent->_color = BLACK;
                        w->_left->_color = BLACK;
                        rotateRight(x->_parent);
                        x = _root;
                    }
                }
            }
            x->_color = BLACK;
        }

        node_pointer treeSuccessor(node_pointer x)
        {
            if (x->_right != &_sentinel)
            {
                while (x->_left != &_sentinel)
                    x = x->_left;
                return x;
            }
            node_pointer y = x->_parent;
            while (y != &_sentinel && x == y->_right)
            {
                x = y;
                y = y->_parent;
            }
            return y;
        }

        int deleteNode(node_pointer z)
        {
            node_pointer x, y;

            if (!z || z == &_sentinel)
                return 0;

            y = z->_left == &_sentinel || z->_right == &_sentinel ? z : treeSuccessor(z);
            x = y->_left != &_sentinel ? y->_left : y->_right;

            x->_parent = y->_parent;
            if (y->_parent == NULL)
                _root = x;
            else
            {
                if (y == y->_parent->_left)
                    y->_parent->_left = x;
                else
                    y->_parent->_right = x;
            }

            if (y != z)
            {
                delete z->pair;
                z->pair = new value_type(*y->pair);
            }

            if (y->_color == BLACK)
                deleteFixup(x);

            _allocator_rebind_node.deallocate(y, sizeof(node));
            _allocator_rebind_node.destroy(y);

            _sentinel._parent = getLast();
            _sentinel._begin = getBegin();
            _size--;
            return 1;
        }

        node_pointer getBegin()
        {
            node_pointer tmp = _root;
            while (tmp->_left != &_sentinel)
                tmp = tmp->_left;
            return tmp;
        }

        node_pointer getLast()
        {
            node_pointer tmp = _root;
            while (tmp->_right != &_sentinel)
                tmp = tmp->_right;
            return tmp;
        }

        node_pointer getEnd()
        {
            return &_sentinel;
        }

        ft::pair<iterator, bool>
        insertNode(node_pointer pos, const value_type &value)
        {
            node_pointer current, parent, x;

            current = pos;
            parent = 0;
            while (current != &_sentinel)
            {
				if (value.first == current->pair->first)
					return ft::make_pair(current, BLACK);
                parent = current;
                current = _comp(value.first, current->pair->first) ? current->_left : current->_right;
            }

            x = _allocator_rebind_node.allocate(sizeof(node));
            _allocator_rebind_node.construct(x, value);
            x->_parent = parent;
            x->_left = &_sentinel;
            x->_right = &_sentinel;
            x->_begin = &_sentinel;
            x->_color = RED;

            if (parent)
            {
                if (_comp(value.first, parent->pair->first))
                    parent->_left = x;
                else
                    parent->_right = x;
            }
            else
                _root = x;

			if (x == getLast()) { _sentinel._parent = x; }
			if (x == getBegin()) { _sentinel._begin = x; }
			insertFixup(x);
            _size++;
            return ft::make_pair(x, true);
        }

        void clearTree(node_pointer tmp)
        {
            if (tmp == &_sentinel)
                return;
            if (tmp->_left != &_sentinel)
                clearTree(tmp->_left);
            if (tmp->_right != &_sentinel)
                clearTree(tmp->_right);

            _allocator_rebind_node.destroy(tmp);
            _allocator_rebind_node.deallocate(tmp, sizeof(node_pointer));
        }

        void insertValue(const value_type &val) {
            insertNode(_root, val);
        }

        iterator find(const key_type key)
        {
            node_pointer current = _root;

            while (current != &_sentinel) {
                if (key == current->pair->first)
                    return (current);
                else
                    current = _comp(key, current->pair->first) ? current->_left : current->_right;
            }
            return getEnd();
        }
    };
}