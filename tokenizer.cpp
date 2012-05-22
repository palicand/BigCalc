#include "tokenizer.h"
#include <iterator>
#include <sstream>
#include <cctype>

tokenizer::tokenizer(const std::string& input_str) : str(input_str)
{
	pos = 0;
}

std::string tokenizer::next_token()
{
	while(pos < str.length() && isspace(str[pos]))
		pos++;
	if(pos >= str.length())
		return "";
	if(isdigit(str[pos]))
	{
		get_number();
		return number;
	}
	else
	{
		pos++;
		return str.substr(pos-1, 1);
	}
}

void tokenizer::get_number()
{
	int point_count = 0;
	size_t start_pos = pos;
	while((pos < str.length()) && (isdigit(str[pos]) || str[pos] == '.'))
	{
		pos++;
	}
	number.assign(str.substr(start_pos, pos - start_pos));
}