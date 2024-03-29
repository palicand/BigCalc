﻿#ifndef __BIG_CALC_H__
#define __BIG_CALC_H__
#include <string>
/**
\file
\brief This file contains ponies and  the main function
*/

/**
\mainpage PA2 project
\section Description
Evaluates the mathematical expressions with arbitrarily long numbers. Valid expressions may contain operators +, - (binary and unary), * and () (with no limit on the level of nesting). 
You must provide both operands for all binary operators, and all parentheses must be paired. A valid operand is either just a number, or a subexpression in parentheses.

\section Usage
There are two modes of usage:
<ol>
	<li>Interactive mode</li>
	<li>File input mode</li>
</ol>

\par You enter interactive mode just by running the program without any command-line arguments. It reads expressions line by line until it receives an EOF or until it receives a line containing only character "q".
\par To trigger file input mode, you have to pass a input file on a command line. It then evaluates each line and prints the result with the order number of the expression.
*/

/**
\def __PONY__ 
\brief This define makes the source about 20% cooler!

\class bad_file_exception
\brief Thrown when user enters bad comand-line arguments
\details Gets thrown only in \ref file_input_mode(const std::string&) when the file either doesn't exist, the user doesn't have enough permissions to open it or if it was somehow
corrupted

\fn bad_file_exception::bad_file_exception(const std::string&)
\brief constructs the exception with the specified error message
\param msg the error message describing what went wrong

\fn interactive_mode()
\brief The interactive mode of the application
\return returns 0
\details The program reads one expression per line from a standard input. It stops reading either when end of line is encountered, or when the key "q" is pressed. It either prints the result, or if the 
input is incorrectly formatted, an error message describing the mistake in the input on the newline right after the entered expression.

\fn file_input_mode(const std::string&)
\brief Reads the expressions from the input file
\param filename The name of the input file
\return Returns 0, if everything went all right or throws the \ref bad_file_exception if there was a problem while opening or reading the file
\details While in the file input mode, the program reads expressions separated by a newline. Each result is printed on a new line. If some expression
was in incorrect format, it prints the error and corresponding number of the expression and the continues computing the others

\fn main(int, char**)
\brief Starting point for the application, main is responsible for creating objects and calling functions that manage I/O, parse the input and do the calculations
\param argc Number of arguments, must be at least 2, because we have to determine the mode of input (interactive/from file)
\param argv The argument we pass to the program, the fist argument should be \em i for interactive mode or \em f for input from file

*/
#define __PONY__ "pony is the most awesome creature in the whole universe!!!!"

int interactive_mode();
int file_input_mode(const std::string& filename);

#endif
