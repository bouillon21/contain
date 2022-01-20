#pragma once

#include "ft.hpp"

namespace ft
{
	//------------------------iterator_traits-------------------------//
	//Вспомогательная структура-шаблон, используется для указания
	//всех критических определений типов, которые должен иметь итератор.

	template <class T>
	struct iterator_traits
	{
	public:
		typedef typename T::value_type value_type;
		typedef typename T::difference_type difference_type;
		typedef typename T::pointer pointer;
		typedef typename T::const_pointer const_pointer;
		typedef typename T::reference reference;
		typedef typename T::const_reference const_reference;
		typedef typename T::iterator_category iterator_category;
	};

	template <class T>
	class iterator_traits<T *>
	{
	public:
		typedef T value_type;
		typedef T *pointer;
		typedef const T *const_pointer;
		typedef T &reference;
		typedef const T &const_reference;
		typedef ptrdiff_t difference_type;
		typedef std::random_access_iterator_tag iterator_category;
	};

	template <class T>
	class iterator_traits<const T *>
	{
	public:
		typedef T value_type;
		typedef const T *pointer;
		typedef const T *const_pointer;
		typedef const T &reference;
		typedef const T &const_reference;
		typedef ptrdiff_t difference_type;
		typedef std::random_access_iterator_tag iterator_category;
	};






	//---------------iterator and reverse_iterator--------------------//
	template <class T>
	class iterator
	{
	private:
		T _ptr;

	public:
		typedef T iterator_type;
		typedef typename iterator_traits<iterator_type>::value_type value_type;
		typedef typename iterator_traits<iterator_type>::pointer pointer;
		typedef typename iterator_traits<iterator_type>::const_pointer const_pointer;
		typedef typename iterator_traits<iterator_type>::reference reference;
		typedef typename iterator_traits<iterator_type>::const_reference const_reference;
		typedef typename iterator_traits<iterator_type>::difference_type difference_type;
		typedef typename iterator_traits<iterator_type>::iterator_category iterator_category;

		iterator() : _ptr(NULL) {}
		
		iterator(iterator_type value) : _ptr(value) {}
		
		
		//enable_if  используется для удаления кандидатов из разрешения перегрузки,
		//— так как он исключает набор перегрузок,
		//— чтобы одно определение можно было отклонить в пользу другого.

		//is_convertible
		//Проверяет, можно ли преобразовать один тип в другой.
		template <class U>
		iterator(const iterator<U> &other,
				 typename ft::enable_if<std::is_convertible<U, iterator_type>::value>::type * = 0) : _ptr(other.base()){};
		~iterator(){};

		T base() const { return _ptr; }

		reference operator*() const { return *this->_ptr; }
		pointer operator->() const { return &(operator*()); }

		iterator &operator=(const iterator &obj)
		{
			this->_ptr = obj._ptr;
			return *this;
		}

		iterator operator++(int)
		{
			iterator tmp(*this);
			_ptr++;
			return tmp;
		}
		iterator operator--(int)
		{
			iterator tmp(*this);
			_ptr--;
			return tmp;
		}
		iterator &operator++()
		{
			this->_ptr++;
			return *this;
		}
		iterator &operator--()
		{
			this->_ptr--;
			return *this;
		}

		iterator operator-(int n) const { return iterator(this->_ptr - n); }
		iterator operator+(int n) const { return iterator(this->_ptr + n); }
		iterator &operator-=(int n)
		{
			this->_ptr -= n;
			return (*this);
		}
		iterator &operator+=(int n)
		{
			this->_ptr += n;
			return (*this);
		}

		reference operator[](const unsigned int index) { return this->_ptr[index]; }

		bool operator!=(const iterator &a) { return _ptr != a.base(); };
		bool operator==(const iterator &a) { return _ptr == a.base(); };

		template <class const_iterator>
		bool operator!=(const const_iterator &a) { return _ptr != a.base(); };

		template <class const_iterator>
		bool operator==(const const_iterator &a) { return _ptr == a.base(); };

		bool operator==(iterator const &obj) const { return this->_ptr == obj.base(); };
		bool operator!=(iterator const &obj) const { return this->_ptr != obj.base(); };
		bool operator<(iterator const &obj) const { return this->_ptr < obj.base(); };
		bool operator>(iterator const &obj) const { return this->_ptr > obj.base(); };
		bool operator<=(iterator const &obj) const { return this->_ptr <= obj.base(); };
		bool operator>=(iterator const &obj) const { return this->_ptr >= obj.base(); };

