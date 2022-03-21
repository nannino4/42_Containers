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
			Default constructor
			Constructs an empty container with no elements
		*/
		explicit vector (const allocator_type& alloc = allocator_type()) : _allocator(alloc), _vector(nullptr), _capacity(0), _size(0) {}

		/*
			Fill constructor
			Constructs a container with n elements. Each element is a copy of val.
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
			Range constructor
			Constructs a container with as many elements as the range [first, last).
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
		//TODO
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
		//TODO
		vector& operator=(const vector& other);


    /* ------------------------------------------------------------- */
    /* ITERATORS
    /* ------------------------------------------------------------- */
	public:
		/*
			ft::vector::begin()
				Returns an iterator to the first element of the vector.
				If empty, should not be dereferenced.	
		*/
		iterator begin() { return iterator(_vector); }
		const_iterator begin() const { return const_iterator(_vector); }

		/*
			ft::vector::end()
				Returns an iterator to the past-the-end element the vector.
				It does not point to any element, and thus shall not be dereferenced.
				If empty, returns the same as vector::begin().
		*/
		iterator end() { return iterator(_vector + size); }
		const_iterator end const () { return const_iterator(_vector + size); }

		/*
			ft::vector::rbegin()
				Returns a reverse iterator to the last element of the vector.
				If empty, should not be dereferenced.	
		*/
		reverse_iterator rbegin() { return reverse_iterator(_vector + size - 1); }
		const_reverse_iterator rbegin() const { return const_reverse_iterator(_vector + size - 1); }

		/*
			ft::vector::rend()
				Returns a reverse iterator to the theoretical element preceding the first
					element of the vector.
				It does not point to any element, and thus shall not be dereferenced.
		*/
		reverse_iterator rend() { return reverse_iterator(_vector - 1); }
		const_reverse_iterator rend() const { return const_reverse_iterator(_vector - 1); }
	

    /* ------------------------------------------------------------- */
    /* CAPACITY
    /* ------------------------------------------------------------- */
	public:
		/*
			ft::vector::size()
				Returns the number of elements in the vector.
				This is the number of actual objects held in the vector, which is not necessarily
					equal to its storage capacity.
		*/
		size_type size() const { return _size; }

		/*
			ft::vector::max_size()
				Returns the maximum number of elements that the vector can hold.
				This is the maximum potential size the container can reach due to known system
					or library implementation limitations, but the container is by no means guaranteed
					to be able to reach that size: it can still fail to allocate storage at any point
					before that size is reached.
		*/
		size_type max_size() const { return _allocator.max_size(); }

		/*
			ft::vector::resize()
				Resizes the container so that it contains n elements.
				If n is smaller than the current container size, the content is reduced to its
					first n elements, removing those beyond (and destroying them).
				If n is greater than the current container size, the content is expanded by inserting
					at the end as many elements as needed to reach a size of n. If val is specified,
					the new elements are initialized as copies of val, otherwise, they are
					value-initialized.
				If n is also greater than the current container capacity, an automatic reallocation
					of the allocated storage space takes place.
		*/
		void resize(size_type n, value_type val = value_type())
		{
			if (n > this->max_size())
				throw (std::length_error("Error: cannot resize vector: new_size > max_size()"));
			else if (n > _capacity)
				reallocate(n);
			while (n > _size)
				push_back(val);
			while (n < _size)
				pop_back();
		}

		/*
			ft::vector::capacity()
			Returns the size of the storage space currently allocated for the vector,
				expressed in terms of elements.
		*/
		size_type capacity() const { return _capacity; }

		/*
			ft::vector::empty()
				Returns whether the vector is empty (i.e. whether its size is 0).
		*/
		bool empty() const { return (_size == 0); }

		/*
			ft::vector::reserve()
				Requests that the vector capacity be at least enough to contain n elements.
		*/
		void reserve(size_type n)
		{
			if (n > this->max_size())
				throw (std::length_error("Error: cannot reserve vector: reserve_size > max_size()"));
			if (n > _capacity)
				reallocate(n);
		}


    /* ------------------------------------------------------------- */
    /* ELEMENT ACCESS
    /* ------------------------------------------------------------- */
	public:
		/*
			ft::vector::operator[]
				Returns a reference to the element at position n in the vector container.
				Undefined behavior if n is outside vector's range.
		*/
		reference operator[](size_type n) { return _vector[n]; }
		const_reference operator[](size_type n) const { return _vector[n]; }

		/*
			ft::vector::at()
				Returns a reference to the element at position n in the vector.
				The function automatically checks whether n is within the bounds of valid elements
					in the vector, throwing an out_of_range exception if it is not (i.e., if n is
					greater than, or equal to, its size).
		*/
		reference at(size_type n)
		{
			if (n >= _size)
			throw std::out_of_range("Error: cannot access vector element: element_position >= size()");
			return _vector[n];
		}
		const_reference at(size_type n) const
		{
			if (n >= _size)
			throw std::out_of_range("Error: cannot access vector element: element_position >= _size()");
			return _vector[n];
		}

		/*
			ft::vector::front()
				Returns a reference to the first element in the vector.
				Calling this function on an empty container causes undefined behavior.
		*/
		reference front() {return _vector[0]; }
		const_reference front() const {return _vector[0]; }

		/*
			ft::vector::back()
				Returns a reference to the last element in the vector.
				Calling this function on an empty container causes undefined behavior.
		*/
		reference back() {return _vector[_size - 1]; }
		const_reference back() const {return _vector[_size - 1]; }


    /* ------------------------------------------------------------- */
    /* MODIFIERS
    /* ------------------------------------------------------------- */
	public:
		/*
			ft::vector::assign()
				Assigns new contents to the vector, replacing its current contents,
					and modifying its size accordingly.
		*/
		//range
		template <class InputIterator>
		void assign(InputIterator first, InputIterator last)
		{
			clear();
			
			size_type newSize = last - first;
			if (newSize > _capacity)
			{
				_allocator.deallocate(_vector, _capacity);
				_vector = _allocator.allocate(newSize);
				_capacity = newSize;
			}
			for (size_type i; first != last; ++i, ++first)
				_allocator.construct(&_vector[i], *first);
			_size = newSize;
		}

		//fill
		void assign(size_type n, const value_type& val)
		{
			clear();

			if (n > _capacity)
			{
				_allocator.deallocate(_vector, _capacity);
				_vector = _allocator.allocate(n);
				_capacity = n;
			}
			for (size_type i; i < n; ++i)
				_allocator.construct(&_vector[n], val);
			_size = n;
		}

		/*
			ft::vector::push_back()
				Adds a new element at the end of the vector, after its current last element.
					The content of val is copied (or moved) to the new element.
				This effectively increases the container size by one, which causes an automatic
					reallocation of the allocated storage space if -and only if- the new vector
					size surpasses the current vector capacity.
		*/
		void push_back(const value_type& val)
		{
			if (_size + 1 > _capacity)
				reallocateVec(!_capacity ? 1 : _capacity * 2);
			_allocator.construct(&_vector[_size++], val);
		}

		/*
			ft::vector::pop_back()
				Removes the last element in the vector, effectively reducing the container size by one.
				This destroys the removed element.
		*/
		void pop_back()
		{
			if (_size)
                _allocator.destroy(&_vector[--_size]);
		}

		/*
			ft::vector::insert()
				The vector is extended by inserting new elements before the element at the specified position,
					effectively increasing the container size by the number of elements inserted.
		*/
		//single element
		iterator insert(iterator position, const value_type& val)
		{
			// In case of a realloc, position will be invalited because _vector
			// points to another allocated area so we need to save the index array
			// where position iterator is pointing to create a new one after the reallocation
			difference_type index = position - begin();
			insert(position, 1, val);
			return (iterator(&_vector[index]));
		}

		//fill
		void insert(iterator position, size_type n, const value_type& val)
		{
			if (n < 0)
				throw (std::length_error("Error: cannot insert: n < 0."));
			else if (n == 0)
				return ;
			else if (n > this->max_size())
				throw (std::length_error("Error: cannot insert: n > max_size()."));
			// In case of a realloc, position will be invalited because _vector
			// points to another allocated area so we need to save the index array
			// where position iterator is pointing to create a new one after the reallocation
			difference_type index = position - begin();

			if (_size + n > _capacity)
				reallocate(_capacity + n);

			// Creating a new iterator pointing to the correct allocated are (case a realloc occured previously)
			iterator newPosition(&_vector[index]);

			// Moving at newPosition + n all elements after newPosition
			if (newPosition != end())
				shiftElementsToTheRight(newPosition, n);

			// Constructing n new elements from val
			for (size_type i = 0; i < n; ++i)
				_alloc.construct(&(*newPosition++), val);
			_size += n;
		}
		//range
		template <class InputIterator>
		void insert(iterator position, InputIterator first, InputIterator last)
		{
			size_type n = last - first;

			// In case of a realloc, position will be invalited because _vector
			// points to another allocated area so we need to save the index array
			// where position iterator is pointing to create a new one after the reallocation
			difference_type index = position - begin();

			if (_size + n > _capacity)
				reallocate(_capacity + n);

			// Creating a new iterator pointing to the correct allocated are (case a realloc occured previously)
			iterator newPosition(&_vector[index]);

			// Moving at newPosition + n all elements after newPosition
			if (newPosition != end())
				shiftElementsToTheRight(newPosition, n);

			// Constructing n new elements from range
			for (size_type i = 0; i < n; ++i)
				_alloc.construct(&(*newPosition++), *first++);
			_size += n;
		}

		/*
			ft::vector::erase()
				Removes from the vector either a single element (position) or a range of elements ([first,last)).
		*/
		//single element
		iterator erase(iterator position)
		{
			return erase(position, position + 1);
		}

		//range
		iterator erase(iterator first, iterator last)
		{

		}


    /* ------------------------------------------------------------- */
    /* PRIVATE MEMBER FUNCTIONS
    /* ------------------------------------------------------------- */
	private:
		/*
			reallocate(size_type newCapacity)
				Allocates a new _vector with _capacity = newCapacity, copies the elements of the
					old _vector in it, and destroys and deallocates the old _vector.
				The _allocator may throw bad_alloc expections.
		*/
		void reallocate(size_type newCapacity)
		{
			pointer new_vector = _allocator.allocate(newCapacity);
			for (size_type i = 0; i < _size; i++)
				new_vector[i] = _allocator.construct(&new_vector[i], _vector[i]);
			this->~vector();
			_capacity = newCapacity;
			_vector = new_vector;
		}

		void shiftElementsToTheRight(iterator position, size_type n)
		{

			for (iterator it = end() - 1; it >= position; --it)
			{
				_allocator.construct(&(*(it + n)), *it);
				_allocator.destroy(&(*it));
			}
		}

	}; //class Vector

} //namespace ft
