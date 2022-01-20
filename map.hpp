#pragma once

#include "ft.hpp"
#include "iterator.hpp"
#include "RBTree.hpp"

namespace ft
{

	template <class Key, class T, class Compare = ft::less<Key>, class Alloc = std::allocator<std::pair<const Key, T> > >
	class map
	{
	public:
		typedef Key																key_type;
		typedef T																mapped_type;
		typedef ft::pair<const key_type, mapped_type>							value_type;
		typedef std::size_t														size_type;
		typedef std::ptrdiff_t													difference_type;
		typedef Compare															key_compare;
		typedef Alloc															allocator_type;
		typedef value_type&														reference;
		typedef const value_type&												const_reference;
		typedef typename allocator_type::pointer								pointer;
		typedef typename allocator_type::const_pointer							const_pointer;

		typedef ft::node_iterator<rb_node<value_type> *, value_type>			iterator;
		typedef ft::node_iterator<const rb_node<value_type> *, value_type>		const_iterator;
		typedef ft::reverse_iterator<iterator>									reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>							const_reverse_iterator;

		typedef RBTree<value_type, Compare, Alloc>								tree;
		typedef typename allocator_type::template rebind<tree>::other			allocator_rebind_tree;

		class value_compare : public std::binary_function<value_type, value_type, bool>
		{
		protected:
			key_compare comp;

		public:
			explicit value_compare(key_compare c) : comp(c) {};
			bool operator()(const value_type &x, const value_type &y) const { return comp(x.first, y.first); };
		};

	private:
		allocator_type															_allocator;
		allocator_rebind_tree													_allocator_rebind;
		Compare																	_comp;
		tree*																	_tree;

	public:
		// Constructors
		// Empty (default)
		map() {
			allocateTree();
		}

		explicit map(const Compare &comp, const Alloc &alloc = Alloc()) : _comp(comp), _allocator(alloc){
			allocateTree();
		}

		// Range
		template <class InputIt>
		map(InputIt first, InputIt last,
			const Compare &comp = Compare(), const Alloc &alloc = Alloc()) : _allocator(alloc), _comp(comp)
		{
			allocateTree();

			for (; first != last; first++)
				insert(ft::make_pair(first->first, first->second));
		}

		// Copy constructor
		map(const map &other) : _allocator(other._allocator), _comp(other._comp)
		{
			_tree = _allocator_rebind.allocate(sizeof(_tree));
			_allocator_rebind.construct(_tree, *(other._tree));

			insert(other.begin(), other.end());
		}

		// Assignment operation
		map &operator=(const map &other)
		{
			if (this == &other)
				return *this;
			_comp = other._comp;
			_allocator = other._allocator;

			clear();

			insert(other.begin(), other.end());
			return *this;
		}

		// Destructor
		~map()
		{
			_tree->clearTree(_tree->_root);
			_allocator_rebind.destroy(_tree);
			_allocator_rebind.deallocate(_tree, sizeof(_tree));
		}

		void allocateTree()
		{
			_tree = _allocator_rebind.allocate(sizeof(_tree));
			_allocator_rebind.construct(_tree);
		}

		T &at(const Key &key)
		{
			iterator tmp = find(key);
			return (tmp == end()) ? throw std::out_of_range("key not found") : tmp->second;
		}

		// Iterators
		allocator_type						get_allocator() const					{ return _allocator; }
		const T								&at(const Key &key) const				{ return static_cast<const T>(at(key)); }
		T									&operator[](const Key &key)				{ return insert(ft::make_pair(key, T())).first->second; }
		
		iterator 							begin()									{ return iterator(_tree->getBegin()); }
		const_iterator 						begin() const							{ return const_iterator(_tree->getBegin()); }
		
		iterator							end()									{ return iterator(_tree->getEnd()); }
		const_iterator						end() const								{ return const_iterator(_tree->getEnd()); }
		
