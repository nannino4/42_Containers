#pragma once

#include "iterator.hpp"
#include "random_access_iterator.hpp"

namespace ft
{
	template <class iterator>
	class reverse_random_access_iterator
	{

    /* ------------------------------------------------------------- */
    /* MEMBER TYPES
    /* ------------------------------------------------------------- */
	public:
		typedef iterator													iterator_type;
		typedef typename ft::iterator_traits<iterator>::value_type			value_type;
		typedef typename ft::iterator_traits<iterator>::difference_type		difference_type;
		typedef typename ft::iterator_traits<iterator>::pointer				pointer;
		typedef typename ft::iterator_traits<iterator>::reference			reference;
		typedef typename ft::iterator_traits<iterator>::iterator_category	iterator_category;


    /* ------------------------------------------------------------- */
    /* ATTRIBUTES
    /* ------------------------------------------------------------- */
	private:
		iterator_type	_baseIterator;


    /* ------------------------------------------------------------- */
    /* COPLIEN FORM
    /* ------------------------------------------------------------- */
	public:
		// Default constructor
		reverse_random_access_iterator(pointer element = 0) : _baseIterator(element + 1) {}
		// Copy constructor
		reverse_random_access_iterator(const reverse_random_access_iterator<iterator_type> &other) : _baseIterator(other._baseIterator) {}
		// Convert constructor
		reverse_random_access_iterator(const iterator_type &other) : _baseIterator(other) {}
		// Assign operator
	    reverse_random_access_iterator& operator=(const reverse_random_access_iterator<iterator_type> &other)
	    {
	        if (this != &other)
			{
				this->_baseIterator = other._baseIterator;
			}
	        return (*this);
	    }
		// Destructor
		~reverse_random_access_iterator() {}


    /* ------------------------------------------------------------- */
    /* GETTERS
    /* ------------------------------------------------------------- */
	public:
		pointer			getElement() const { return (_baseIterator._baseIterator - 1); }
		iterator_type	base() const { return _baseIterator; }


    /* ------------------------------------------------------------- */
    /* OPERATOR OVELOADS
    /* ------------------------------------------------------------- */
	public:
		reference	operator*() const { return (*(_baseIterator._baseIterator - 1)); }
        pointer		operator->() const { return &(operator*()); }
		reference operator[](difference_type n) const { return _baseIterator[-n - 1]; }

		reverse_random_access_iterator	&operator++() {

			--_baseIterator;
			return (*this);
		}
		
		reverse_random_access_iterator	operator++(int) {
			reverse_random_access_iterator ret(*this);
			--(*this);
			return (ret);
		}
		
		reverse_random_access_iterator	&operator--() {

			++_baseIterator;
			return (*this);
		}
		
		reverse_random_access_iterator	operator--(int) {
			reverse_random_access_iterator ret(*this);
			++(*this);
			return (ret);
		}
		
		reverse_random_access_iterator operator+=(difference_type n)
		{
			_baseIterator -= n;
			return (*this);
		}

		reverse_random_access_iterator operator-=(difference_type n)
		{
			_baseIterator += n;
			return (*this);
		}

	    reverse_random_access_iterator operator+(difference_type n) const
		{
			reverse_random_access_iterator ret(_baseIterator - n);
			return ret;
		}

	    reverse_random_access_iterator operator-(difference_type n) const
		{
			reverse_random_access_iterator ret(_baseIterator + n);
			return ret;
		}		

	};	// class reverse_random_access_iterator


/* ------------------------------------------------------------- */
/* NON-MEMBER OPERATOR OVERLOADS
/* ------------------------------------------------------------- */
	template <class iterator_type>
	reverse_random_access_iterator<iterator_type>::difference_type operator-(const reverse_random_access_iterator<iterator_type> lhs, const reverse_random_access_iterator<iterator_type> rhs)
	{
		return (lhs.base() - rhs.base());
	}

	template <class iterator_type>
	reverse_random_access_iterator<iterator_type> operator+(const reverse_random_access_iterator<iterator_type>::difference_type n, const reverse_random_access_iterator<iterator_type> it)
	{
		return (it + n);
	}

	template <class iterator_type>
    bool operator==(const reverse_random_access_iterator<iterator_type> lhs, const reverse_random_access_iterator<iterator_type> rhs)
	{
		return (lhs.base() == rhs.base());
	}

	template <class iterator_type>
    bool operator!=(const reverse_random_access_iterator<iterator_type> lhs, const reverse_random_access_iterator<iterator_type> rhs)
	{
		return (lhs.base() != rhs.base());
	}

	template <class iterator_type>
    bool operator>(const reverse_random_access_iterator<iterator_type> lhs, const reverse_random_access_iterator<iterator_type> rhs)
	{
		return (lhs.base() < rhs.base());
	}

	template <class iterator_type>
    bool operator>(const reverse_random_access_iterator<iterator_type> lhs, const reverse_random_access_iterator<iterator_type> rhs)
	{
		return (lhs.base() < rhs.base());
	}

	template <class iterator_type>
    bool operator>=(const reverse_random_access_iterator<iterator_type> lhs, const reverse_random_access_iterator<iterator_type> rhs)
	{
		return (lhs.base() <= rhs.base());
	}

	template <class iterator_type>
    bool operator>=(const reverse_random_access_iterator<iterator_type> lhs, const reverse_random_access_iterator<iterator_type> rhs)
	{
		return (lhs.base() <= rhs.base());
	}

}	// namespace ft
