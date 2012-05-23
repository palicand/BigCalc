#ifndef __PARSER_H__
#define __PARSER_H__
#include <string>
#include <vector>
#include <stdexcept>
#include "base_node.h"
#include "tokenizer.h"
//#include "tree.h"
/**
\file
\brief Contains the declaration of the \ref parser class
*/

/**
\class parser
\brief Class responsible for parsing of the input expression
\details The parser creates the asymptotic syntax tree from the classes, that are derived from \ref base_node. It was inspired by Mr. Vagners 6th proseminar
and by http://math.hws.edu/javanotes/c9/s5.html. It recursively costructs the tree modeling the expression by going through each token and creating the appropriate node for it.

\fn parser::parser(const std::string&)
\brief the constructor of parser
\param str the string to be parsed

\fn parser::parse(const std::string&)
\brief parses the input string
\details The only public method of the class. It receives the input string, creates a parser object and then parses the string. 
\param str The input string
\return The root of the syntactic tree

\class parse_exception
\brief The exception that is thrown while parsing
\details The exception is thrown while a problem is encountered while the string is being parsed, for example when parentheses aren't corretly paired, or when there are unexpected/invalid characters in the string

\fn parse_exception::parse_exception(const std::string&)
\brief constructor for the exception
\param msg The error message
*/

class parse_exception : public std::runtime_error
{
public:
	parse_exception(const std::string& msg) : std::runtime_error(msg) { }
};

class parser
{
public:

	static base_node* parse(const std::string& str);
private:
	enum {NUM, ADD, SUB, MUL, LPAR, RPAR};
	parser(const std::string& str);
	base_node* create_tree();
	
	base_node* get_expression();
	base_node* get_term();
	base_node* get_factor();
	
	bool is_number(const std::string& str) const;

	tokenizer tok;
	std::string str;
	std::string current_token;
	bool negative_expr;
};
#endif
