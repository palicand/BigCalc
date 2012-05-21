#ifndef __NUM_NODE_H__
#define __NUM_NODE_H__
#include "base_node.h"
#include <string>
class num_node :
	public base_node
{
public:
	//num_node(const std::string& num);
	num_node(const std::string& val) : number(val) { }
	virtual ~num_node(void);
	big_num eval() const { return number; }
private:
	//big_num val;
	big_num number;
};

#endif
