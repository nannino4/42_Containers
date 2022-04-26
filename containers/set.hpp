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
		typedef Alloc											allocator_type;

	private:
		struct Node
		{
			value_type	value;
			Node		*parent;
			Node		*child[2];
			bool		color;
		};

	public:
		typedef Compare												key_compare;
		typedef Compare												value_compare;

		typedef typename allocator_type::reference 					reference;
		typedef typename allocator_type::const_reference			const_reference;
		typedef typename allocator_type::pointer					pointer;
		typedef typename allocator_type::const_pointer				const_pointer;

		typedef ft::bidirectional_iterator<value_type,Node>			iterator;
		typedef ft::bidirectional_iterator<const value_type,Node>	const_iterator;
		typedef ft::reverse_iterator<iterator>						reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>				const_reverse_iterator;

		typedef ptrdiff_t											difference_type;
		typedef size_t												size_type;


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
		set(const set &other) : _root(nullptr), _size(0)
		{
			*this = other;
		}

		// destructor
		~set() { clear(); }

		// assign operator
		set &operator=(const set &other)
		{
			if (this != &other)
			{
				clear();
				_compare = other.key_comp();
				_allocPair = other.get_allocator();
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
			// check if val already exists
			if (find(val) != end())
				return find(val);

			// check if hint is correct
			if (!position.getNode())
				return (insert(val)).first;
			if (value_comp()(*position, val) && (!(position + 1).getNode() || value_comp()(val, *(position + 1))))
			{
				// position is predecessor of new node
				Node *p = position.getNode();

				// create new node n
				++_size;
				Node *n = _allocNode.allocate(1);
				_allocPair.construct(&n->value, val);
				n->color = RED;
				n->left = nullptr;
				n->right = nullptr;
				n->parent = nullptr;

				// insert n
				if (!p->right)
					p->right = n;
				else
				{
					p = (position + 1).getNode();
					p->left = n;
				}
				n->parent = p;

				// rebalance
				rebalanceIn(n);

				return (iterator(n, _root));
			}
			else if (value_comp()(val, *position) && (!(position - 1).getNode() || value_comp()(*(position + 1), val)))
			{
				// position is successor of new node
				Node *p = position.getNode();

				// create new node n
				++_size;
				Node *n = _allocNode.allocate(1);
				_allocPair.construct(&n->value, val);
				n->color = RED;
				n->left = nullptr;
				n->right = nullptr;
				n->parent = nullptr;

				// insert n
				if (!p->left)
					p->left = n;
				else
				{
					p = (position - 1).getNode();
					p->right = n;
				}
				n->parent = p;

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
					else
						_root = N->right;
					N->left->parent = N->parent;
					N->left->color = BLACK;
					_allocNode.deallocate(N, 1);
					return ;
				}
				else if (N->right)			// N has 1 child (right)
				{
					if (N->parent)
						N->parent->child[childDir(N)] = N->right;
					else
						_root = N->right;
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
						if (S->color == RED)
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
		size_type erase(const key_type &key)
		{
			iterator position = find(key);
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
			Node		*tmpRoot = other._root;
			size_type	tmpSize = other.size();

			other._root = _root;
			other._size = _size;
			_root = tmpRoot;
			_size = tmpSize;
		}

		void clear()
		{
			// _size = 0;
			// for (iterator it = begin(); it != end(); )
			// 	_allocNode.deallocate((it++).getNode(), 1);
			// _root = nullptr;
			erase(begin(), end());
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
		iterator	find(const key_type &key)
		{
			Node *node = _root;

			while (node)
			{
				if (areKeysEqual(key, node->value))
					return iterator(node, _root);
				else if (_compare(key, node->value))
					node = node->left;
				else
					node = node->right;
			}
			return end();
		}

		const_iterator	find(const key_type &key) const
		{
			Node *node = _root;

			while (node)
			{
				if (areKeysEqual(key, node->value))
					return const_iterator(node, _root);
				else if (_compare(key, node->value))
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
				if (!_compare(node->value, key))
				{
					ret = iterator(node, _root);
					node = node->left;
				}
				else
					node = node->right;
			}
			return (ret);
		}

		const_iterator lower_bound(const key_type &key) const
		{
			const_iterator ret = end();
			Node *node = _root;

			while (node)
			{
				if (!_compare(node->value, key))
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
				if (_compare(key, node->value))
				{
					ret = iterator(node, _root);
					node = node->left;
				}
				else
					node = node->right;
			}
			return (ret);
		}

		const_iterator upper_bound(const key_type &key) const
		{
			const_iterator ret = end();
			Node *node = _root;

			while (node)
			{
				if (_compare(key, node->value))
				{
					ret = const_iterator(node, _root);
					node = node->left;
				}
				else
					node = node->right;
			}
			return (ret);
		}

		pair<const_iterator,const_iterator> equal_range(const key_type &key) const
		{
			return make_pair(lower_bound(key), upper_bound(key));
		}

		pair<iterator,iterator> equal_range(const key_type &key)
		{
			return make_pair(lower_bound(key), upper_bound(key));
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
		bool areKeysEqual(key_type lhs, key_type rhs) const { return (!_compare(lhs, rhs) && !_compare(rhs, lhs)); }

		Node *min(Node *node)
		{
			while (node && node->left)
				node = node->left;
			return (node);
		}

		Node *min(Node *node) const
		{
			while (node && node->left)
				node = node->left;
			return (node);
		}

		void swapNodes(Node *n1, Node *n2)
		{
			Node tmp;	// for n1 internal dependencies to copy from
			if (n2->parent == n1)
				tmp.parent = n2;
			else
				tmp.parent = n2->parent;
			if (n2->left == n1)
				tmp.left = n2;
			else
				tmp.left = n2->left;
			if (n2->right == n1)
				tmp.right = n2;
			else
				tmp.right = n2->right;
			tmp.color = n2->color;

			// swap root
			if (_root == n1)
				_root = n2;
			else if (_root == n2)
				_root = n1;

			// swap n2 external dependencies
			if (n2->parent && n2->parent != n1)
				n2->parent->child[childDir(n2)] = n1;
			if (n2->left && n2->left != n1)
				n2->left->parent = n1;
			if (n2->right && n2->right != n1)
				n2->right->parent = n1;

			// swap n2 internal dependencies
			if (n1->parent == n2)
				n2->parent = n1;
			else
				n2->parent = n1->parent;
			if (n1->left == n2)
				n2->left = n1;
			else
				n2->left = n1->left;
			if (n1->right == n2)
				n2->right = n1;
			else
				n2->right = n1->right;
			n2->color = n1->color;

			// swap n1 external dependencies
			if (n1->parent)
				n1->parent->child[childDir(n1)] = n2;
			if (n1->left && n1->left != n2)
				n1->left->parent = n2;
			if (n1->right && n1->right != n2)
				n1->right->parent = n2;
			
			// swap n1 internal dependencies
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
				return rebalanceInCase4(p);				// p is RED && _root
			// p is RED && not _root
			Node *u = g->child[1 - childDir(p)];	// u = uncle of n
			if (!u || u->color == BLACK)
				return rebalanceInCase56(n, p, g);		// p RED && u BLACK
			return rebalanceInCase2(p, g, u);		// p+u RED
		}

		void rebalanceInCase1()
		{
			return ;
		}

		void rebalanceInCase2(Node *p, Node *g, Node *u)
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

		void rebalanceInCase56(Node *n, Node *p, Node *g)
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


//------------------------------------------------------------- */
// NON-MEMBER FUNCTIONS
//------------------------------------------------------------- */

	//
	// swap
	//
	template<class Key, class Compare, class Alloc>
	void swap(set<Key, Compare, Alloc>& lhs, set<Key, Compare, Alloc>& rhs )
	{
		lhs.swap(rhs);
	}

	//
	// relational operators
	//
	template<class Key, class Compare, class Alloc>
	bool operator==(const set<Key, Compare, Alloc>& lhs, const set<Key, Compare, Alloc>& rhs)
	{
		if (lhs.size() != rhs.size())
			return false;
		return equal(lhs.begin(), lhs.end(), rhs.begin());
	}

	template<class Key, class Compare, class Alloc>
	bool operator!=(const set<Key, Compare, Alloc>& lhs, const set<Key, Compare, Alloc>& rhs)
	{
		return !(lhs == rhs);
	}

	template<class Key, class Compare, class Alloc>
	bool operator<(const set<Key, Compare, Alloc>& lhs, const set<Key, Compare, Alloc>& rhs)
	{
		return lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	template<class Key, class Compare, class Alloc>
	bool operator<=(const set<Key, Compare, Alloc>& lhs, const set<Key, Compare, Alloc>& rhs)
	{
		return !(rhs < lhs);
	}

	template<class Key, class Compare, class Alloc>
	bool operator>(const set<Key, Compare, Alloc>& lhs, const set<Key, Compare, Alloc>& rhs)
	{
		return !(lhs <= rhs);
	}

	template<class Key, class Compare, class Alloc>
	bool operator>=(const set<Key, Compare, Alloc>& lhs, const set<Key, Compare, Alloc>& rhs)
	{
		return !(lhs < rhs);
	}

} // namespace ft
