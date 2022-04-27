#pragma once

#include "iterator.hpp"

#define LEFT		0
#define RIGHT		1
#define _left_		child[LEFT]
#define _right_		child[RIGHT]

namespace ft
{
	template<class T, class Node>
	class bidirectional_iterator : public ft::iterator<bidirectional_iterator_tag, T>
	{

    //------------------------------------------------------------- */
    // MEMBER TYPES
    //------------------------------------------------------------- */
	public:
		typedef T							value_type;
		typedef long int					difference_type;
		typedef T*							pointer;
		typedef T&							reference;
		typedef bidirectional_iterator_tag	iterator_category;

    //------------------------------------------------------------- */
    // ATTRIBUTES
    //------------------------------------------------------------- */
	private:
        Node	*_node;
        Node	*_root;


    //------------------------------------------------------------- */
    // COPLIEN FORM
    //------------------------------------------------------------- */
	public:
		// default constructor
        bidirectional_iterator(Node *node = nullptr, Node *root = nullptr)
		{
			_node = node;
			_root = root;
		}

		// copy constructor
		bidirectional_iterator(bidirectional_iterator const &other) { *this = other; }

		// destructor
		~bidirectional_iterator() {}

		// assign operator
		bidirectional_iterator &operator=(bidirectional_iterator const &other)
		{
			if (this != &other)
			{
				_node = other.getNode();
				_root = other.getRoot();
			}
			return (*this);
		}


    //------------------------------------------------------------- */
    // GETTERS
    //------------------------------------------------------------- */
	public:
		Node 		*getNode() const { return _node; }
		value_type 	getValue() const { return _node->value; }
		Node 		*getRoot() const { return _root; }


    //------------------------------------------------------------- */
    // OPERATOR OVERLOADS
    //------------------------------------------------------------- */
	public:
		bool operator==(bidirectional_iterator const &other) const { return _node == other.getNode(); }
		bool operator!=(bidirectional_iterator const &other) const { return _node != other.getNode(); }

		reference	operator*() const { return _node->value; } 
		pointer		operator->() const { return &(_node->value); }

		bidirectional_iterator	operator++()
		{
			_node = successor(_node);
			return (*this);
		}

		bidirectional_iterator	operator++(int)
		{
			bidirectional_iterator tmp(*this);
			operator++();
			return (tmp);
		}

		bidirectional_iterator	operator--()
		{
			_node = predecessor(_node);
			return (*this);
		}

		bidirectional_iterator	operator--(int)
		{
			bidirectional_iterator tmp(*this);
			operator--();
			return (tmp);
		}

		bidirectional_iterator	operator+(difference_type n) const
		{
			bidirectional_iterator ret(*this);
			while (n-- > 0)
				++ret;
			return ret;
		}

		bidirectional_iterator	operator-(difference_type n) const
		{
			bidirectional_iterator ret(*this);
			while (n-- > 0)
				--ret;
			return ret;
		}


    //------------------------------------------------------------- */
    // PRIVATE MEMBER FUNCTIONS
    //------------------------------------------------------------- */
	private:
		Node *max(Node *node)
		{
			while (node && node->_right_)
				node = node->_right_;
			return (node);
		}

		Node *min(Node *node)
		{
			while (node && node->_left_)
				node = node->_left_;
			return (node);
		}

		Node *successor(Node *node)
		{
			if (!node)
				return (min(_root));
			if (node->_right_)
				return (min(node->_right_));

			Node *parent = node->parent;
			while (parent && node == parent->_right_)
			{
				node = parent;
				parent = parent->parent;
			}
			return (parent);
		}

		Node *predecessor(Node *node)
		{
			if (!node)
				return (max(_root));
			if (node->_left_)
				return (max(node->_left_));

			Node *parent = node->parent;
			while (parent && node == parent->_left_)
			{
				node = parent;
				parent = parent->parent;
			}
			return (parent);
		}

	}; // class bidirectional_iterator

} // namespace ft
