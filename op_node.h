#pragma once
#include "base_node.h"
class op_node :
	public base_node
{
public:
	op_node(base_node* left, base_node* right);
	virtual ~op_node(void);
	virtual big_num eval() const = 0;
protected:
	base_node* left, *right;
};

