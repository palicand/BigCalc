#ifndef __UNARY_SUB_NODE_H__
#define __UNARY_SUB_NODE_H__
#include "base_node.h"

/**
\file 
\brief contains the declaration of \ref unary_sub_node

\class unary_sub_node
\brief the node representing the adding operation


\fn unary_sub_node::unary_sub_node(base_node*)
\brief constructs the node for unary minus
\param left the left root of the subtree representing the left subexpression

\fn unary_sub_node::eval() const
\brief creates a negative expression
\details calls the \ref base_node::eval() on the \ref unary_sub_node::child and then uses the \ref big_num::operator-() on it
\return the result of the addition

\fn unary_sub_node::~unary_sub_node()
\brief destroys the tree
\details calls delete on both sides of the expression, therefore causing a recursive descent and deletion of all resources on both subtrees

\var base_node* unary_sub_node::child
\brief the child of the node
\details the exression that should be negative
*/
class unary_sub_node :
	public base_node
{
public:
	unary_sub_node(base_node* child);
	~unary_sub_node();
	virtual big_num eval() const;
protected:
	base_node* child;
};
#endif
