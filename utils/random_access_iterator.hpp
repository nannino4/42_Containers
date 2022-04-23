#pragma once

#include "iterator.hpp"

namespace ft
{
	template <typename T>
	class random_access_iterator : public ft::iterator<random_access_iterator_tag, T>
	{

    //------------------------------------------------------------- */
    // MEMBER TYPES
    //------------------------------------------------------------- */
	public:
		typedef T							value_type;
		typedef long int					difference_type;
		typedef T*							pointer;
		typedef T&							reference;
		typedef random_access_iterator_tag	iterator_category;

    //------------------------------------------------------------- */
    //ATTRIBUTES
    //------------------------------------------------------------- */
	private:
        pointer _element;


    //------------------------------------------------------------- */
    //COPLIEN FORM
    //------------------------------------------------------------- */
	public:
		// Default constructor
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


    //------------------------------------------------------------- */
    //OPERATOR OVERLOADS
    //------------------------------------------------------------- */
	public:
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


//------------------------------------------------------------- */
//NON-MEMBER OPERATOR OVERLOADS
//------------------------------------------------------------- */
    template <typename T>
	typename random_access_iterator<T>::difference_type operator-(const random_access_iterator<T> &lhs, const random_access_iterator<T> &rhs)
    {
        return (lhs.base() - rhs.base());
    }

    template <typename T>
	random_access_iterator<T> operator+(const typename random_access_iterator<T>::difference_type n, const random_access_iterator<T> &it)
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
