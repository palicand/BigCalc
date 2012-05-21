#pragma once
#include "op_node.h"
class sub_node :
	public op_node
{
public:
	sub_node(base_node* left, base_node* right);
	virtual ~sub_node(void);
	virtual big_num eval() const;
};

