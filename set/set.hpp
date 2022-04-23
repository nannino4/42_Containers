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
	template <class T, class Compare = std::less<T>, class Alloc = std::allocator<T> >
	class set
	{

    //------------------------------------------------------------- */
    // MEMBER TYPES
    //------------------------------------------------------------- */
	public:
		typedef T												key_type;
		typedef T												value_type;

	private:
		struct Node
		{
			value_type	value;
			Node		*parent;
			Node		*child[2];
			bool		color;
		};

	public:
		typedef Compare											key_compare;
		typedef Compare											value_compare;

		typedef Alloc											allocator_type;
		typedef allocator_type::reference 						reference;
		typedef allocator_type::const_reference					const_reference;
		typedef allocator_type::pointer							pointer;
		typedef allocator_type::const_pointer					const_pointer;

		typedef bidirectional_iterator<value_type,Node>			iterator;
		typedef bidirectional_iterator<const value_type,Node>	const_iterator;
		typedef reverse_iterator<iterator>						reverse_iterator;
		typedef reverse_iterator<const_iterator>				const_reverse_iterator;

		typedef ptrdiff_t										difference_type;
		typedef size_t											size_type;


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
		explicit set(const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type())
		{
			_root = nullptr;
			_size = 0;
			_compare = comp;
			_allocPair = alloc;
		}

		// range constructor
		template <class InputIterator>
		set(InputIterator first, InputIterator last, const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type())
		{
			_root = nullptr;
			_size = 0;
			_compare = comp;
			_allocPair = alloc;
			insert(first, last);
		}

		// copy constructor
		set(const set &other) { *this = other; }

		// destructor
		~set() { clear(); }

		// assign operator
		set &operator=(const set &other)
		{
			if (this != &other)
			{
				clear();
				insert(other.begin(), other.end());
			}
			return *this;
		}

    //------------------------------------------------------------- */
    // ITERATORS
    //------------------------------------------------------------- */
	public:
		iterator		begin()			{ return iterator(min(_root), _root); }
		const_iterator	begin() const	{ return const_iterator(min(_root), _root); }
		iterator		end()			{ return iterator(nullptr, _root); }
		const_iterator	end() const		{ return const_iterator(nullptr, _root); }

		reverse_iterator		rbegin()		{ return reverse_iterator(end()); }
		const_reverse_iterator	rbegin() const	{ return const_reverse_iterator(end()); }
		reverse_iterator		rend()			{ return reverse_iterator(begin()); }
		const_reverse_iterator	rend() const	{ return const_reverse_iterator(begin()); }

    //------------------------------------------------------------- */
    // CAPACITY
    //------------------------------------------------------------- */
	public:
		bool		empty() const { return !_size; }
		size_type	size() const { return _size; }
		size_type	max_size() const { return _allocNode.max_size(); }

    //------------------------------------------------------------- */
    // MODIFIERS
    //------------------------------------------------------------- */
	public:
		// insert single element
		pair<iterator,bool> insert(const value_type &val)
		{
			// check if val already exists
			if (find(val) != end())
				return ft::make_pair(find(val), false);

			// create new node n
			++_size;
			Node *n = _allocNode.allocate(1);
			_allocPair.construct(&n->value, val);
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
				if (value_comp()(tmp->value, n->value))
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
			rebalanceIn(n);

			// return
			return (ft::make_pair(iterator(n, _root), true));
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
				_allocPair.construct(&n->value, val);
				n->color = RED;
				n->left = nullptr;
				n->right = nullptr;
				n->parent = p;

				// insert n
				p->right = n;

				// rebalance
				rebalanceIn(n);

				return (iterator(n, _root));
			}
			return (insert(val)).first;
		}

		// insert range
		template<class InputIterator>
		void insert(InputIterator first, InputIterator last)
		{
			for (InputIterator it = first; it != last; ++it)
				insert(*it);
		}

		// erase single
		void erase(iterator position)
		{
			Node *N = position.getNode();

			if (!N)
				return ;

			--_size;

			// N is _root && has NO child
			if (N == _root && !N->left && !N->right)
			{
				_allocNode.deallocate(N, 1);
				_root = nullptr;
				return ;
			}

			if (N->left && N->right)	// N has 2 children
			{
				swapNodes(N, (position - 1).getNode());
			}

			// from now on N has at most 1 child

			if (N->color == RED)		// N is RED && has 0 children
			{
				N->parent->child[childDir(N)] = nullptr;
				_allocNode.deallocate(N, 1);
				return ;
			}
			else						// N is BLACK && has at most 1 RED child
			{
				if (N->left)				// N has 1 child (left)
				{
					if (N->parent)
						N->parent->child[childDir(N)] = N->left;
					N->left->parent = N->parent;
					N->left->color = BLACK;
					_allocNode.deallocate(N, 1);
					return ;
				}
				else if (N->right)			// N has 1 child (right)
				{
					if (N->parent)
						N->parent->child[childDir(N)] = N->right;
					N->right->parent = N->parent;
					N->right->color = BLACK;
					_allocNode.deallocate(N, 1);
					return ;
				}
				else						// N has NO child
				{
					Node *P = N->parent;	// parent
					Node *S;				// sibling
					Node *C;				// close   nephew
					Node *D;				// distant nephew
					bool dir = childDir(N);

					// erase N
					P->child[dir] = nullptr;
					_allocNode.deallocate(N, 1);

					while (P)
					{
						S = P->child[1 - dir];
						D = S->child[1 - dir];
						C = S->child[dir];
						if (S->color = RED)
							return eraseCase3(P, S, C, D, dir);		// S is RED => P+C+D BLACK

						// S is BLACK

						if (D && D->color == RED)
							return eraseCase6(P, S, D);				// D is RED && S is BLACK
						if (C && C->color == RED)
							return eraseCase5(P, S, C, D);			// C is RED && S+D BLACK

						// both nephews are NULL or BLACK

						if (P->color == RED)
							return eraseCase4(P, S);					// P is RED && C+S+D BLACK

						// Case1:
						// P+C+S+D BLACK
						S->color = RED;
						N = P;
						P = N->parent;
						if (P)
							dir = childDir(N);
					}
					// N is _root, the tree is rebalanced
				}
			}
		}

		// erase specific key
		size_type erase(const value_type &value)
		{
			iterator position = find(value);
			if (position.getNode())
			{
				erase(position);
				return (1);
			}
			else
				return (0);
		}

		// erase range
		void erase(iterator first, iterator last)
		{
			for (iterator it = first; it != last; )
				erase(it++);
		}

		void swap(set &other)
		{
			set tmp = other;
			other._root = _root;
			other._size = _size;
			_root = tmp._root;
			_size = tmp._size;
		}

		void clear()
		{
			_size = 0;
			for (iterator it = begin(); it != end(); )
				_allocNode.deallocate((it++).getNode(), 1);
			_root = nullptr;
		}


    //------------------------------------------------------------- */
    // OBSERVERS
    //------------------------------------------------------------- */
	public:
		key_compare		key_comp() const { return _compare; }
		value_compare	value_comp() const { return value_compare(_compare); }


    //------------------------------------------------------------- */
    // OPERATIONS
    //------------------------------------------------------------- */
	public:
		iterator	find(const value_type &value)
		{
			Node *node = _root;

			while (node)
			{
				if (areValuesEqual(value, node->value.first))
					return iterator(node, _root);
				else if (_compare(value, node->value.first))
					node = node->left;
				else
					node = node->right;
			}
			return end();
		}

		const_iterator	find(const value_type &value) const
		{
			Node *node = _root;

			while (node)
			{
				if (areValuesEqual(value, node->value.first))
					return const_iterator(node, _root);
				else if (_compare(value, node->value.first))
					node = node->left;
				else
					node = node->right;
			}
			return end();
		}

		size_type count(const value_type &value) const
		{
			if (find(value) == end())
				return 0;
			else
				return 1;
		}

		iterator lower_bound(const value_type &value)
		{
			iterator ret = end();
			Node *node = _root;

			while (node)
			{
				if (!_compare(node->value.first, value))
				{
					ret = iterator(node, _root);
					node = node->left;
				}
				else
					node = node->right;
			}
			return (ret);
		}

		const_iterator lower_bound(const value_type &value) const
		{
			const_iterator ret = end();
			Node *node = _root;

			while (node)
			{
				if (!_compare(node->value.first, value))
				{
					ret = const_iterator(node, _root);
					node = node->left;
				}
				else
					node = node->right;
			}
			return (ret);
		}

		iterator upper_bound(const value_type &value)
		{
			iterator ret = end();
			Node *node = _root;

			while (node)
			{
				if (_compare(value, node->value.first))
				{
					ret = iterator(node, _root);
					node = node->left;
				}
				else
					node = node->right;
			}
			return (ret);
		}

		const_iterator upper_bound(const value_type &value) const
		{
			const_iterator ret = end();
			Node *node = _root;

			while (node)
			{
				if (_compare(value, node->value.first))
				{
					ret = const_iterator(node, _root);
					node = node->left;
				}
				else
					node = node->right;
			}
			return (ret);
		}

		pair<const_iterator,const_iterator> equal_range(const value_type &value) const
		{
			pair<const_iterator,const_iterator> ret;

			ret.first = lower_bound(value);
			ret.second = upper_bound(value);
			return ret;
		}

		pair<iterator,iterator> equal_range(const value_type &value)
		{
			pair<iterator,iterator> ret;

			ret.first = lower_bound(value);
			ret.second = upper_bound(value);
			return ret;
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
		bool areValuesEqual(value_type lhs, value_type rhs) const { return (!_compare(lhs, rhs) && !_compare(rhs, lhs)); }

		Node *min(Node *node) const
		{
			while (node && node->left)
				node = node->left;
			return (node);
		}

		void swapNodes(Node *n1, Node *n2)
		{
			Node tmp = *n2;

			if (_root == n1)
				_root = n2;
			else if (_root == n2)
				_root = n1;

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

			_allocPair.construct(&n2->value, n1->value);
			n2->parent = n1->parent;
			n2->left = n1->left;
			n2->right = n1->right;
			n2->color = n1->color;
			
			_allocPair.construct(&n1->value, tmp.value);
			n1->parent = tmp.parent;
			n1->left = tmp.left;
			n1->right = tmp.right;
			n1->color = tmp.color;
		}

		void rotate(Node *p, Node *n)
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

		//
		// insert helpers
		//
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
			rebalanceIn(g);
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

		//
		// erase helpers
		//
		void eraseCase3(Node *P, Node *S, Node *C, Node *D, bool dir)
		{
			rotate(P, S);
			P->color = RED;
			S->color = BLACK;
			S = C;
			// from here P RED && S BLACK
			D = S->child[1 - dir];
			if (D && D->color == RED)
				return eraseCase6(P, S, D);			// D RED && S BLACK
			C = S->child[dir];
			if (C && C->color == RED)
				return eraseCase5(P, S, C, D);		// C RED && S+D BLACK
			return eraseCase4(P, S);				// S+C+D BLACK
		}

		void eraseCase4(Node *P, Node *S)
		{
			S->color = RED;
			P->color = BLACK;
		}

		void eraseCase5(Node *P, Node *S, Node *C, Node *D)
		{
			rotate(S, C);
			S->color = RED;
			C->color = BLACK;
			D = S;
			S = C;
			eraseCase6(P, S, D);	// D RED && S BLACK
		}

		void eraseCase6(Node *P, Node *S, Node *D)
		{
			rotate(P, S);
			S->color = P->color;
			P->color = BLACK;
			D->color = BLACK;
		}

	}; // class set

} // namespace ft
