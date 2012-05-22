#ifndef __OP_NODE_H__
#define __OP_NODE_H__
#include "base_node.h"
class op_node :
	public base_node
{
public:
	op_node(const base_node* left, const base_node* right);
	virtual ~op_node(void);
	virtual big_num eval() const = 0;
protected:
	base_node* left, *right;
};
#endif
