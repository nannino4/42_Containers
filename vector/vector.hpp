#pragma once

#include <memory>
#include "iterator.hpp"
#include "random_access_iterator.hpp"
#include "reverse_iterator.hpp"
#include "equal.hpp"
#include "lexicographical_compare.hpp"

namespace ft
{
    template <class T, class Allocator = std::allocator<T> >
	class vector
	{

    //------------------------------------------------------------- */
    //MEMBER TYPES
    //------------------------------------------------------------- */
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


    //------------------------------------------------------------- */
    //ATTRIBUTES
    //------------------------------------------------------------- */
	private:
		allocator_type	_allocator;
		pointer			_vector;
		size_type		_size;
		size_type		_capacity;


    //------------------------------------------------------------- */
    //COPLIEN FORM
    //------------------------------------------------------------- */
	public:
		/*
			Default constructor
			Constructs an empty container with no elements
		*/
		explicit vector(const allocator_type& alloc = allocator_type()) : _allocator(alloc), _vector(nullptr), _size(0), _capacity(0) {}

		/*
			Fill constructor
			Constructs a container with n elements. Each element is a copy of val.
		*/
		explicit vector(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type())
		{
			_allocator = alloc;
			_size = n;
			_capacity = n;
			_vector = _allocator.allocate(_capacity);

			for ( iterator i = _vector; i < _vector + _size; i++)
			{
				_allocator.construct(&(*i), val);
			}
		}

		/*
			Range constructor
			Constructs a container with as many elements as the range [first, last).
		*/
		vector(iterator first, iterator last, const allocator_type& alloc = allocator_type())
		{
			_allocator = alloc;
			_size = ft::distance<iterator>(first, last);
			_capacity = _size;
			_vector = _allocator.allocate(_capacity);

			for (iterator i = _vector; i < _vector + _size; i++)
			{
				_allocator.construct(&(*i), *first);
				++first;
			}
		}

		vector(const_iterator first, const_iterator last, const allocator_type& alloc = allocator_type())
		{
			_allocator = alloc;
			_size = ft::distance<const_iterator>(first, last);
			_capacity = _size;
			_vector = _allocator.allocate(_capacity);

			for (iterator i = _vector; i < _vector + _size; i++)
			{
				_allocator.construct(&(*i), *first);
				++first;
			}
		}

		//copy constructor
		vector(const vector& other)
		{
			vector();
			*this = other;
		}

		//destructor
		~vector()
		{
			clear();
			_allocator.deallocate(_vector, _capacity);
		}

		//assign operator
		vector& operator=(const vector& other)
		{
			if (this != &other)
			{
				this->~vector();
				_allocator = other.get_allocator();
				_size = other.size();
				_capacity = other.capacity();
				_vector = _allocator.allocate(_capacity);
				for (size_type i = 0; i < other.size(); ++i)
				{
					_allocator.construct(&_vector[i], other[i]);
				}
			}
			return *this;
		}


    //------------------------------------------------------------- */
    //ITERATORS
    //------------------------------------------------------------- */
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
		iterator end() { return iterator(_vector + _size); }
		const_iterator end() const { return const_iterator(_vector + _size); }

		/*
			ft::vector::rbegin()
				Returns a reverse iterator to the last element of the vector.
				If empty, should not be dereferenced.	
		*/
		reverse_iterator rbegin() { return reverse_iterator(_vector + _size - 1); }
		const_reverse_iterator rbegin() const { return const_reverse_iterator(_vector + _size - 1); }

		/*
			ft::vector::rend()
				Returns a reverse iterator to the theoretical element preceding the first
					element of the vector.
				It does not point to any element, and thus shall not be dereferenced.
		*/
		reverse_iterator rend() { return reverse_iterator(_vector - 1); }
		const_reverse_iterator rend() const { return const_reverse_iterator(_vector - 1); }
	

    //------------------------------------------------------------- */
    //CAPACITY
    //------------------------------------------------------------- */
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


    //------------------------------------------------------------- */
    //ELEMENT ACCESS
    //------------------------------------------------------------- */
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


