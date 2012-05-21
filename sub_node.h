#ifndef __SUB_NODE_H__
#define __SUB_NODE_H__
#include "op_node.h"
class sub_node :
	public op_node
{
public:
	sub_node(base_node* left, base_node* right);
	virtual ~sub_node(void);
	virtual big_num eval() const;
};
#endif
