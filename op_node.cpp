#include "op_node.h"


op_node::op_node(base_node* left, base_node* right)
{
	this->left = left;
	this->right = right;
}


op_node::~op_node(void)
{
	delete left;
	delete right;
}
