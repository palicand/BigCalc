#include "mul_node.h"


mul_node::mul_node(base_node* left, base_node* right) : op_node(left, right)
{
}


mul_node::~mul_node(void)
{
}

big_num mul_node::eval() const
{
	return left->eval() * right->eval();
}
