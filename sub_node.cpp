#include "sub_node.h"


sub_node::sub_node(base_node* left, base_node* right) : op_node(left, right)
{
}


sub_node::~sub_node(void)
{
}

big_num sub_node::eval() const
{
	return left->eval() - right->eval();
}
