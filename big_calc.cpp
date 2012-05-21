/**
\file
\brief This file contains ponies and  the main function
*/
/**
\def __PONY__ 
This define makes the source about 20% cooler!

\exception bad_arg_exception
\brief Thrown when user enters bad comand-line arguments

\fn main(int, char**)
Starting point for the application, main is responsible for creating objects and calling functions that manage I/O, parse the input and do the calculations
\param argc Number of arguments, must be at least 2, because we have to determine the mode of input (interactive/from file)
\param argv The argument we pass to the program, the fist argument should be \em i for interactive mode or \em f for input from file

*/


#include <vector>
#include <string>
#include <cstdlib>
#include <stdexcept>
#include <iostream>
#include <fstream>
#include "parser.h"
#include "base_node.h"
#include "big_calc.h"
#define __PONY__ "pony is the most awesome creature in the whole universe!!!!"

class bad_file_exception : public std::runtime_error
{
public:
	bad_file_exception(const std::string& msg) : std::runtime_error(msg) { }
};

int interactive_mode()
{
	std::string line;
	base_node* expr;
	while(!std::getline(std::cin, line).eof() && line != "q")
	{
		try {
			expr = parser::parse(line);
		}
		catch(parse_exception& e)
		{
			std::cerr << "parse pony is very sad :-(\nerror: " << e.what() << std::endl;
		}
		if(expr != NULL)
		{
			std::cout << expr->eval() << std::endl;
			delete expr;
		}
	}
	return 0;
}

int file_input_mode(const std::string& filename)
{
	std::ifstream input(filename);
	if(input.fail())
		throw bad_file_exception("either file doesn't exist, or you don't have enough permission for reading it");
	std::string line;
	base_node* expr;
	while(!input.eof() && !input.fail())
	{
		std::getline(input, line);
		try {
			expr = parser::parse(line);
		}
		catch(parse_exception& e)
		{
			std::cerr << "parse pony is very sad :-(\nerror: " << e.what() << std::endl;
		}
		if(expr != NULL)
		{
			std::cout << expr->eval() << std::endl;
			delete expr;
		}
	}
}

int get_mode(int argc, char** argv)
{
	if(argc == 1)
		return 0;
	else
		return 1;
}

int main(int argc, char** argv)
{
	int mode = get_mode(argc, argv);
	std::string line;
	int ret;
	if(mode == 0)
	{
		ret = interactive_mode();
	}
	else
	{
		std::string filename(argv[1]);
		try {
			ret = file_input_mode(filename);
		}
		catch(bad_file_exception& e)
		{
			std::cerr << e.what() << std::endl;
		}
	}
	return ret;

	/*big_num a("-1");
	big_num b("2.1");
	std::cout << a + b << std::endl;

	return 0;*/
}