#pragma once

#include "vector.hpp"

namespace ft
{
	template <class T, class Container = vector<T> >
	class stack
	{


    //------------------------------------------------------------- */
    // MEMBER TYPES
    //------------------------------------------------------------- */
	public:

		typedef T			value_type;
		typedef Container	container_type;
		typedef size_t		size_type;


    //------------------------------------------------------------- */
    // ATTRIBUTES
    //------------------------------------------------------------- */
	protected:

		container_type c;


    //------------------------------------------------------------- */
    // COPLIEN
    //------------------------------------------------------------- */
	public:

		// default constructor
		explicit stack(const container_type &ctnr = container_type()) : c(ctnr) {}


    //------------------------------------------------------------- */
    // MEMBER FUNCTIONS
    //------------------------------------------------------------- */
	public:

		bool empty() const { return c.empty(); }

		size_type size() const { return c.size(); }

		value_type &top() { return c.back(); }
		const value_type &top() const { return c.back(); }

		void push(const value_type &value) { c.push_back(value); }

		void pop() { c.pop_back(); }


    //------------------------------------------------------------- */
    // FRIEND FUNCTIONS 
    //------------------------------------------------------------- */
	public:

		template <class type, class ctnr>
		friend bool operator==(const stack<type,ctnr> &lhs, const stack<type,ctnr> &rhs);
		template <class type, class ctnr>
		friend bool operator!=(const stack<type,ctnr> &lhs, const stack<type,ctnr> &rhs);
		template <class type, class ctnr>
		friend bool operator<(const stack<type,ctnr> &lhs, const stack<type,ctnr> &rhs);
		template <class type, class ctnr>
		friend bool operator<=(const stack<type,ctnr> &lhs, const stack<type,ctnr> &rhs);
		template <class type, class ctnr>
		friend bool operator>(const stack<type,ctnr> &lhs, const stack<type,ctnr> &rhs);
		template <class type, class ctnr>
		friend bool operator>=(const stack<type,ctnr> &lhs, const stack<type,ctnr> &rhs);

	}; // class stack

	template <class type, class ctnr>
	bool operator==(const stack<type, ctnr> &lhs, const stack<type, ctnr> &rhs)
	{
		return lhs.c == rhs.c;
	}

	template <class type, class ctnr>
	bool operator!=(const stack<type, ctnr> &lhs, const stack<type, ctnr> &rhs)
	{
		return lhs.c != rhs.c;
	}

	template <class type, class ctnr>
	bool operator<(const stack<type, ctnr> &lhs, const stack<type, ctnr> &rhs)
	{
		return lhs.c < rhs.c;
	}

	template <class type, class ctnr>
	bool operator<=(const stack<type, ctnr> &lhs, const stack<type, ctnr> &rhs)
	{
		return lhs.c <= rhs.c;
	}

	template <class type, class ctnr>
	bool operator>(const stack<type, ctnr> &lhs, const stack<type, ctnr> &rhs)
	{
		return lhs.c > rhs.c;
	}

	template <class type, class ctnr>
	bool operator>=(const stack<type, ctnr> &lhs, const stack<type, ctnr> &rhs)
	{
		return lhs.c >= rhs.c;
	}

} // namepace ft
