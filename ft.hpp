#pragma once
#include <stdexcept>
#include <algorithm>
#include <cstddef>

namespace ft
{
	template <bool B, class T = void>
	struct enable_if
	{
	};
	template <class T>
	struct enable_if<true, T>
	{
		typedef T type;
	};

	template <class T, bool v>
	struct integral_constant
	{
		static const bool value = v;
		typedef T value_type;
		typedef integral_constant type;
		operator value_type() const { return value; }
	};

	template <class T>
	struct is_integral : public ft::integral_constant<T, false>
	{
	};

	template <>
	struct is_integral<bool> : public ft::integral_constant<bool, true>
	{
	};
	template <>
	struct is_integral<char> : public ft::integral_constant<bool, true>
	{
	};
	template <>
	struct is_integral<signed char> : public integral_constant<bool, true>
	{
	};
	template <>
	struct is_integral<unsigned char> : public integral_constant<bool, true>
	{
	};
	template <>
	struct is_integral<wchar_t> : public integral_constant<bool, true>
	{
	};
	template <>
	struct is_integral<char16_t> : public integral_constant<bool, true>
	{
	};
	template <>
	struct is_integral<short> : public integral_constant<bool, true>
	{
	};
	template <>
	struct is_integral<unsigned short> : public integral_constant<bool, true>
	{
	};
	template <>
	struct is_integral<int> : public integral_constant<bool, true>
	{
	};
	template <>
	struct is_integral<unsigned int> : public integral_constant<bool, true>
	{
	};
	template <>
	struct is_integral<long> : public integral_constant<bool, true>
	{
	};
	template <>
	struct is_integral<unsigned long> : public integral_constant<bool, true>
	{
	};
	template <>
	struct is_integral<long long> : public integral_constant<bool, true>
	{
	};
	template <>
	struct is_integral<unsigned long long> : public integral_constant<bool, true>
	{
	};

	template <class InputIt1, class InputIt2>
	bool equal(InputIt1 first1, InputIt1 last1, InputIt2 first2)
	{
		for (; first1 != last1; ++first1, ++first2)
			if (*first1 != *first2)
				return false;
		return true;
	}

	template <class InputIt1, class InputIt2, class BinaryPredicate>
	bool equal(InputIt1 first1, InputIt1 last1, InputIt2 first2, BinaryPredicate p)
	{
		for (; first1 != last1; ++first1, ++first2)
			if (!p(*first1, *first2))
				return false;
		return true;
	}

	template <class Ite1, class Ite2>
	bool lexicographical_compare(Ite1 first1, Ite1 last1, Ite2 first2, Ite2 last2)
	{
		while (first1 != last1 && first2 != last2 && *first1 == *first2) {
			++first1;
			++first2;
		}
		if (first1 == last1)
			return (first2 != last2);
		else if (first2 == last2)
			return (false);
		return (*first1 < *first2);
	}

	template <class T1, typename T2>
	struct pair
	{
		typedef T1 first_type;
		typedef T2 second_type;

		first_type first;
		second_type second;

		pair() : first(), second(){};
		template <class U, class V>
		pair(const pair<U, V> &src) : first(src.first), second(src.second){};
		pair(const first_type &a, const second_type &b) : first(a), second(b){};

		pair &operator=(const pair &src)
		{
			if (this == &src)
				return (*this);
			this->first = src.first;
			this->second = src.second;
			return (*this);
		}

		void swap(pair &p)
		{
			swap(first, p.first);
			swap(second, p.second);
		}
	};

	template <class T1, class T2>
	inline bool operator==(const pair<T1, T2> &x, const pair<T1, T2> &y) { return x.first == y.first && x.second == y.second; }
	template <class T1, class T2>
	inline bool operator!=(const pair<T1, T2> &x, const pair<T1, T2> &y) { return !(x == y); }
	template <class T1, class T2>
	inline bool operator<(const pair<T1, T2> &x, const pair<T1, T2> &y) { return x.first < y.first || (!(y.first < x.first) && x.second < y.second); }
	template <class T1, class T2>
	inline bool operator>(const pair<T1, T2> &x, const pair<T1, T2> &y) { return y < x; }
	template <class T1, class T2>
	inline bool operator>=(const pair<T1, T2> &x, const pair<T1, T2> &y) { return !(x < y); }
	template <class T1, class T2>
	inline bool operator<=(const pair<T1, T2> &x, const pair<T1, T2> &y) { return !(y < x); }
	template <class T1, class T2>
	inline pair<T1, T2> make_pair(T1 x, T2 y) { return pair<T1, T2>(x, y); }

	template <class Ite>
	size_t distance(Ite first, Ite last)
	{
		size_t i = 0;

		while (first != last)
		{
			first++;
			i++;
		}
		return (i);
	}

	template <class T>
	struct less : std::binary_function<T, T, bool>
	{
		bool operator()(T const &x, T const &y) const { return x < y; }
	};
}
