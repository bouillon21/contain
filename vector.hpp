#pragma once

#include "iterator.hpp"

namespace ft
{
	template <class T, class Alloc = std::allocator<T> >
	class vector
	{
	public:
		typedef T													value_type;
		typedef Alloc												allocator_type;
		typedef typename allocator_type::reference					reference;
		typedef typename allocator_type::const_reference			const_reference;
		typedef typename allocator_type::pointer					pointer;
		typedef typename allocator_type::const_pointer				const_pointer;
		typedef ptrdiff_t											difference_type;
		typedef size_t												size_type;
		typedef ft::iterator<pointer>								iterator;
		typedef ft::iterator<const_pointer>							const_iterator;
		typedef ft::reverse_iterator<iterator>						reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>				const_reverse_iterator;

	private:
		pointer														_arr;
		size_type													_capacity;
		size_type													_size;
		allocator_type												_alloc;

	public:

		//------------------Constructors--------------------//

		// Empty (default)
		explicit vector(const Alloc &alloc = Alloc()) : _arr(0), _capacity(0), _size(0), _alloc(alloc) {}

		// Fill
		vector(size_type size, const_reference value = value_type(), const Alloc &alloc = Alloc()) : 
				_arr(NULL), _capacity(size), _size(size), _alloc(alloc) {
			if (size < 0)
				throw std::length_error("size < 0");
			_arr = _alloc.allocate(_capacity);
			for (size_type i = 0; i < size; i++)
				_alloc.construct(&_arr[i], value);
		};

		// Range
		template <class InputIt>
		vector(typename ft::enable_if<!std::numeric_limits<InputIt>::is_integer, InputIt>::type first, InputIt last, const allocator_type &alloc = allocator_type()) : _arr(NULL), _capacity(0), _size(0), _alloc(alloc) {
			_arr = _alloc.allocate(_capacity);
			assign(first, last);
		};

		// Copy constructor
		vector(const vector &toCopy) : _arr(0), _capacity(toCopy._capacity), _size(toCopy._size), _alloc(toCopy.get_allocator()) {
			_arr = _alloc.allocate(toCopy._capacity);
			for (size_type i = 0; i < _size; i++)
				_alloc.construct(&_arr[i], toCopy._arr[i]);
		};

		// Destructor
		~vector() {
			this->clearAndDealocate();
		};

		// Assignment operation
		vector &operator=(const vector &toCopy)
		{
			// insert(begin(), toCopy.begin(), toCopy.end());
			if (this == &toCopy)
				return *this;
			this->clearAndDealocate();

			_capacity = toCopy._capacity;
			_size = toCopy._size;
			_arr = _alloc.allocate(_capacity);
			for (size_type i = 0; i < _size; i++)
				_alloc.construct(&_arr[i], toCopy._arr[i]);

			return *this;
		};

		//----------------Modifiers-------------------//

		//Присваивает вектору новое содержимое, заменяя его текущее содержимое и соответствующим образом изменяя его размер.
		void assign(size_type size, const_reference value)
		{
			if (size < 0)
				throw std::length_error("size < 0");
			this->clear();
			this->reserve(size);
			while (size--)
				push_back(value);
		};

		template <class InputIt>
		typename ft::enable_if<!std::numeric_limits<InputIt>::is_integer, void>::type
		assign(InputIt first, InputIt last)
		{
			size_type range = ft::distance(first, last);
			if (range < 0)
				throw std::length_error("vector");
			this->clear();
			this->reserve(range);
			for (; first != last; ++first)
				this->push_back(*first);
		};

		//Добавляет элементы в конец
		void push_back(const_reference value)
		{
			if (_size == _capacity)
				this->reserve(_capacity == 0 ? 1 : _capacity * 2);
			_arr[_size++] = value;
		};

		//Удаляет последний элемент
		void pop_back() {
			_alloc.destroy(_arr + _size--);
		}

		//Изменяет размер
		void resize(size_type n, value_type value = value_type()) {
			if (_capacity * 2 < n)
				reserve(n);
			while (this->_size != n)
				(_size > n) ? pop_back() : push_back(value);
		}

		//Добавляет новый элемент с выделением памяти
		void insert(iterator position, size_type n, const value_type &val)
		{
			difference_type const index = position - this->begin();
			iterator end;
			difference_type const oldEndIndex = this->end() - this->begin();
			iterator oldEnd;

			this->resize(this->_size + n);

			end = this->end();
			position = this->begin() + index;
			oldEnd = this->begin() + oldEndIndex;

			while (oldEnd != position)
				*--end = *--oldEnd;
			while (n-- > 0)
				*position++ = val;
		};

		iterator insert(iterator position, const_reference value)
		{
			size_type index = position - begin();
			this->insert(position, 1, value);
			return iterator(_arr + index);
		};

		template <class InputIt>
		typename ft::enable_if<!std::numeric_limits<InputIt>::is_integer, void>::type
		insert(iterator pos, InputIt first, InputIt last)
		{
			difference_type const offset = pos - this->begin();
			iterator end;
			difference_type const oldEndIndex = this->end() - this->begin();
			iterator oldEnd;
			size_type range = ft::distance(first, last);

			pointer temp = _alloc.allocate(range);
			size_type i = 0;
			for (InputIt it = first; it != last; it++)
				try { temp[i++] = *it; }
				catch (...) {
					_alloc.deallocate(temp, range);
					throw std::exception();
				}
			_alloc.deallocate(temp, range);

			this->resize(this->_size + range);
			end = this->end();
			pos = this->begin() + offset;
			oldEnd = this->begin() + oldEndIndex;

			while (oldEnd != pos)
				*--end = *--oldEnd;
			while (first != last)
				*pos++ = *first++;
		};


