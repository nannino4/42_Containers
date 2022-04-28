#pragma once

namespace ft
{

	template <class T1, class T2>
	struct pair
	{
	//------------------------------------------------------------- */
	// MEMBER TYPES
	//------------------------------------------------------------- */
		typedef T1	first_type;
		typedef T2	second_type;

	//------------------------------------------------------------- */
	// ATTRIBUTES
	//------------------------------------------------------------- */
		first_type	first;
		second_type	second;

	//------------------------------------------------------------- */
	// COPLIEN
	//------------------------------------------------------------- */
		// default constructor
		pair() : first(), second() {}

		// copy constructor
		template <class U, class V>
		pair(const pair<U,V> &other) : first(other.first), second(other.second) {}

		// initialization constructor
		pair(const first_type &a, const second_type &b) : first(a), second(b) {}

		// assign operator
		pair &operator=(const pair &other)
		{
			if (this != &other)
			{
				first = other.first;
				second = other.second;
			}
			return *this;
		}

	}; // class pair

//------------------------------------------------------------- */
// RELATIONAL OPERATORS
//------------------------------------------------------------- */
	template <class T1, class T2>
	bool operator==(const pair<T1,T2> &lhs, const pair<T1,T2> &rhs)
	{
		return (lhs.first == rhs.first && lhs.second == rhs.second);
	}

	template <class T1, class T2>
	bool operator!=(const pair<T1,T2> &lhs, const pair<T1,T2> &rhs)
	{
		return !(lhs == rhs);
	}

	template <class T1, class T2>
	bool operator<(const pair<T1,T2> &lhs, const pair<T1,T2> &rhs)
	{
		return (lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second));
	}

	template <class T1, class T2>
	bool operator<=(const pair<T1,T2> &lhs, const pair<T1,T2> &rhs)
	{
		return !(rhs < lhs);
	}

	template <class T1, class T2>
	bool operator>(const pair<T1,T2> &lhs, const pair<T1,T2> &rhs)
	{
		return (rhs < lhs);
	}

	template <class T1, class T2>
	bool operator>=(const pair<T1,T2> &lhs, const pair<T1,T2> &rhs)
	{
		return !(lhs < rhs);
	}

	template <class T1, class T2>
	pair<T1,T2> make_pair(T1 x, T2 y) { return pair<T1,T2>(x,y); }

} // namespace ft
