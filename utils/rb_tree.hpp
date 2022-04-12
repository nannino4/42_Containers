#pragma once

#define BLACK 0
#define RED 1

namespace ft
{
	template <class T>
	struct Node
	{
		Node	*parent;
		Node	*right;
		Node	*left;
		bool	color;
		T		value;

		// default constructor
		Node(Node *p = nullptr, Node *r = nullptr, Node *l = nullptr, bool c = BLACK, T v = T()) : 
			parent(p), right(r), left(l), color(c), value(v) {}
		
		// copy constructor
		Node(Node const &other) { *this = other; }

		// assign operator
		Node &operator=(Node const &other)
		{
			if (this != &other)
			{
				parent = other.parent;
				right = other.right;
				left = other.left;
				color = other.color;
				value = other.value;
			}
		}

		// comparison operator
		bool operator==(Node const &other) const { return (value == other.value); }

	}; // struct node

	template< class T, class Compare, class Alloc = std::allocator<Node<T> > >
	class RBTree
	{

	//------------------------------------------------------------- */
	// MEMBER TYPES
	//------------------------------------------------------------- */
	public:
		typedef T																value_type;
		typedef typename Node<T>												node_type;
		typedef Compare															value_compare;
		typedef Alloc															allocator_type;
		typedef typename allocator_type::reference 								reference;
		typedef typename allocator_type::const_reference 						const_reference;
		typedef typename allocator_type::pointer 								pointer;
		typedef typename allocator_type::const_pointer 							const_pointer;
		typedef typename allocator_type::difference_type 						difference_type;
		typedef typename allocator_type::size_type 								size_type;


	//------------------------------------------------------------- */
	// ATTRIBUTES
	//------------------------------------------------------------- */
	private:
		pointer			_root;
		size_type		_size;
		value_compare	_compare;
		allocator_type	_allocator;


	//------------------------------------------------------------- */
	// COPLIEN FORM
	//------------------------------------------------------------- */
	public:
		// default constructor
		RBTree(value_compare const compare = value_compare()) : _root(nullptr), _size(0), _compare(compare) {}
		//TODO


	//------------------------------------------------------------- */
	// MEMBER FUNCTIONS
	//------------------------------------------------------------- */
	public:

	}; // class rb_tree

} // namespace ft
