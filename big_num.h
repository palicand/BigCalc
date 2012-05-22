#ifndef __BIG_NUM_H__
#define __BIG_NUM_H__


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
	big_num(int src = 0);
	big_num(const big_num& src);
	~big_num();

	big_num& operator=(const big_num& other);
	big_num& operator=(const std::string& src);
	big_num& operator=(int n);
	//arihmetic operators
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
