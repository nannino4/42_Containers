#pragma once

#include <memory>
#include "random_access_iterator.hpp"
#include "reverse_random_access_iterator.hpp"

namespace ft
{
    /**
    *   @param T        Type of container's elements.
    *   @param Allocator    Object used to manage the vector' storage.
    */
    template <class T, class Allocator = std::allocator<T> >
	class Vector
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
		typedef ft::reverse_random_access_iterator<iterator>		reverse_iterator;
		typedef ft::reverse_random_access_iterator<const_iterator>	const_reverse_iterator;
	};
}
