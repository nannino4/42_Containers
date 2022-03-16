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
	random_access_iterator(pointer element = 0) : _element(element) {}
	// Copy constructor
	random_access_iterator(const random_access_iterator& other) : _element(other._element) {}
	// Assign operator
    random_access_iterator& operator=(const random_access_iterator& other)
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
	pointer getElement() const { return _element; }


    /* ------------------------------------------------------------- */
    /* OPERATOR OVERLOADS
    /* ------------------------------------------------------------- */

        reference operator*() const { return (*_element); }
        pointer operator->() const { return (_element); }

        random_access_iterator& operator++() { ++_element; return (*this); }
        random_access_iterator& operator--() { --_element; return (*this); }

        random_access_iterator operator++(int)
        {
            random_access_iterator ret(*this);
            ++(*this);
            return (ret);
        }

        random_access_iterator operator--(int)
        {
            random_access_iterator res(*this);
            --(*this);
            return (res);
        }

        bool operator==(const random_access_iterator& other) const	{ return (_element == other._element); }
        bool operator!=(const random_access_iterator& other) const	{ return (_element != other._element); }
        bool operator>(const random_access_iterator& other) const	{ return (_element > other._element); }
        bool operator<(const random_access_iterator& other) const	{ return (_element < other._element); }
        bool operator<=(const random_access_iterator& other) const	{ return (_element <= other._element); }
        bool operator>=(const random_access_iterator& other) const	{ return (_element >= other._element); }
	};
}
