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
\param num the small source number
\return the reference to calling object

*/

#include <string>
#include <vector>
#include <climits>
#include <iostream>
#include <cmath>
/**
\brief The type of one block of array used for the representation of a number
*/
typedef unsigned char byte;
/**
\brief The type that has 2x more bits than the byte
*/
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
	\brief Adds a and b and stores the result in a
	\param a the left operand
	\param b the right operand
	\return reference to the a
	*/
	friend big_num& operator+=(big_num& a, const big_num& b);

	/**
	\brief adds the a and b and returns the result
	\param a the left operand
	\param b the right operand
	\return the result

	\details 
	*/
	friend big_num operator+(const big_num& a, const big_num& b);
	/**
	\brief Subracts b from a and stores the result in a
	\param a the left operand
	\param b the right operand
	\return the reference to a
	*/
	friend big_num& operator-=(big_num& a, const big_num& b);
	/**
	\brief Subracts b from a and returns the result
	\param a the left operand
	\param b the right operand
	\return The result
	*/
	friend big_num operator-(const big_num& a, const big_num& b);
	/**
	\brief multiplies a by b and stores the result in a
	\param a the left operand
	\param b the right operand
	\return the reference to a
	*/
	friend big_num& operator*=(big_num& a, const big_num& b);

	/**
	\brief multiplies a by b and returns the result
	\param a the left operand
	\param b the right operand
	\return the result
	*/
	friend big_num operator*(const big_num& a, const big_num& b);

	/**
	\brief the unary - operator, it returns the number with inverted sign
	\return the inverted number
	*/
	big_num operator-() const;
	
	/**
	\brief Prints the number to the defined output stream
	\param os the output stream
	\param num the number to be printed
	\return the modified output stream
	*/
	friend std::ostream& operator<<(std::ostream& os, const big_num& num);

	/**
	\brief the absolute value of a number
	*/
	big_num abs() const;
private:
	/**
	\brief the array of numbers
	*/
	std::vector<byte> number;
	/**
	number of decimal digits
	*/
	size_t decimal;
	/**
	\brief number of blocks filled with something meaningful
	*/
	size_t filled_blocks;
	/**
	\brief is nmber negative?
	*/
	bool negative;

	/**
	\brief the max value in one element of n. array
	*/
	static const byte MAX_NUM;
	/**
	\brief number of bits in one component
	*/
	static const int BITS;
	/**
	\brief the startig allocation size
	*/
	static const size_t START_ALLOCATION;
	/**
	\brief gets number from src
	*/
	void from_string(const std::string& src);
	/**
	\brief coverts number to string
	*/
	std::string to_string() const;
	/**
	\brief inverts all the numbers in the array
	*/
	void invert();
	/**
	\brief inserts n at position i in the number array, resizes the array if needed
	*/
	void add_to(size_t i, byte n);
	/**
	\brief sets the numbers to have the same number of decimal digits by calling the dec_shift_left while also increasing the number of decimal digits
	*/
	void normalize(big_num& other);
	/**
	\brief multiplies the number n times by 10
	*/
	void dec_shift_left(size_t n);
	/**
	\brief resizes the  number array to the same size if it's different
	*/
	void set_same_size(big_num& other);

	bool operator==(const big_num& other) const;
	bool operator>(const big_num& other) const;
	bool operator<(const big_num& other) const;
	bool operator!=(const big_num& other) const;
	friend big_num& operator/=(big_num& a, byte b);
	friend byte operator%(const big_num& a, byte b);
};

#endif
