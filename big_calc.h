#ifndef __BIG_CALC_H__
#define __BIG_CALC_H__
#include <string>
/**
\fn check_arguments(int, char**)
\brief Checks if command-line arguments are ok and sets the mode
\param argc Number of arguments
\param argv The arguments themelves
\ret returns 0 or 1 if everything's in order, that means if we got 1 argument and it's 0, or 2 arguments and they're zero and a filename; otherwise, return -1
*/

int get_mode(int argc);
int interactive_mode();
int file_input_mode(const std::string& filename);
void open_file(const std::string& filename);
#endif
