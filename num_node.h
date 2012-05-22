#ifndef __NUM_NODE_H__
#define __NUM_NODE_H__
#include "base_node.h"
#include <string>

/**
\file 
\brief contains the \ref num_node declaration

\class num_node
\brief the node containing the \ref big_num representaion of number
\details Each object of this class is associated with one particular number from the expression. num_nodes are the leaves of the tree.

\fn num_node::num_node(const std::string&)
\brief constructs the num_node with the number passed in string
\param num the string representation of a number

\fn num_node::eval() const
\brief returns the number contained in the node
\return the value of the number

\fn num_node::~num_node()
\brief destroys the node
*/
class num_node :
	public base_node
{
public:
	//num_node(const std::string& num);
	num_node(const std::string& val) : number(val) { }
	virtual ~num_node(void);
	big_num eval() const { return number; }
private:
	//big_num val;
	big_num number;
};

#endif
