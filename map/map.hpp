#pragma once

#include <memory>
#include <functional>
#include "pair.hpp"
#include "bidirectional_iterator.hpp"
#include "reverse_iterator.hpp"

#define BLACK 0
#define RED 1

namespace ft
{
	template <class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<pair<const Key, T> > >
	class map
	{

    //------------------------------------------------------------- */
    // MEMBER TYPES
    //------------------------------------------------------------- */
	public:
		typedef Key															key_type;
		typedef T															mapped_type;
		typedef pair<const key_type,mapped_type>							value_type;
		typedef Alloc														allocator_type;
		typedef ptrdiff_t													difference_type;
		typedef size_t														size_type;

		typedef Compare														key_compare;
		class																value_compare
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

		typedef allocator_type::reference 									reference;
		typedef allocator_type::const_reference								const_reference;
		typedef allocator_type::pointer										pointer;
		typedef allocator_type::const_pointer								const_pointer;

		typedef bidirectional_iterato<value_type,ft::node<value_type>		iterator;
		typedef bidirectional_iterato<const value_type,ft::node<value_type>	const_iterator;
		typedef reverse_iterator<iterator>									reverse_iterator;
		typedef reverse_iterator<const_iterator>							const_reverse_iterator;

		struct Node
		{
			value_type	value;
			Node		*parent;
			Node		*right;
			Node		*left;
			bool		color;
		}


    //------------------------------------------------------------- */
    // ATTRIBUTES
    //------------------------------------------------------------- */
	private:
		Node					*_root;
		Node					*_pacmanNode;	// max() -> _pacmanNode -> min()
		key_compare				_compare;
		size_type				_size;
		allocator_type			_allocPair;
		std::allocator<Node>	_allocNode;

    //------------------------------------------------------------- */
    // COPLIEN FORM
    //------------------------------------------------------------- */
	public:
		// default constructor = empty
		explicit map(const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type())
		{
			//TODO
		}

		// range constructor
		template <class InputIterator>
		map(InputIterator first, InputIterator last, const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type())
		{
			//TODO
		}

		// copy constructor
		map(const map &other) { *this = other; }

		// assign operator
		map &operator=(const map &other)
		{
			if (this != &other)
			{
				//TODO
			}
		}

    //------------------------------------------------------------- */
    // ITERATORS
    //------------------------------------------------------------- */
	public:
		iterator		begin() { return iterator(_pacmanNode->right, _root); }
		const_iterator	begin() { return const_iterator(_pacmanNode->right, _root); }
		iterator		end() { return iterator(_pacmanNode, _root); }
		const_iterator	end() { return const_iterator(_pacmanNode, _root); }

		reverse_iterator		rbegin() { return reverse_iterator(end()); }
		const_reverse_iterator	rbegin() { return const_reverse_iterator(end()); }
		reverse_iterator		rend() { return reverse_iterator(begin()); }
		const_reverse_iterator	rbegin() { return const_reverse_iterator(end()); }

    //------------------------------------------------------------- */
    // CAPACITY
    //------------------------------------------------------------- */
	public:
		bool		empty() const { return !_size; }
		size_type	size() const { return _size; }
		size_type	max_size() const { return }

    //------------------------------------------------------------- */
    // ELEMENT ACCESS
    //------------------------------------------------------------- */
	public:
		mapped_type &operator[](const key_type &key)
		{
			iterator *it = find(key);
			if (it.getNode())
				return (it.getValue().second);
			else
			{
				value_type value = make_pair<key_type, mapped_type>(k, mapped_type());
				//TODO
				// return (insert(value)->value.second);
			}
		}

    //------------------------------------------------------------- */
    // MODIFIERS
    //------------------------------------------------------------- */
	public:
		pair<iterator,bool> insert(const value_type &val)
		{
			if (find(val.first) != end())
				return pair<find(val.first), false>;
			else
			{
				iterator it = upper_bound(val.first);
				//TODO insert
			}
		}

    //------------------------------------------------------------- */
    // OBSERVERS
    //------------------------------------------------------------- */
	public:
		key_compare		key_comp() const { return _compare; }
		valye_compare	value_comp() const { return value_compare(_compare); }
		size_type		max_size() const { return allocNode.max_size(); }

