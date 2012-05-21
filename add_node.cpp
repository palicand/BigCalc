#include "add_node.h"


add_node::add_node(base_node* left, base_node* right) : op_node(left, right)
{
}


add_node::~add_node(void)
{
}

big_num add_node::eval() const { return left->eval() + right->eval(); }