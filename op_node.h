#ifndef __OP_NODE_H__
#define __OP_NODE_H__
#include "base_node.h"

/**
\file 
\brief contains the declaration of \ref op_node

\class op_node
\brief the base abstract class for operators
\details This class is intended as a base class for operators. It gives access to left and right subexpressions for every class that is derived from it. 

\fn op_node::op_node(base_node* left, base_node* right)
\brief creates the op_node
\param left the left subexpression
\param right the right subexpression

\fn op_node::~op_node()
\brief destroys the op_node
\details calls delete on both subtrees, which calls the destructor in each node and it recursivelly traverses until it reaches leaves and then on the way back frees the memory

\fn op_node::eval() const
\brief evaluates the expression
\details Recursivelly computes the value of the expression. It first calls eval() on both left and right subtrees, therefore recursively descents until it reaches \ref num_node
which just returns the \ref big_num representation. It then performs it's respective operation with the returned values.

\var op_node::left The left subtree
\var op_node::right The right subtree
*/
class op_node :
	public base_node
{
public:
	op_node(base_node* left, base_node* right);
	virtual ~op_node();
	virtual big_num eval() const = 0;
protected:
	base_node* left, *right;
};
#endif