		//Стерание элемента
		iterator erase(iterator pos) {
			return (this->erase(pos, pos + 1));
		}

		iterator erase(iterator first, iterator last)
		{
			size_type start = first - begin();
			size_type end = last - begin();
			size_type offset = end - start;

			_size -= offset;
			for (size_type i = start; i < _size; ++i)
				_alloc.construct(&_arr[i], _arr[i + offset]);
			return _arr + start;
		}

		void swap(vector &other)
		{
			pointer arr = other._arr;
			size_type size = other._size;
			size_type capacity = other._capacity;
			allocator_type alloc = other._alloc;

			other._arr = _arr;
			other._size = _size;
			other._capacity = _capacity;
			other._alloc = _alloc;

			_arr = arr;
			_size = size;
			_capacity = capacity;
			_alloc = alloc;
		}

		//Изменяет капасити
		void reserve(size_type size)
		{
			if (_capacity > size)
				return;
			if (size > this->max_size())
				throw std::length_error("exceeds maximum supported size");
			if (size < 0)
				throw std::length_error("vector");
			value_type *tmp = _alloc.allocate(size);
			if (_arr && tmp)
				for (size_type i = 0; i < _size; i++)
					_alloc.construct(&tmp[i], _arr[i]);
			if (_arr)
				_alloc.deallocate(_arr, _capacity);
			_capacity = size;
			_arr = tmp;
		};

		void clear()
		{
			for (size_type i = 0; i < _size; i++)
				_alloc.destroy(_arr + i);
			_size = 0;
		};

		void clearAndDealocate()
		{
			this->clear();
			_alloc.deallocate(_arr, _capacity);
		};

		// Exceptions
		struct OutOfLimit : std::exception
		{ const char *what() const throw() { return ("This element is out of the limits"); } };

		//-----------------Element access--------------------//

		reference operator[](size_type pos)
		{
			if (pos >= _size || pos < 0)
				throw std::out_of_range("vector");
			return _arr[pos];
		};

		const_reference operator[](size_type pos) const
		{
			if (pos >= _size || pos < 0)
				throw std::out_of_range("vector");
			return _arr[pos];
		};

		//доступ к элементам только с проверкой
		reference at(size_type pos)
		{
			if (pos >= _size)
				throw std::out_of_range("vector");
			return _arr[pos];
		};

		const_reference at(size_type pos) const
		{
			if (pos >= _size)
				throw std::out_of_range("vector");
			return _arr[pos];
		};

		//-------------------Iterators-------------------//

		reference 												front()					{ return *_arr; };
		reference												back()					{ return _arr[_size - 1]; };
		const_reference											front()	const			{ return *_arr; };
		const_reference											back()	const			{ return _arr[_size - 1]; };
		pointer													data()					{ return _arr; };
		const_pointer											data()	const			{ return _arr; };
		iterator												begin()					{ return iterator(_arr); };
		const_iterator											begin()	const			{ return const_iterator(_arr); };
		iterator												end()					{ return iterator(_arr + _size); };
		const_iterator											end()	const			{ return const_iterator(_arr + _size); };
		reverse_iterator										rbegin()				{ return reverse_iterator(iterator(_arr + _size - 1)); };
		const_reverse_iterator									rbegin() const			{ return const_reverse_iterator(const_iterator(_arr + _size - 1)); };
		reverse_iterator										rend()					{ return reverse_iterator(iterator(_arr - 1)); };
		const_reverse_iterator									rend()	const			{ return const_reverse_iterator(const_iterator(_arr - 1)); };

		// Assignement operator
		friend bool operator==(const vector &lhs, const vector &rhs)
		{
			typename ft::vector<value_type, Alloc>::const_iterator l_it = lhs.begin();
			typename ft::vector<value_type, Alloc>::const_iterator l_ite = lhs.end();
			typename ft::vector<value_type, Alloc>::const_iterator r_it = rhs.begin();
			typename ft::vector<value_type, Alloc>::const_iterator r_ite = rhs.end();

			if (lhs.size() != rhs.size())
				return false;
			for (; l_it != l_ite; ++l_it, ++r_it) {
				if (*l_it != *r_it)
					return false;;
			};
			return true;
		};

		//-----------------------Overload operator-------------------//
		friend bool operator<(const vector &lhs, const vector &rhs) { return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()); };
		friend bool operator!=(const vector &lhs, const vector &rhs) { return !(lhs == rhs); };
		friend bool operator<=(const vector &lhs, const vector &rhs) { return !(rhs < lhs); };
		friend bool operator>=(const vector &lhs, const vector &rhs) { return !(lhs < rhs); };
		friend bool operator>(const vector &lhs, const vector &rhs) { return (rhs < lhs); };

		//----------------------Getters---------------------//
		bool empty() const { return _size <= 0; };
		size_type size() const { return _size; };
		size_type capacity() const { return _capacity; };
		size_type max_size() const { return _alloc.max_size(); };
		allocator_type get_allocator() const { return this->_alloc; };
	};
}
