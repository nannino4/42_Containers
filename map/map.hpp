#pragma once

#include <memory>
#include <functional>
#include "pair.hpp"
#include "bidirectional_iterator.hpp"
#include "reverse_iterator.hpp"
#include "rb_tree.hpp"

namespace ft
{
	template <class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<pair<const Key, T> > >
	class map
	{

    //------------------------------------------------------------- */
    // MEMBER TYPES
    //------------------------------------------------------------- */
	public:
		typedef Key									key_type;
		typedef T									mapped_type;
		typedef pair<const key_type,mapped_type>	value_type;
		typedef Alloc								allocator_type;
		typedef ptrdiff_t							difference_type;
		typedef size_t								size_type;

		typedef Compare		key_compare;
		class				value_compare
		{
			friend class map;
		protected:
			key_compare comp;
			value_compare(key_compare c) : comp(c) {}
		public:
			typedef bool result_type;
			typedef value_type first_argument_type;
			typedef value_type second_argument_type;
			bool operator()(const value_type &x, const value_type &y) const
				return comp(x.first, y.first);
		}

		typedef allocator_type::reference 			reference;
		typedef allocator_type::const_reference		const_reference;
		typedef allocator_type::pointer				pointer;
		typedef allocator_type::const_pointer		const_pointer;

		typedef bidirectional_iterato<value_type,ft::node<value_type>		iterator;
		typedef bidirectional_iterato<const value_type,ft::node<value_type>	const_iterator;
		typedef reverse_iterator<iterator>									reverse_iterator;
		typedef reverse_iterator<const_iterator>							const_reverse_iterator;


    //------------------------------------------------------------- */
    // ATTRIBUTES
    //------------------------------------------------------------- */
	private:
		rb_tree	_tree;

    //------------------------------------------------------------- */
    // COPLIEN FORM
    //------------------------------------------------------------- */

    //------------------------------------------------------------- */
    // ITERATORS
    //------------------------------------------------------------- */

    //------------------------------------------------------------- */
    // CAPACITY
    //------------------------------------------------------------- */

    //------------------------------------------------------------- */
    // ELEMENT ACCESS
    //------------------------------------------------------------- */

    //------------------------------------------------------------- */
    // MODIFIERS
    //------------------------------------------------------------- */

    //------------------------------------------------------------- */
    // OBSERVERS
    //------------------------------------------------------------- */

    //------------------------------------------------------------- */
    // OPERATIONS
    //------------------------------------------------------------- */

    //------------------------------------------------------------- */
    // ALLOCATOR
    //------------------------------------------------------------- */

	}; // class map

} // namespace ft
