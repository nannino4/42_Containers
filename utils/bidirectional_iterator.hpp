#pragma once

#include "iterator.hpp"

namespace ft
{
	template<class T, class Node>
	class bidirectional_iterator : iterator<bidirectional_iterator_tag, T>
	{

    //------------------------------------------------------------- */
    // ATTRIBUTES
    //------------------------------------------------------------- */
	private:
        Node	*_element;
        Node	*_root;


    //------------------------------------------------------------- */
    // COPLIEN FORM
    //------------------------------------------------------------- */
	public:
        bidirectional_iterator(Node *element = nullptr, Node *root = nullptr) : 
			_element(element), _root(root) {}

		bidirectional_iterator(bidirectional_iterator const &other) :
			_element(other.getElement()), _root(other.getRoot())) {}

		~bidirectional_iterator() {}

		bidirectional_iterator &operator=(bidirectional_iterator const &other)
		{
			if (this != &other)
			{
				_element = other.getElement();
				_root = other.getRoot();
			}
			return (*this);
		}


    //------------------------------------------------------------- */
    // GETTERS
    //------------------------------------------------------------- */
	public:
		Node 	*getElement() { return _element; }
		Node 	*getRoot() { return _root; }


    //------------------------------------------------------------- */
    // OPERATOR OVERLOADS
    //------------------------------------------------------------- */
	public:
		bool operator==(bidirectional_iterator const &other) const { return _element == other.getElement(); }
		bool operator!=(bidirectional_iterator const &other) const { return _element != other.getElement(); }

		reference	operator*() const { return _element->value; } 
		pointer		operator->() const { return &(_element->value); }

		bidirectional_iterator	operator++()
		{
			if (!_node || _node == max(_root))
				_node = nullptr;
			else
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
			if (!_node || _node == min(_root))
				_node = nullptr;
			else
				_node = predecessor(_node);
			return (*this);
		}

		bidirectional_iterator	operator--(int)
		{
			bidirectional_iterator tmp(*this);
			operator--();
			return (tmp);
		}


    //------------------------------------------------------------- */
    // PRIVATE MEMBER FUNCTIONS
    //------------------------------------------------------------- */
	private:
		Node *max(Node *node)
		{
			while (node && node->right)
				node = node->right;
			return (node);
		}

		Node *min(Node *node)
		{
			while (node && node->left)
				node = node->left;
			return (node);
		}

		Node *successor(Node *node)
		{
			if (!node)
				return (nullptr);
			if (node->right)
				return (min(node->right));

			Node *parent = node->parent;
			while (parent && node == parent->right)
			{
				node = parent;
				parent = parent->parent;
			}
			return (parent);
		}

		Node *predecessor(Node *node)
		{
			if (!node)
				return (nullptr);
			if (node->left)
				return (max(node->left));

			Node *parent = node->parent;
			while (parent && node == parent->left)
			{
				node = parent;
				parent = parent->parent;
			}
			return (parent);
		}

	}; // class bidirectional_iterator

} // namespace ft
