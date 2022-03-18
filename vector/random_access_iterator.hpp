#pragma once

#include "iterator.hpp"

namespace ft
{
	template <typename T>
	class random_access_iterator : ft::iterator<ft::random_access_iterator_tag, T>
	{

    /* ------------------------------------------------------------- */
    /* MEMBER TYPES
    /* ------------------------------------------------------------- */
	public:
		typedef typename ft::iterator<ft::random_access_iterator_tag, T>::value_type		value_type;
		typedef typename ft::iterator<ft::random_access_iterator_tag, T>::difference_type	difference_type;
		typedef typename ft::iterator<ft::random_access_iterator_tag, T>::pointer			pointer;
		typedef typename ft::iterator<ft::random_access_iterator_tag, T>::reference			reference;
		typedef typename ft::iterator<ft::random_access_iterator_tag, T>::iterator_category	iterator_category;


    /* ------------------------------------------------------------- */
    /* ATTRIBUTES
    /* ------------------------------------------------------------- */
	private:
        pointer _element;


    /* ------------------------------------------------------------- */
    /* COPLIEN FORM
    /* ------------------------------------------------------------- */
	public:
		// Default constructor
		random_access_iterator() : _element(nullptr) {}
		random_access_iterator(pointer elem = nullptr) : _element(elem) {}
		// Copy constructor
		random_access_iterator(const random_access_iterator<value_type> &other) : _element(other._element) {}
		// Assign operator
	    random_access_iterator& operator=(const random_access_iterator<value_type> &other)
	    {
	        if (this != &other)
	            this->_element = other._element;
	        return (*this);
	    }
		// Destructor
		~random_access_iterator() {}


    /* ------------------------------------------------------------- */
    /* GETTERS
    /* ------------------------------------------------------------- */
	pointer base() const { return _element; }


    /* ------------------------------------------------------------- */
    /* OPERATOR OVERLOADS
    /* ------------------------------------------------------------- */
	public:
	    bool operator==(const random_access_iterator<value_type> &other) const	{ return (_element == other._element); }
	    bool operator!=(const random_access_iterator<value_type> &other) const	{ return (_element != other._element); }
	    bool operator>(const random_access_iterator<value_type> &other) const	{ return (_element > other._element); }
	    bool operator<(const random_access_iterator<value_type> &other) const	{ return (_element < other._element); }
	    bool operator<=(const random_access_iterator<value_type> &other) const	{ return (_element <= other._element); }
	    bool operator>=(const random_access_iterator<value_type> &other) const	{ return (_element >= other._element); }

	    reference operator*() const { return (*_element); }
	    pointer operator->() const { return (_element); }
	    reference operator[](difference_type n) const { return (*(operator+(n))); }

	    random_access_iterator& operator++()
		{
			++_element;
			return (*this);
		}

	    random_access_iterator operator++(int)
	    {
	        random_access_iterator ret(*this);
	        ++(*this);
	        return (ret);
	    }

		random_access_iterator& operator--()
		{
			--_element;
			return (*this);
		}

	    random_access_iterator operator--(int)
	    {
	        random_access_iterator res(*this);
	        --(*this);
	        return (res);
	    }

	    random_access_iterator &operator+=(difference_type n)
	    {
	        _element += n;
	        return (*this);
	    }

	    random_access_iterator &operator-=(difference_type n)
	    {
	        _element -= n;
	        return (*this);
	    }
		
	    random_access_iterator operator+(difference_type n) const
		{
			random_access_iterator ret(*this);
			ret += n;
			return ret;
		}

	    random_access_iterator operator-(difference_type n) const
		{
			random_access_iterator ret(*this);
			ret -= n;
			return ret;
		}
	
	};	// class random_access_iterator


/* ------------------------------------------------------------- */
/* NON-MEMBER OPERATOR OVERLOADS
/* ------------------------------------------------------------- */
    template <typename T>
	random_access_iterator<T>::difference_type operator-(const random_access_iterator<T> &lhs, const random_access_iterator<T> &rhs)
    {
        return (lhs.base() - rhs.base());
    }

    template <typename T>
	random_access_iterator<T> operator+(const random_access_iterator<T>::difference_type n, const random_access_iterator<T> &it)
    {
        return (it + n);
    }

    template <typename T>
    bool operator==(const random_access_iterator<T> lhs, const random_access_iterator<T> rhs)
    {
        return (lhs.base() == rhs.base());
    }

    template <typename T>
    bool operator!=(const random_access_iterator<T> lhs, const random_access_iterator<T> rhs)
    {
        return (lhs.base() != rhs.base());
    }

    template <typename T>
    bool operator>(const random_access_iterator<T> lhs, const random_access_iterator<T> rhs)
    {
        return (lhs.base() > rhs.base());
    }

    template <typename T>
    bool operator>=(const random_access_iterator<T> lhs, const random_access_iterator<T> rhs)
    {
        return (lhs.base() >= rhs.base());
    }

    template <typename T>
    bool operator<(const random_access_iterator<T> lhs, const random_access_iterator<T> rhs)
    {
        return (lhs.base() < rhs.base());
    }

    template <typename T>
    bool operator<=(const random_access_iterator<T> lhs, const random_access_iterator<T> rhs)
    {
        return (lhs.base() <= rhs.base());
    }

}	// namespace ft
