#ifndef __BIG_CALC_H__
#define __BIG_CALC_H__
#include <string>
/**
\file
\brief This file contains ponies and  the main function
*/
/**
\def __PONY__ 
\brief This define makes the source about 20% cooler!

\class bad_file_exception
\brief Thrown when user enters bad comand-line arguments
\detailed Gets thrown only in \ref file_input_mode(const string&) when the file either doesn't exist, the user doesn't have enough permissions to open it or if it was somehow
corrupted

\fn bad_file_exception::bad_file_exception(const std::string&)
\brief constructs the exception with the specified error message
\param msg the error message describing what went wrong

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
#define __PONY__ "pony is the most awesome creature in the whole universe!!!!"
int get_mode(int argc);
int interactive_mode();
int file_input_mode(const std::string& filename);
void open_file(const std::string& filename);
#endif
