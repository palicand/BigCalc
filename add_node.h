#ifndef __ADD_NODE_H__
#define __ADD_NODE_H__
#include "op_node.h"

/**
\file contains the declaration of \ref add_node

\class add_node
\brief the node representing the adding operation


\fn add_node::add_node(const base_node*, const base_node*)
\brief constructs the add node
\param left the left root of the sutree representing the left subexpression
\param right the right root of the sutree representing the right subexpression

\fn add_node::eval() const
\brief performs the add operation on the left and right subexpressions
\details calls the \ref base_node::eval() on the \ref left and \ref right subtrees and then adds the numbers that the function returns.
\return the result of the addition

\fn add_node::~add_node()
\brief destroys the tree
\details calls delete on both sides of the expression, therefore causing a recursive descent and deletion of all resources on both subtrees
*/
class add_node :
	public op_node
{
public:
	add_node(const base_node* left, const base_node* right);
	virtual big_num eval() const;
	virtual ~add_node();
};
#endif
