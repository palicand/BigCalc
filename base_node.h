#ifndef __BASE_NODE_H__
#define __BASE_NODE_H__
#include "big_num.h"

class base_node
{
public:
	base_node();
	virtual ~base_node(void);
	virtual big_num eval() const = 0;
};

#endif