		reverse_iterator					rbegin()								{ return reverse_iterator(iterator(_tree->getLast())); }
		const_reverse_iterator				rbegin() const							{ return const_reverse_iterator(const_iterator(_tree->getLast())); }
		
		reverse_iterator					rend()									{ return reverse_iterator(iterator(_tree->getEnd())); }
		const_reverse_iterator				rend() const							{ return const_reverse_iterator(const_iterator(_tree->getEnd())); }
		
		bool								empty() const							{ return size() == 0; }
		size_type							size() const							{ return _tree->_size; }
		size_type							max_size() const						{ return _allocator_rebind.max_size(); }

		// Modifiers
		void clear()
		{
			_tree->clearTree(_tree->_root);
			_allocator_rebind.destroy(_tree);
			_allocator_rebind.deallocate(_tree, sizeof(_tree));

			allocateTree();
		}

		ft::pair<iterator, bool>
		insert(const value_type &value)
		{
			return _tree->insertNode(_tree->_root, value);
		}

		iterator insert(iterator pos, const value_type &value)
		{
			if (value_comp()(*pos, value) && value_comp()(value, *++pos))
			{
				_tree->insertValue(value);
				return find(value.first);
			}
			return insert(value).first;
		}

		template <class InputIt>
		void insert(InputIt first, InputIt last)
		{
			for (; first != last; first++)
				insert(ft::make_pair(first->first, first->second));
		}

		void erase(iterator pos)
		{
			if (pos == end())
				return;
			_tree->deleteNode(pos.base());
		}

		void erase(iterator first, iterator last)
		{
			while (first != last)
				erase(first++);
		}

		size_type erase(const key_type &key)
		{
			iterator it = find(key);
			if (it == end())
				return 0;
			return _tree->deleteNode(it.base());
		}

		void swap(map &other)
		{
			std::swap(_tree, other._tree);
		}

		size_type count(const Key &key) const
		{
			return (find(key) == end()) ? 0 : 1;
		}

		// Getters
		iterator find(const Key &key) { return _tree->find(key); }
		const_iterator find(const Key &key) const { return _tree->find(key); }

		iterator lower_bound(const Key &key)
		{
			for (iterator it = begin(); it != end(); it++)
				if (!_comp(it->first, key))
					return it;
			return end();
		}

		const_iterator lower_bound(const Key &key) const
		{
			for (const_iterator it = begin(); it != end(); it++)
				if (!_comp(it->first, key))
					return it;
			return this->end();
		}

		iterator upper_bound(const Key &key)
		{
			iterator tmp = lower_bound(key);
			return (tmp == end()) ? tmp : (_comp(key, tmp->first)) ? tmp
																   : ++tmp;
		}

		const_iterator upper_bound(const Key &key) const
		{
			const_iterator tmp = lower_bound(key);
			return (tmp == end()) ? tmp : (_comp(key, tmp->first)) ? tmp
																   : ++tmp;
		}

		ft::pair<iterator, iterator>
		equal_range(const Key &key) {
			return ft::pair<iterator, iterator>(lower_bound(key), upper_bound(key));
		}

		ft::pair<const_iterator, const_iterator>
		equal_range(const Key &key) const {
			return ft::pair<const_iterator, const_iterator>(lower_bound(key), upper_bound(key));
		}

		key_compare key_comp() const { return _comp; }

		ft::map<Key, T, Compare, Alloc>::value_compare
		value_comp() const { return value_compare(key_comp()); }

		// overload operator
		friend bool operator==(const map &lhs, const map &rhs) { return lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin()); }
		friend bool operator!=(const map &lhs, const map &rhs) { return !(lhs == rhs); }
		friend bool operator<(const map &lhs, const map &rhs) { return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()); }
		friend bool operator>(const map &lhs, const map &rhs) { return rhs < lhs; }
		friend bool operator>=(const map &lhs, const map &rhs) { return !(lhs < rhs); }
		friend bool operator<=(const map &lhs, const map &rhs) { return !(rhs < lhs); }
	};
}