		friend iterator operator+(const iterator &it, difference_type n) { return iterator(it._ptr + n); }
		friend iterator operator+(difference_type n, const iterator &it) { return iterator(it._ptr + n); }
		friend iterator operator-(const iterator &it, difference_type n) { return iterator(it._ptr - n); }
		friend iterator operator-(difference_type n, const iterator &it) { return iterator(it._ptr - n); }
		friend difference_type operator-(const iterator &a, const iterator &b) { return (a._ptr - b._ptr); }
	};



	template <class T>
	class reverse_iterator
	{
		T _ptr;

	public:
		typedef T iterator_type;
		typedef typename iterator_traits<iterator_type>::difference_type difference_type;
		typedef typename iterator_traits<iterator_type>::value_type value_type;
		typedef typename iterator_traits<iterator_type>::reference reference;
		typedef typename iterator_traits<iterator_type>::const_reference const_reference;
		typedef typename iterator_traits<iterator_type>::pointer pointer;
		typedef typename iterator_traits<iterator_type>::const_pointer const_pointer;
		typedef typename iterator_traits<iterator_type>::iterator_category iterator_category;

		reverse_iterator(iterator_type value = NULL) : _ptr(value){};

		//enable_if  используется для удаления кандидатов из разрешения перегрузки,
		//— так как он исключает набор перегрузок,
		//— чтобы одно определение можно было отклонить в пользу другого.
		
		//is_convertible
		//Проверяет, можно ли преобразовать один тип в другой.
		template <class U>
		reverse_iterator(const reverse_iterator<U> &other, typename ft::enable_if<std::is_convertible<U, T>::value>::type * = 0) : _ptr(other.base()){};

		~reverse_iterator(){};
		iterator_type base() const { return this->_ptr; }

		reference operator*() { return *this->_ptr; }
		const_reference operator*() const { return *this->_ptr; }
		pointer operator->() { return &(operator*()); }
		const_pointer operator->() const { return &(operator*()); }

		reverse_iterator &operator=(const reverse_iterator &obj)
		{
			this->_ptr = obj._ptr;
			return *this;
		}
		reference operator[](difference_type n) const { return *(*this + n); }

		reverse_iterator &operator++()
		{
			--_ptr;
			return *this;
		}
		reverse_iterator operator++(int)
		{
			reverse_iterator tmp(*this);
			--_ptr;
			return tmp;
		}
		reverse_iterator &operator--()
		{
			++_ptr;
			return *this;
		}
		reverse_iterator operator--(int)
		{
			reverse_iterator tmp(*this);
			++_ptr;
			return tmp;
		}

		reverse_iterator operator+(difference_type n) const { return reverse_iterator(_ptr - n); }
		reverse_iterator &operator+=(difference_type n)
		{
			this->_ptr -= n;
			return *this;
		}
		reverse_iterator operator-(difference_type n) const { return reverse_iterator(_ptr + n); }
		reverse_iterator &operator-=(difference_type n)
		{
			this->_ptr += n;
			return *this;
		}

		bool operator==(reverse_iterator const &obj) const { return this->_ptr == obj.base(); };
		bool operator!=(reverse_iterator const &obj) const { return this->_ptr != obj.base(); };
		bool operator<(reverse_iterator const &obj) const { return this->_ptr < obj.base(); };
		bool operator>(reverse_iterator const &obj) const { return this->_ptr > obj.base(); };
		bool operator<=(reverse_iterator const &obj) const { return this->_ptr <= obj.base(); };
		bool operator>=(reverse_iterator const &obj) const { return this->_ptr >= obj.base(); };
	};

	template <typename Iterator>
	iterator<Iterator> operator+(typename iterator<Iterator>::difference_type n, const iterator<Iterator> &x)
	{
		return iterator<Iterator>(x.base() + n);
	}

	template <typename Iterator>
	iterator<Iterator> operator-(typename iterator<Iterator>::difference_type n, const iterator<Iterator> &x)
	{
		return iterator<Iterator>(x.base() - n);
	}

	template <class It>
	reverse_iterator<It> operator+(typename reverse_iterator<It>::difference_type n, const reverse_iterator<It> &rev_it)
	{
		reverse_iterator<It> tmp(rev_it);
		tmp += n;
		return tmp;
	}
 
	template <class It>
	reverse_iterator<It> operator-(typename reverse_iterator<It>::difference_type n, const reverse_iterator<It> &rev_it)
	{
		reverse_iterator<It> tmp(rev_it);
		tmp -= n;
		return tmp;
	}

	template <class It>
	typename reverse_iterator<It>::difference_type operator-(const reverse_iterator<It> &lhs, const reverse_iterator<It> &rhs)
	{ return rhs.base() - lhs.base(); }

