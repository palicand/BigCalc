#ifndef __SUB_NODE_H__
#define __SUB_NODE_H__
#include "op_node.h"
/**
\file contains the declaration of \ref sub_node

\class sub_node
\brief class used to represent a subtracting operation

\fn sub_node::sub_node(base_node* left, base_node* right)
\brief creates the node
\param left the left subtree
\param right the right subtree

\fn sub_node::~sub_node()
\brief destroys the sub_node and its subtrees

\fn eval() const
\brief subtracts the value in right subtree from value in left subtree
\details calls eval() on both subtrees and then subtracts the values. 
\return the result


*/
class sub_node :
	public op_node
{
public:
	sub_node(base_node* left, base_node* right);
	virtual ~sub_node();
	virtual big_num eval() const;
};
#endif
