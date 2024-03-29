﻿#include <cctype>
#include "parser.h"
#include "add_node.h"
#include "op_node.h"
#include "num_node.h"
#include "sub_node.h"
#include "mul_node.h"
#include "unary_sub_node.h"
//influenced by Mr. Vagner's class and http://math.hws.edu/javanotes/c9/s5.html
base_node* parser::parse(const std::string&str)
{
	parser p(str);
	return p.create_tree();
}

parser::parser(const std::string& str) : str(str), tok(str)
{

}

/**
\brief creates the syntactic tree

*/
base_node* parser::create_tree()
{
	base_node* node = NULL;
	current_token = tok.next_token();
	node = get_expression();
	if(current_token != "")
	{
		if(node != NULL)
			delete node;
		throw parse_exception("invalid characters at the end of the input");
	}
	return node;
}

base_node* parser::get_expression()
{
	//current_token = tok.next_token();
	base_node* res = NULL;
	bool negative_expr = false;
	if(current_token == "-")
	{
		negative_expr = true;
		current_token = tok.next_token();
	}
	try {
		res = get_term();
		if(negative_expr)
		{
			res = new unary_sub_node(res);
			negative_expr = false;
		}
		while(current_token == "+" || current_token == "-")
		{
			if(current_token == "+")
			{
				current_token = tok.next_token();
				res = new add_node(res, get_term());
			}
			else
			{
				current_token = tok.next_token();
				res = new sub_node(res, get_term());
			}
		}
	}
	catch(parse_exception& e)
	{
		if(res != NULL)
			delete res;
		throw;
	}
	return res;
}

base_node* parser::get_term()
{
	//current_token = tok.next_token();
	base_node* res = NULL;
	try {
		res = get_factor();
		while(current_token == "*")
		{
			if(current_token == "*")
			{
				current_token = tok.next_token();
				res = new mul_node(res, get_factor());
			}
		}
	}
	catch(parse_exception& e)
	{
		if(res != NULL)
			delete res;
		throw;
	}
	return res;
}

base_node* parser::get_factor()
{
	base_node* res = NULL;
	if(is_number(current_token))
	{
		res = new num_node(current_token);
		current_token = tok.next_token();
		return res;
	}
	else if(current_token == "(")
	{
		current_token = tok.next_token();
		res = get_expression();
		if(current_token != ")")
		{
			delete res;
			throw parse_exception("missing right parenthesis");
		}
		current_token = tok.next_token();
		return res;
	}
	else
		throw parse_exception("invalid input");
}

bool parser::is_number(const std::string& str) const
{
	int dec_count = 0;
	for(size_t i = 0; i < str.length(); i++)
	{
		if(!std::isdigit(str[i]))
		{
			if(str[i] == '.' && dec_count == 0)
			{
				dec_count++;
			}
			else
			{
				return false;
			}
		}
	}
	return true;
}