	template <class It1, class It2>
	typename reverse_iterator<It1>::difference_type operator-(const reverse_iterator<It1> &lhs, const reverse_iterator<It2> &rhs)
	{ return rhs.base() - lhs.base(); }

	template <class _Iter1, class _Iter2>
	inline bool operator==(const reverse_iterator<_Iter1> &x, const reverse_iterator<_Iter2> &y)
	{ return (x.base() == y.base()); }

	template <class _Iter1, class _Iter2>
	inline bool operator!=(const reverse_iterator<_Iter1> &x, const reverse_iterator<_Iter2> &y) { return (x.base() != y.base()); }

	template <class _Iter1, class _Iter2>
	inline bool operator<(const reverse_iterator<_Iter1> &x, const reverse_iterator<_Iter2> &y)
	{ return (x.base() > y.base()); }

	template <class _Iter1, class _Iter2>
	inline bool operator<=(const reverse_iterator<_Iter1> &x, const reverse_iterator<_Iter2> &y) { return (x.base() >= y.base()); }

	template <class _Iter1, class _Iter2>
	inline bool operator>(const reverse_iterator<_Iter1> &x, const reverse_iterator<_Iter2> &y) { return (x.base() < y.base()); }

	template <class _Iter1, class _Iter2>
	inline bool operator>=(const reverse_iterator<_Iter1> &x, const reverse_iterator<_Iter2> &y) { return (x.base() <= y.base()); }








	//--------------------------node_iterator-------------------------//
	template <class T, class Pair>
	class node_iterator
	{
		T _node;

	public:
		typedef T iterator_type;
		typedef Pair value_type;
		typedef ptrdiff_t difference_type;
		typedef Pair &reference;
		typedef const Pair &const_reference;
		typedef Pair *pointer;
		typedef const Pair *const_pointer;
		typedef typename iterator_traits<iterator_type>::iterator_category iterator_category;

		node_iterator(iterator_type value = NULL) : _node(value){};
		~node_iterator(){};

		template <class U, class Z>
		node_iterator(const node_iterator<U, Z> &other, typename ft::enable_if<std::is_convertible<U, T>::value>::type * = 0) : _node(other.base()){};

		iterator_type base() const { return _node; }

		node_iterator &operator=(const node_iterator &obj)
		{
			_node = obj._node;
			return *this;
		}
		node_iterator operator++(int)
		{
			node_iterator tmp(*this);
			_node = nextNode();
			return tmp;
		}
		node_iterator &operator++()
		{
			_node = nextNode();
			return *this;
		}
		node_iterator operator--(int)
		{
			node_iterator tmp(*this);
			_node = prevNode();
			return tmp;
		}
		node_iterator &operator--()
		{
			_node = prevNode();
			return *this;
		}

		reference operator*() { return *(_node->pair); }
		const_reference operator*() const { return *(_node->pair); }
		pointer operator->() { return _node->pair; }
		const_pointer operator->() const { return _node->pair; }

		bool operator==(node_iterator const &obj) const { return _node == obj._node; };
		bool operator!=(node_iterator const &obj) const { return _node != obj._node; };
		bool operator>(node_iterator const &obj) const { return _node->pair > obj._node->pair; };
		bool operator<(node_iterator const &obj) const { return obj._node->pair > _node->pair; };
		bool operator<=(node_iterator const &obj) const { return _node->pair <= obj._node->pair; };
		bool operator>=(node_iterator const &obj) const { return _node->pair >= obj._node->pair; };

		T nextNode()
		{
			if (_node->_nil && _node->_begin != _node)
				return _node->_begin;
			if (!_node->_right->_nil)
			{
				_node = _node->_right;
				while (!_node->_left->_nil)
				{
					_node = _node->_left;
				}
				return _node;
			}
			T current = _node;
			T tmp = _node;
			_node = _node->_parent;
			if (!_node)
				return current->_right;
			while (_node->_left != tmp)
			{
				if (!_node->_parent)
					return current->_right;
				tmp = _node;
				_node = _node->_parent;
			}
			return _node;
		}

		T prevNode()
		{
			if (_node->_nil && _node->_parent != _node)
				return _node->_parent;
			if (!_node->_left->_nil)
			{
				_node = _node->_left;
				while (!_node->_right->_nil)
				{
					_node = _node->_right;
				}
				return _node;
			}
			T current = _node;
			T tmp = _node;
			_node = _node->_parent;
			if (!_node)
				return current->_left;
			while (_node->_right != tmp)
			{
				if (!_node->_parent)
					return current->_left;
				tmp = _node;
				_node = _node->_parent;
			}
			return _node;
		}
	};

}
