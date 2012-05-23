#ifndef __UNARY_SUB_NODE_H__
#define __UNARY_SUB_NODE_H__
#include "base_node.h"
class unary_sub_node :
	public base_node
{
public:
	unary_sub_node(base_node* child);
	~unary_sub_node();
	virtual big_num eval() const;
private:
	base_node* child;
};
#endif
