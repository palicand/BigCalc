#ifndef __BASE_NODE_H__
#define __BASE_NODE_H__
#include "big_num.h"

/**
\file containt the \ref base_node class declaration

\class base_node
\brief The base type of a syntactic tree node
\details The abstract base class for all the nodes of the tree. If you want to extend the grammar of the tree, you should inherit either from this class, or from any other
abstract child of this class (for example like the \ref op_node). This class provides the abstract method \ref base_node::eval(), which you must call in order to evaluate the value
of the expression.

\fn base_node::base_node()
\brief the constructor of the base_node

\fn base_node::eval() const
\brief method for an evaluation of the expression
\details as each node type represents a different element of the expression, they all behave quite differently. The base_node::eval() method provides the different behavior for 
each expression element. In order to add a support for a new expression element, not only you must inherit from the base_node, but you must also override this method and define
its behavior.
\return the value of the expression in \ref big_num

\fn base_node::~base_node()
\brief destroys the node
\details Inherited classes should specify their of method of destruction
*/

class base_node
{
public:
	base_node();
	virtual ~base_node();
	virtual big_num eval() const = 0;
};

#endif
