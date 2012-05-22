/**
\file
\brief This file contains ponies and  the main function
*/
/**
\def __PONY__ 
\brief This define makes the source about 20% cooler!

\exception bad_file_exception
\brief Thrown when user enters bad comand-line arguments
\detailed Gets thrown only in \ref file_input_mode(const string&) when the file either doesn't exist, the user doesn't have enough permissions to open it or if it was somehow
corrupted

\fn interactive_mode()
\brief The interactive mode of the application
\return returns 0
\detailed The program reads one expression per line from a standard input. It stops reading either when end of line is encountered, or when the key "q" is pressed. It either prints the result, or if the 
input is incorrectly formatted, an error message describing the mistake in the input on the newline right after the entered expression.

\fn file_input_mode(const std::string&)
\brief Reads the expressions from the input file
\param filename The name of the input file
\return Returns 0, if everything went all right or throws the \ref bad_file_exception if there was a problem while opening or reading the file
\detailed While in the file input mode, the program reads expressions separated either by a newline or a semicolon. Each result is printed on a new line. If some expression
was in incorrect format, it prints the error and corresponding number of the expression and the continues computing the others

\fn main(int, char**)
\brief Starting point for the application, main is responsible for creating objects and calling functions that manage I/O, parse the input and do the calculations
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
		throw bad_file_exception("There was a problem while I've been reading the file - it's probably corrupted");
	}
	return 0;
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
			return 1;
		}
	}
	return ret;

	/*big_num a("-1");
	big_num b("2.1");
	std::cout << a + b << std::endl;

	return 0;*/
}