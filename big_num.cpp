#include "big_num.h"
#include <algorithm>

const byte big_num::MAX_NUM = 0 - 1;
const int big_num::BITS = CHAR_BIT * sizeof(byte);
const size_t big_num::START_ALLOCATION = 100;
big_num::big_num(signed char n) : number(big_num::START_ALLOCATION, 0)
{
	filled_blocks = 1;
	negative = false;
	if(n < 0)
	{
		invert();
		negative = true;
	}
	number[0] = (byte)n;
	decimal = 0;
}

big_num::big_num(const std::string& str) : number(big_num::START_ALLOCATION, 0)
{
	decimal = 0;
	filled_blocks = 1;
	negative = false;
	from_string(str);
	
}
big_num::big_num(const big_num& src) : number(src.number)
{
	filled_blocks = src.filled_blocks;
	negative = src.negative;
	decimal = src.decimal;
}

big_num::~big_num()
{
}

big_num& big_num::operator=(const big_num& src)
{
	if(this == &src)
		return *this;
	number = src.number;
	decimal = src.decimal;
	filled_blocks = src.filled_blocks;
	negative = src.negative;
	return *this;
}

big_num& big_num::operator=(signed char n)
{
	number.assign(big_num::START_ALLOCATION, 0);
	filled_blocks = 1;
	number[0] =(byte) n;
	if(n < 0)
	{
		invert();
		negative = true;
	}
	else
		negative = false;
	return *this;
}

big_num operator+(const big_num& a, const big_num& b)
{
	big_num res = a;
	res += b;
	return res;
}

big_num& operator+=(big_num& a, const big_num& b)
{
	big_num& res = a;
	bool negative;
	double_byte carry = 0;
	size_t i = 0;
	big_num tempB = b;
	a.set_same_size(tempB);
	a.normalize(tempB);
	if(a.abs() == tempB.abs() && a.negative != tempB.negative)
	{
		return (a=0);
	}
	double_byte carry_limit = 0;
	size_t max_filled = (a.filled_blocks > tempB.filled_blocks) ? a.filled_blocks : tempB.filled_blocks;
	if(a.abs() > tempB.abs())
		negative = a.negative;
	else
		negative = tempB.negative;
	if((negative && a.negative && tempB.negative) || ((a.negative || tempB.negative) && !negative))
		carry_limit = 1;
	while(i < max_filled) 
	{
        double_byte temp_sum = carry;
		carry = 0;
		if (i < a.filled_blocks || i < tempB.filled_blocks) 
		{
			temp_sum += a.number[i];
			temp_sum += tempB.number[i];
		}
		if (temp_sum > big_num::MAX_NUM) {
			temp_sum &= big_num::MAX_NUM;
            carry = 1;
        }
		res.add_to(i, (byte)temp_sum);
		i++;
    }
	if(carry != carry_limit)
		res.add_to(i, (byte)carry);
	if(res.negative != negative)
	{
		res.negative = negative;
		if(res.negative)
			std::fill(res.number.begin() + i, res.number.end(), big_num::MAX_NUM);
			//memset(res.number+i, big_num::MAX_NUM, (res.number.size()-i)*sizeof(byte));
		else
			std::fill(res.number.begin() + i, res.number.end(), 0);
	}
	return res;
}

big_num operator*(const big_num& a, const big_num& b)
{
	big_num ret = a;
	ret *= b;
	return ret;
}

big_num& operator*=(big_num& a, const big_num& b)
{
	big_num ret;
	double_byte carry = 0, temp_res = carry;
	size_t upper_limit = a.filled_blocks + b.filled_blocks;
	if(a.negative != b.negative)
		ret.negative = true;
	else
		ret.negative = false;
	big_num tempA = a;
	big_num tempB = b;
	tempA.set_same_size(tempB);
	if(a.negative)
	{
		tempA.negative = false;
		tempA.invert();
	}
	if(b.negative)
	{
		tempB.negative = false;
		tempB.invert();
	}
	size_t i;
	for(i = 0; i <= upper_limit; i++)
	{
		//carry z predchadzajucej iteracie
		temp_res = carry;
		carry = 0;
		//j - index na b, k - index na a
		size_t k = (i < a.filled_blocks) ? i : a.filled_blocks;
		size_t j = i - k;
		while(j <= b.filled_blocks && (k >= 0 && k != (size_t)0-1))
		{
			temp_res += (double_byte) tempA.number[k] * tempB.number[j];
			carry += (temp_res >> (big_num::BITS));
			//if(ret.negative)
				
			temp_res &=  big_num::MAX_NUM;
			j++;
			k--;
		}
		ret.add_to(i, (byte) temp_res);
	}
	if(carry != 0)
		ret.add_to(i, (byte)carry);
	if(ret.negative)
		ret.invert();
	ret.decimal = a.decimal + b.decimal;
	a = ret;
	return a;
}

std::ostream& operator<<(std::ostream& os, const big_num& c)
{
	os << c.to_string();
	return os;
}


bool big_num::operator==(const big_num& other) const
{
	if(this->negative != other.negative)
		return false;
	size_t i = 0;
	while(i < number.size() && number[i] == other.number[i])
		i++;
	if(i == number.size())
		return true;
	else
		return false;
}


