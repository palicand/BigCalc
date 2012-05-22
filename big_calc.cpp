#include <vector>
#include <string>
#include <cstdlib>
#include <stdexcept>
#include <iostream>
#include <fstream>
#include "parser.h"
#include "base_node.h"
#include "big_calc.h"

class bad_file_exception : public std::runtime_error
{
public:
	bad_file_exception(const std::string& msg) : std::runtime_error(msg) { }
};

int interactive_mode()
{
	std::string line;
	base_node* expr = NULL;
	while(!std::getline(std::cin, line).eof() && line != "q")
	{
		try {
			expr = parser::parse(line);
		}
		catch(parse_exception& e)
		{
			std::cerr << "parse pony is very sad :-(\nerror: " << e.what() << std::endl;
			delete expr;
			expr = NULL;
		}
		if(expr != NULL)
		{
			std::cout << "Result: " << expr->eval() << std::endl;
 			delete expr;
		}
	}
	return 0;
}

int file_input_mode(const std::string& filename)
{
	std::ifstream input(filename.c_str());
	if(input.fail())
		throw bad_file_exception("either file doesn't exist, or you don't have enough permission for reading it");
	std::string line;
	base_node* expr;
	int expr_n = 1;
	while(!input.eof() && !input.fail())
	{
		std::getline(input, line);
		try {
			expr = parser::parse(line);
		}
		catch(parse_exception& e)
		{
			std::cerr << "parse pony is very sad :-(\n problem with expression " << expr_n << ": "<< e.what() << std::endl;
			delete expr;
			expr = NULL;
		}
		if(expr != NULL)
		{
			std::cout << expr->eval() << std::endl;
			delete expr;
		}
		expr_n++;
	}
	if(input.fail())
	{
		input.close();
		throw bad_file_exception("There was a problem while I've been reading the file - it's probably corrupted");
	}
	return 0;
}

int main(int argc, char** argv)
{
	std::string line;
	int ret;
	if(argc == 1)
	{
		ret = interactive_mode();
	}
	else if(argc == 2)
	{
		std::string filename(argv[1]);
		try {
			ret = file_input_mode(filename);
		}
		catch(bad_file_exception& e)
		{
			std::cerr << e.what() << std::endl;
			return 1;
		}
	}
	else
	{
		std::cerr << "bad number of arguments, please refer to documentation for the right arguments\n";
		return 1;
	}
	return ret;

	/*big_num a("-1");
	big_num b("2.1");
	std::cout << a + b << std::endl;

	return 0;*/
}