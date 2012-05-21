#ifndef __TOKENIZER_H__
#define __TOKENIZER_H__

/**
\file
\brief Contains the \ref tokenizer declaration

\class tokenizer
\brief Tokenizes the input string

It receives a string as a parameter of its static method \ref tokenizer::tokenize(const std::string&) and outputs an array of tokens, 
which is then parsed by the \ref parser. Since it's meant to be used only in this program, it isn't very flexible, you cannot set your own delimiter and you cannot create more instances of it.

\fn tokenizer::tokenize(const std::string &str)
This function is the only public member of the \ref tokenizer. It receives the string and internally creates a \ref tokenizer object, that then creates the tokens.

*/

#include <string>
#include <vector>

class tokenizer
{
public:
	tokenizer(const std::string& input_str);
	std::string next_token();
private:
	std::string str;
	size_t pos;
	void get_number();
	std::string number;
};

#endif