    //------------------------------------------------------------- */
    // OPERATIONS
    //------------------------------------------------------------- */
	public:
		iterator	find(const key_type &key)
		{
			Node *node = _root;

			while (node && node != _pacmanNode)
			{
				if (areKeysEqual(key, node->value.first))
					return iterator(node, _root);
				else if (_compare(key, node->value.first))
					node = node->left;
				else
					node = node->right;
			}
			return end();
		}

		const_iterator	find(const key_type &key)
		{
			Node *node = _root;

			while (node && node != _pacmanNode)
			{
				if (areKeysEqual(key, node->value.first))
					return const_iterator(node, _root);
				else if (_compare(key, node->value.first))
					node = node->left;
				else
					node = node->right;
			}
			return end();
		}

		size_type count(const key_type &key) const
		{
			if (find(key) == end())
				return 0;
			else
				return 1;
		}

		iterator lower_bound(const key_type &key)
		{
			iterator ret = end();
			Node *node = _root;

			while (node && node != _pacmanNode)
			{
				if (!_compare(node->value.first, key))
				{
					ret = iterator(node, _root);
					node = node->left;
				}
				else
					node = node->right;
			}
			return (ret);
		}

		const_iterator lower_bound(const key_type &key)
		{
			const_iterator ret = end();
			Node *node = _root;

			while (node && node != _pacmanNode)
			{
				if (!_compare(node->value.first, key))
				{
					ret = const_iterator(node, _root);
					node = node->left;
				}
				else
					node = node->right;
			}
			return (ret);
		}

		iterator upper_bound(const key_type &key)
		{
			iterator ret = end();
			Node *node = _root;

			while (node && node != _pacmanNode)
			{
				if (_compare(key, node->value.first))
				{
					ret = iterator(node, _root);
					node = node->left;
				}
				else
					node = node->right;
			}
			return (ret);
		}

		const_iterator upper_bound(const key_type &key)
		{
			const_iterator ret = end();
			Node *node = _root;

			while (node && node != _pacmanNode)
			{
				if (_compare(key, node->value.first))
				{
					ret = const_iterator(node, _root);
					node = node->left;
				}
				else
					node = node->right;
			}
			return (ret);
		}

		pair<iterator,iterator> equal_range(const key_type &key) const
		{
			pair<iterator,iterator> ret;

			ret.first = lower_bound(key);
			ret.second = upper_bound(key);
		}

		pair<iterator,iterator> equal_range(const key_type &key) const
		{
			pair<iterator,iterator> ret;

			ret.first = lower_bound(key);
			ret.second = upper_bound(key);
		}

    //------------------------------------------------------------- */
    // ALLOCATOR
    //------------------------------------------------------------- */
	public:
		allocator_type	get_allocator() const { return _allocPair; }

	
    //------------------------------------------------------------- */
    // PRIVATE MEMBER FUNCTIONS
    //------------------------------------------------------------- */
	private:
		bool areKeysEqual(key_type lhs, key_type rhs) { return (!_compare(lhs, rhs) && !_compare(rhs, lhs)); }

	// 	Node *max(Node *node)
	// 	{
	// 		while (node && node->right && node->right != _pacmanNode)
	// 			node = node->right;
	// 		return (node);
	// 	}

	// Node *min(Node *node)
	// {
	// 	while (node && node->left && node->left != _pacmanNode)
	// 		node = node->left;
	// 	return (node);
	// }

	// 	Node *successor(Node *node)
	// 	{
	// 		if (!node)
	// 			return (nullptr);
	// 		if (node->right)
	// 			return (min(node->right));

	// 		Node *parent = node->parent;
	// 		while (parent && node == parent->right)
	// 		{
	// 			node = parent;
	// 			parent = parent->parent;
	// 		}
	// 		return (parent);
	// 	}

	// 	Node *predecessor(Node *node)
	// 	{
	// 		if (!node)
	// 			return (nullptr);
	// 		if (node->left)
	// 			return (max(node->left));

	// 		Node *parent = node->parent;
	// 		while (parent && node == parent->left)
	// 		{
	// 			node = parent;
	// 			parent = parent->parent;
	// 		}
	// 		return (parent);
	// 	}

	}; // class map

} // namespace ft
