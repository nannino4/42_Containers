#pragma once

#include <memory>
#include <functional>
#include "pair.hpp"
#include "bidirectional_iterator.hpp"
#include "reverse_iterator.hpp"

#define BLACK		0
#define RED			1
#define LEFT		0
#define RIGHT		1
#define left		child[LEFT]
#define right		child[RIGHT]
#define childDir(N) ( N == (N->parent)->right ? RIGHT : LEFT )

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
			value_compare(key_compare c = key_compare()) : comp(c) {}
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
			Node		*child[2];
			bool		color;
		}


    //------------------------------------------------------------- */
    // ATTRIBUTES
    //------------------------------------------------------------- */
	private:
		Node					*_root;
		size_type				_size;
		key_compare				_compare;
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
		iterator		begin() { return iterator(min(_root), _root); }
		const_iterator	begin() { return const_iterator(min(_root), _root); }
		iterator		end() { return iterator(nullptr, _root); }
		const_iterator	end() { return const_iterator(nullptr, _root); }

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
		size_type	max_size() const { return allocNode.max_size(); }

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
		// insert single element
		pair<iterator,bool> insert(const value_type &val)
		{
			// check if val already exists
			if (find(val.first) != end())
				return pair<find(val.first), false>;

			// create new node n
			++_size;
			Node *n = _allocNode.allocate(1);
			n->value = val;
			n->color = RED;
			n->left = nullptr;
			n->right = nullptr;
			n->parent = nullptr;

			// find parent node p
			Node *p = _root;
			Node *tmp = _root;
			while (tmp)
			{
				p = tmp;
				if (value_comp()(tmp->val, n->val))
					tmp = tmp->right;
				else
					tmp = tmp->left;
			}

			// insert n
			n->parent = p;
			if (p)
			{
				if (value_comp()(p->value, n->value))
					p->right = n;
				else
					p->left = n;
			}

			// rebalance
			rebalance(n);

			// return
			return (make_pair(iterator(n, _root), true));
		}

		// insert with hint
		iterator insert(iterator position, const value_type &val)
		{
			// check if hint is correct
			if (position.getNode() && value_comp()(*position, val) &&
					(!(position + 1).getNode() || value_comp()(val, *(position + 1))))
			{
				// parent is in position
				Node *p = position.getNode();

				// create new node n
				++_size;
				Node *n = _allocNode.allocate(1);
				n->value = val;
				n->color = RED;
				n->left = nullptr;
				n->right = nullptr;
				n->parent = p;

				// insert n
				p->right = n;

				// rebalance
				rebalance(n);

				return (iterator(n, _root));
			}
			return (insert(val)).first;
		}

		// insert range
		template<class InputIterator>
		void insert(InputIterator first, InputIterator last)
		{
			for (InputIterator it = first; it != last; ++it)
				insert(*InputIterator);
		}

		void erase(iterator position)
		{
			Node *N = position.getNode();

			// N is _root && has NO child
			if (N == _root && !N->left && !N->right)
			{
				_allocNode.destroy(N);
				_allocNode.deallocate(N, 1);
				_root = nullptr;
				return ;
			}

			// N has 2 children
			if (N->left && N->right)
				swapNodes(N, (position - 1).getNode());

			// from now on N has at most 1 child

			if (N->color == RED)	// N is RED && has 0 children
			{
				if (N != _root)
					N->parent->child[childDir(N)] = nullptr;
				_allocNode.destroy(N);
				_allocNode.deallocate(N, 1);
				return ;
			}
			else					// N is BLACK && has at most 1 RED child
			{
				if (N->left)				// N has 1 child (left)
				{
					if (N->parent)
						N->parent->child[childDir(N)] = N->left;
					N->left->parent = N->parent;
					N->left->color = BLACK;
					_allocNode.destroy(N);
					_allocNode.deallocate(N, 1);
					return ;
				}
				else if (N->right)			// N has 1 child (right)
				{
					if (N->parent)
						N->parent->child[childDir(N)] = N->right;
					N->right->parent = N->parent;
					N->right->color = BLACK;
					_allocNode.destroy(N);
					_allocNode.deallocate(N, 1);
					return ;
				}
				else						// N has NO child
				{
					// TODO
				}
			}
		}

    //------------------------------------------------------------- */
    // OBSERVERS
    //------------------------------------------------------------- */
	public:
		key_compare		key_comp() const { return _compare; }
		valye_compare	value_comp() const { return value_compare(_compare); }

    //------------------------------------------------------------- */
    // OPERATIONS
    //------------------------------------------------------------- */
	public:
		iterator	find(const key_type &key)
		{
			Node *node = _root;

			while (node)
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

			while (node)
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

			while (node)
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

			while (node)
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

			while (node)
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

			while (node)
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

		void swapNodes(Node *n1, Node *n2)
		{
			Node tmp = *n2;

			if (n1->parent)
				n1->parent->child[childDir(n1)] = n2;
			if (n2->parent)
				n2->parent->child[childDir(n2)] = n1;
			if (n1->left)
				n1->left->parent = n2;
			if (n1->right)
				n1->right->parent = n2;
			if (n2->left)
				n2->left->parent = n1;
			if (n2->right)
				n2->right->parent = n1;

			n2->value = n1->value;
			n2->parent = n1->parent;
			n2->left = n1->left;
			n2->right = n1->right;
			n2->color = n1->color;
			
			n1->value = tmp->value;
			n1->parent = tmp->parent;
			n1->left = tmp->left;
			n1->right = tmp->right;
			n1->color = tmp->color;
		}

		Node *rotate(Node *p, Node *n)
		{
			Node *g = p->parent;
			bool dir = childDir(n);

			p->child[dir] = n->child[1 - dir];
			if (p->child[dir])
				(p->child[dir])->parent = p;
			if (g)
				g->child[childDir(p)] = n;
			else
				_root = n;
			n->parent = g;
			n->child[1 - dir] = p;
			p->parent = n;
		}

		void  rebalanceIn(Node *n)
		{
			Node *p = n->parent;
			if (!p)
				return rebalanceInCase3(n);
			if (p->color == BLACK)
				return rebalanceInCase1();
			// P is RED
			Node *g = p->parent;					// g = grandparent of n
			if (!g)
				return rebalanceInCase4(p);			// p is RED && _root
			// p is RED && not _root
			Node *u = g->child[1 - childDir(p)];	// u = uncle of n
			if (!u || u->color == BLACK)
				return rebalanceInCase56(n, p, g, u);	// p RED && u BLACK
			return rebalanceInCase2(n, p, g, u);		// p+u RED
		}

		void rebalanceInCase1()
		{
			return ;
		}

		void rebalanceInCase2(Node *n, Node *p, Node *g, Node *u)
		{
			// p+u RED (g BLACK)
			p->color = BLACK;
			u->color = BLACK;
			g->color = RED;
			rebalance(g);
		}

		void rebalanceInCase3(Node *n)
		{
			_root = n;
		}

		void rebalanceInCase4(Node *p)
		{
			p->color = BLACK;
		}

		void rebalanceInCase56(Node *n, Node *p, Node *g, Node *u)
		{
			if (childDir(n) != childDir(p))
			{
				// case 5:
				// p RED && u BLACK
				// n is INNER child of p
				rotate(p, n);
				n = p;
				p = n->parent;
			}
			// case 6:
			// p RED && u BLACK
			// n is OUTER child of p
			rotate(g, p);
			p->color = BLACK;
			g->color = RED;
		}

		Node *min(Node *node)
		{
			while (node && node->left)
				node = node->left;
			return (node);
		}

	// 	Node *max(Node *node)
	// 	{
	// 		while (node && node->right)
	// 			node = node->right;
	// 		return (node);
	// 	}

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
