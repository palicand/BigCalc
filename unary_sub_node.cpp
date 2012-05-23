#include "unary_sub_node.h"


unary_sub_node::unary_sub_node(base_node* child)
{
	this->child = child;
}


unary_sub_node::~unary_sub_node()
{
	delete child;
}

big_num unary_sub_node::eval() const
{
	return -child->eval();
}
