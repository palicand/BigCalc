#ifndef __BIG_NUM_H__
#define __BIG_NUM_H__
/**
\file
\brief contains the declaration of the \ref big_num class

\class big_num
\brief the class representing the big number
\details The class stores the number as a block sequence of bytes of the binary representation of the number (using the two's complement). Additionally, it stores the position of
the decimal point in the decimal representation of the number, which it updates while doing the arithmetics.

\fn big_num::big_num(const std::string&)
\brief constructs the number from the passed string
\details the string must consist of at least one digit to the left of the decimal point and an optional decimal point and the fraction.
\param num the string representation of number

\fn big_num::big_num(signed char)
\brief constructs the big_num out of a small number (small meaning in the range of a signed char)
\param num the small number

\fn big_num::big_num(const big_num&)
\brief constructs a big_num out of other big_num
\details creates an exact copy of the source big_num
\param src the source big_num out of which the new one will be created

\fn big_num::operator=(const std::string&)
\brief discards current content and creates number out of the string
\param num the string representation of a number
\return the reference to calling object

\fn big_num::operator=(const big_num&)
\brief copies the content from the source big_num over the current content
\param src the source big_num from which we will copy
\return the reference to calling object

\fn big_num::operator=(signed char)
\brief destroys the current content and creates new number from the passed number
\param the small source number
\return the reference to calling object

*/

#include <string>
#include <vector>
#include <climits>
#include <iostream>
#include <cmath>

typedef unsigned char byte;
typedef unsigned short double_byte;

class big_num
{
public:
	big_num(const std::string& num);
	big_num(signed char num = 0);
	big_num(const big_num& src);
	~big_num();

	big_num& operator=(const big_num& src);
	big_num& operator=(const std::string& num);
	big_num& operator=(signed char num);
	//arihmetic operators
	/**
	\brief the adition operation
	*/
	friend big_num& operator+=(big_num& a, const big_num& b);
	friend big_num operator+(const big_num& a, const big_num& b);
	friend big_num& operator-=(big_num& a, const big_num& b);
	friend big_num operator-(const big_num& a, const big_num& b);
	friend big_num& operator*=(big_num& a, const big_num& b);
	friend big_num operator*(const big_num& a, const big_num& b);
	//comparison operators
	big_num operator-() const;
	
	friend std::ostream& operator<<(std::ostream& os, const big_num& num);
	big_num abs() const;
private:
	std::vector<byte> number;
	size_t decimal;
	size_t filled_blocks;
	bool negative;
	static const byte MAX_NUM;
	static const int BITS;
	static const size_t START_ALLOCATION;
	void from_string(const std::string& src);
	std::string to_string() const;
	void add_digit(char digit);
	void invert();
	void add_to(size_t i, byte n);
	void normalize(big_num& other);
	void dec_shift_left(size_t n);
	void set_same_size(big_num& other);

	bool operator==(const big_num& other) const;
	bool operator>(const big_num& other) const;
	bool operator<(const big_num& other) const;
	bool operator!=(const big_num& other) const;
	friend big_num operator/(const big_num& a, byte b);
	friend byte operator%(const big_num& a, byte b);
};

#endif
