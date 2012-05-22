#ifndef __TOKENIZER_H__
#define __TOKENIZER_H__

/**
\file
\brief Contains the \ref tokenizer declaration

\class tokenizer
\brief Tokenizes the input string
\detail Stores the string into its member variable \ref str and returns each token by calling \ref next_token(const std::string&).
\fn tokenizer::next_token()
\brief gets the next token from the string
\detail It skips all the whitespace characters and hen either returns the next character, or, if the next character is a digit, it returns the whole number 
(including up to one decimal point).
\return a token to be parsed by \ref parser
\fn get_nuber()
\brief gets all the digits of a number
\detail called by \ref next_token() whe a digit is encountered, it iterates through the string until something else that can't belong to a number is encountered.
It stores the number in the \ref number member variable

\var str
\brief the tokenized string
\var pos
\brief current position in string
\var number
\brief if a number is found, it is temporarily stored in this member variable
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