bool big_num::operator>(const big_num& other) const
{
	if(this->negative && !other.negative)
		return false;
	else if(!negative && other.negative)
		return true;
	
	size_t i = (number.size() > other.number.size()) ? number.size() - 1 : other.number.size() - 1;
	while(i >= 0 && i != (size_t)0-1)
	{
		byte left, right;
		if(i < number.size())
			left = number[i];
		else
			left = 0;
		if(i < other.number.size())
			right = other.number[i];
		else
			right = 0;
		if(left > right)
			return true;
		else if(left < right)
			return false;
		i--;
	}
	return false;
} 

bool big_num::operator<(const big_num& other) const
{
	if(this->negative && !other.negative)
		return true;
	else if(!negative && other.negative)
		return false;
	
	size_t i = (number.size() > other.number.size()) ? number.size() - 1 : other.number.size() - 1;
	while(i >= 0)
	{
		byte left, right;
		if(i < number.size())
			left = number[i];
		else
			left = 0;
		if(i < other.number.size())
			right = other.number[i];
		else
			right = 0;
		if(left > right)
			return false;
		else if(left < right)
			return true;
		i--;
	}
	return false;
}

big_num big_num::abs() const
{
	if(!this->negative)
		return *this;
	else
	{
		big_num c = *this;
		c.negative = false;
		c.invert();
		return c;
	}
}

void big_num::invert()
{
	for(size_t i = 0; i < number.size(); i++)
		number[i] = ~number[i];
	big_num one(1);
	one.decimal = this->decimal;
	*this += one;
}

void big_num::add_to(size_t i, byte n)
{
	//std::cout << "adding to " << i << std::endl;
	if(i > (number.size() - 1))
	{
		if(negative)
			number.resize((i + 1) * 1.5, big_num::MAX_NUM);
		else
			number.resize((i + 1) * 1.5, 0);
	}
	if(i >= filled_blocks && n != number[i])
		filled_blocks = i + 1;
	number[i] = n;
}

big_num operator/(const big_num& a, byte b)
{
	big_num res;
	double_byte temp = 0;
	for(int i = a.number.size() - 1; i >= 0; i--)
	{
		temp |= a.number[i];
		res.add_to(i, (byte)(temp / b));
		temp =  (temp % b) << (sizeof(byte) * 8);
	}
	if(res.number[a.filled_blocks-1] == 0)
		res.filled_blocks = a.filled_blocks-1;
	else
		res.filled_blocks = a.filled_blocks;
	res.decimal = a.decimal;
	return res;
}

byte operator%(const big_num& a, byte b)
{
    double_byte result = 0;
	int i = a.filled_blocks-1;;
	while(i >=0)
	{
		result <<= (big_num::BITS);
		result += a.number[i];
		result -= (result / b)*b;
		i--;
    }
	return (byte)result;
}

void big_num::from_string(const std::string& str)
{
	size_t dec_pos = 0;
	for(size_t i = 0; i < str.length(); i++)
	{
		if(isdigit(str[i]))
		{
			*this *= 10;
			*this += (str[i] - '0');
		}
		else if(str[i] == '.')
		{
			dec_pos = i+1;
		}
			
	}
	if(dec_pos != 0)
		decimal = str.length() - dec_pos;
	if(str[0] == '-')
	{
		invert();
		this->negative = true;
	}
	else
		this->negative = false;
}

std::string big_num::to_string() const
{
	big_num temp = *this;
	std::string res;
	if(temp == 0)
		return "0";
	if(temp.negative)
	{
		temp.negative = false;
		temp.invert();
	}
	while(temp > 0)
	{
		res += ('0' + temp % 10);
		temp = temp/10;
		temp.decimal--;
		if(temp.decimal ==0)
			res+='.';
	}
	while(temp.decimal != 0)
	{
		res += "0";
		temp.decimal--;
		if(temp.decimal == 0)
			res += ".0";
	}
	if(*(res.end()-1) == '.')
		res += '0';
	if(negative)
		res += '-';
	int i = 0, j = (int)res.length() - 1;
	while(i < j)
	{
		char c = res[i];
		res[i] = res[j];
		res[j] = c;
		i++;
		j--;
	}
	return res;
}

void big_num::normalize(big_num& other)
{
	if(this->decimal < other.decimal)
		this->dec_shift_left(other.decimal - this->decimal);
	else if(this->decimal > other.decimal)
		other.dec_shift_left(this->decimal - other.decimal);
}

void big_num::dec_shift_left(size_t n)
{
	for(size_t i = 0; i < n; i++)
	{
		(*this) *= 10;
		decimal++;
	}
}

big_num& operator-=(big_num& a, const big_num& b)
{
	a += (-b);
	return a;
}

big_num operator-(const big_num& a, const big_num& b)
{
	big_num tempA = a;
	tempA -= b;
	return tempA;
}

big_num big_num::operator-() const
{
	big_num ret(*this);
	ret.invert();
	ret.negative = !ret.negative;
	return ret;
}

void big_num::set_same_size(big_num& other)
{
	if(this->number.size() > other.number.size())
		other.number.resize(this->number.size());
	else if(this->number.size() < other.number.size())
		this->number.resize(other.number.size());
}

