#ifndef __MUL_NODE_H__
#define __MUL_NODE_H__
#include "op_node.h"
class mul_node :
	public op_node
{
public:
	mul_node(base_node* left, base_node* right);
	virtual ~mul_node(void);
	virtual big_num eval() const;
};
#endif
