#pragma once
#include "op_node.h"
class add_node :
	public op_node
{
public:
	add_node(base_node* left, base_node* right);
	virtual big_num eval() const;
	virtual ~add_node(void);
};

