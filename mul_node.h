#ifndef __MUL_NODE_H__
#define __MUL_NODE_H__
#include "op_node.h"


/**
\file 
\brief contains the declaration of \ref mul_node

\class mul_node
\brief the node representing the multiplication operation


\fn mul_node::mul_node(base_node*, base_node*)
\brief constructs the mul_node
\param left the left root of the sutree representing the left subexpression
\param right the right root of the sutree representing the right subexpression

\fn mul_node::eval() const
\brief performs the multiplication operation on the left and right subexpressions
\details calls the \ref base_node::eval() on the \ref op_node::left and \ref op_node::right subtrees and then multiplicates the numbers that the function returns.
\return the result of the multiplication

\fn mul_node::~mul_node()
\brief destroys the tree
\details calls delete on both sides of the expression, therefore causing a recursive descent and deletion of all resources on both subtrees
*/
class mul_node :
	public op_node
{
public:
	mul_node(base_node* left, base_node* right);
	virtual ~mul_node(void);
	virtual big_num eval() const;
};
#endif
