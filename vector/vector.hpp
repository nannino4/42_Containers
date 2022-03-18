#pragma once

#include <memory>
#include "random_access_iterator.hpp"
#include "reverse_iterator.hpp"

namespace ft
{
    template <class T, class Allocator = std::allocator<T> >
	class vector
	{

    /* ------------------------------------------------------------- */
    /* MEMBER TYPES
    /* ------------------------------------------------------------- */
	public:
		typedef T													value_type;
		typedef Allocator											allocator_type;
		typedef size_t												size_type;
		typedef ptrdiff_t											difference_type;

		typedef typename allocator_type::reference					reference;
		typedef typename allocator_type::const_reference			const_reference;
		typedef typename allocator_type::pointer					pointer;
		typedef typename allocator_type::const_pointer				const_pointer;

		typedef ft::random_access_iterator<value_type>				iterator;
		typedef ft::random_access_iterator<const value_type>		const_iterator;
		typedef ft::reverse_iterator<iterator>						reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>				const_reverse_iterator;


    /* ------------------------------------------------------------- */
    /* ATTRIBUTES
    /* ------------------------------------------------------------- */
	private:
		allocator_type	_allocator;
		pointer			_vector;
		size_type		_size;
		size_type		_capacity;


    /* ------------------------------------------------------------- */
    /* COPLIEN FORM
    /* ------------------------------------------------------------- */
	public:
		/*
		**	Default constructor
		**	Constructs an empty container with no elements
		*/
		explicit vector (const allocator_type& alloc = allocator_type()) : _allocator(alloc), _vector(nullptr), _capacity(0), _size(0) {}

		/*
		**	Fill constructor
		**	Constructs a container with n elements. Each element is a copy of val.
		*/
		explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type())
		{
			_allocator = alloc;
			_vector = _allocator.allocate(_capacity);
			_size = n;
			_capacity = n;

			for ( iterator i = _vector; i < _vector + size; i++)
			{
				_allocator.construct(i, val);
			}
		}

		/*
		**	Range constructor
		**	Constructs a container with as many elements as the range [first, last).
		*/
		template <class InputIterator>
		vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type())
		{
			_allocator = alloc;
			_size = std::distance<InputIterator>(first, last);
			_capacity = _size;
			_vector = _allocator.allocate(_capacity);

			while (iterator i = _vector; i < vector + size; i++)
			{
				_allocator.construct(i, *first);
				++first;
			}
		}

		//copy constructor
		vector (const vector& other);

		//desctructor
		~vector()
		{
			for (iterator i = begin(); i < end(); i++)
			{
				_allocator.destroy(&(*i));
			}
			_allocator.deallocate(_vector, _capacity);
			_vector = nullptr;
			_size = 0;
			_capacity = 0;
		}

		//assign operator
		vector& operator=(const vector& other);


    /* ------------------------------------------------------------- */
    /* ITERATORS
    /* ------------------------------------------------------------- */
	public:
		/*
		**	ft::vector::begin()
		**		Returns an iterator to the first element of the vector.
		**		If empty, should not be dereferenced.	
		*/
		iterator begin() { return iterator(_vector); }
		const_iterator begin() const { return const_iterator(_vector); }

		/*
		**	ft::vector::end()
		**		Returns an iterator to the past-the-end element the vector.
		**		It does not point to any element, and thus shall not be dereferenced.
		**		If empty, returns the same as vector::begin().
		*/
		iterator end() { return iterator(_vector + size); }
		const_iterator end const () { return const_iterator(_vector + size); }

		/*
		**	ft::vector::rbegin()
		**		Returns a reverse iterator to the last element of the vector.
		**		If empty, should not be dereferenced.	
		*/
		reverse_iterator rbegin() { return reverse_iterator(_vector + size - 1); }
		const_reverse_iterator rbegin() const { return const_reverse_iterator(_vector + size - 1); }

		/*
		**	ft::vector::rend()
		**		Returns a reverse iterator to the theoretical element preceding the first element of the vector.
		**		It does not point to any element, and thus shall not be dereferenced.
		*/
		reverse_iterator rend() { return reverse_iterator(_vector - 1); }
		const_reverse_iterator rend() const { return const_reverse_iterator(_vector - 1); }
	

    /* ------------------------------------------------------------- */
    /* CAPACITY
    /* ------------------------------------------------------------- */
	public:
		

	}; //class Vector

} //namespace ft
