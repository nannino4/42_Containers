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
	private:

		container_type _container;


    //------------------------------------------------------------- */
    // COPLIEN
    //------------------------------------------------------------- */
	public:

		// default constructor
		explicit stack(const container_type &ctnr = container_type()) : _container(ctnr) {}


    //------------------------------------------------------------- */
    // MEMBER FUNCTIONS
    //------------------------------------------------------------- */
	public:

		bool empty() const { return _container.empty(); }

		size_type size() const { return _container.size(); }

		value_type &top() { return _container.back(); }
		const value_type &top() const { return _container.back(); }

		void push(const value_type &value) { _container.push_back(value); }

		void pop() { _container.pop_back(); }


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
		return lhs._container == rhs._container;
	}

	template <class type, class ctnr>
	bool operator!=(const stack<type, ctnr> &lhs, const stack<type, ctnr> &rhs)
	{
		return lhs._container != rhs._container;
	}

	template <class type, class ctnr>
	bool operator<(const stack<type, ctnr> &lhs, const stack<type, ctnr> &rhs)
	{
		return lhs._container < rhs._container;
	}

	template <class type, class ctnr>
	bool operator<=(const stack<type, ctnr> &lhs, const stack<type, ctnr> &rhs)
	{
		return lhs._container <= rhs._container;
	}

	template <class type, class ctnr>
	bool operator>(const stack<type, ctnr> &lhs, const stack<type, ctnr> &rhs)
	{
		return lhs._container > rhs._container;
	}

	template <class type, class ctnr>
	bool operator>=(const stack<type, ctnr> &lhs, const stack<type, ctnr> &rhs)
	{
		return lhs._container >= rhs._container;
	}

} // namepace ft