    //------------------------------------------------------------- */
    //MODIFIERS
    //------------------------------------------------------------- */
	public:
		/*
			ft::vector::assign()
				Assigns new contents to the vector, replacing its current contents,
					and modifying its size accordingly.
		*/
		//range
		void assign(iterator first, iterator last)
		{
			clear();
			
			size_type newSize = last - first;
			if (newSize > _capacity)
			{
				_allocator.deallocate(_vector, _capacity);
				_vector = _allocator.allocate(newSize);
				_capacity = newSize;
			}
			for (size_type i = 0; first != last; ++i, ++first)
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
			for (size_type i = 0; i < n; ++i)
				_allocator.construct(&_vector[i], val);
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
				reallocate(!_capacity ? 1 : _capacity * 2);
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
			// In case of a realloc, position will be invalidated because _vector
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

			// In case of a realloc, position will be invalidated because _vector
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
				_allocator.construct(&(*newPosition++), val);
			_size += n;
		}

		//range
		void insert(iterator position, iterator first, iterator last)
		{
			size_type n = last - first;

			// In case of a realloc, position will be invalidated because _vector
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
				_allocator.construct(&(*newPosition++), *first++);
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
			if (first == end() || first == last)
				return first;

			if (last < end())
			{
				shiftElementsToTheLeft(first, last);
				_size -= last - first;
			}
			else
			{
				size_type newSize = _size - (last - first);
				while (_size != newSize)
					pop_back();
			}
			return first;
		}

		/*
			ft::vector::swap()
				Exchanges the content of the container by the content of x, which is
					another vector object of the same type. Sizes may differ.
		*/
		void swap(vector &x)
		{
			size_type		tmpSize = _size;
			size_type		tmpCapacity = _capacity;
			pointer			tmpPointer = _vector;
			allocator_type	tmpAlloc = _allocator;

			_size = x.size();
			_capacity = x.capacity();
			_vector = x._vector;
			_allocator = x._allocator;

			x._size = tmpSize;
			x._capacity = tmpCapacity;
			x._vector = tmpPointer;
			x._allocator = tmpAlloc;
		}

		/*
			ft::vector::clear()
				Removes all elements from the vector (which are destroyed),
					leaving the container with a size of 0.
		*/
		void clear()
		{
			while (_size)
				pop_back();
		}


    //------------------------------------------------------------- */
    //ALLOCATOR
    //------------------------------------------------------------- */
	public:
		/*
			ft::vector::get_allocator()
				Returns a copy of the allocator object associated with the vector.
		*/
		allocator_type get_allocator() const { return _allocator; }


    //------------------------------------------------------------- */
    //PRIVATE MEMBER FUNCTIONS
    //------------------------------------------------------------- */
	private:
		void reallocate(size_type newCapacity)
		{
			size_type oldSize = _size;
			pointer new_vector = _allocator.allocate(newCapacity);
			for (size_type i = 0; i < _size; i++)
				_allocator.construct(&new_vector[i], _vector[i]);
			this->~vector();
			_size = oldSize;
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

		void shiftElementsToTheLeft(iterator first, iterator last)
		{
			difference_type n = last - first;
			for (iterator it = first; it + n != end(); ++it)
			{
				_allocator.destroy(&(*it));
				_allocator.construct(&(*it), *(it + n));
			}
		}

	}; //class Vector


//------------------------------------------------------------- */
//NON-MEMBER FUNCTION OVERLOADS
//------------------------------------------------------------- */
	//relational operators
	template <class T, class Alloc>
	bool operator==(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		if (lhs.size() != rhs.size())
			return false;
		return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
	}

	template <class T, class Alloc>
	bool operator!=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		if (lhs.size() != rhs.size())
			return true;
		return !(ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}

	template <class T, class Alloc>
	bool operator<(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template <class T, class Alloc>
	bool operator<=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return !(rhs < lhs);
	}

	template <class T, class Alloc>
	bool operator>(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return !(lhs <= rhs);
	}

	template <class T, class Alloc>
	bool operator>=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return !(lhs < rhs);
	}

	/*
		ft::swap()
			The contents of container x are exchanged with those of y. Both container objects
				must be of the same type (same template parameters), although sizes may differ.
	*/
	template <class T, class Alloc>
	void swap(vector<T,Alloc>& x, vector<T,Alloc>& y) { x.swap(y); }

} //namespace ft
