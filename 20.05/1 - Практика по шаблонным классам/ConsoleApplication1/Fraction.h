#pragma once
#include <iostream>

class Fraction
{
private:
	long long numerator;
	long long denominator;

	static long long gcd(long long a, long long b);
		void reduce();
public:
	Fraction(long long numberator = 0, long long denominator = 1);
	long long getNumerator() const;
	long long getDenominator() const;

	friend Fraction operator+(const Fraction& a, const Fraction& b);
	friend Fraction operator-(const Fraction& a, const Fraction& b);
	friend Fraction operator*(const Fraction& a, const Fraction& b);
	friend Fraction operator/(const Fraction& a, const Fraction& b);

	friend bool operator==(const Fraction& a, const Fraction& b);
	friend bool operator!=(const Fraction& a, const Fraction& b);
	friend bool operator<(const Fraction& a, const Fraction& b);
	friend bool operator>(const Fraction& a, const Fraction& b);

	friend std::ostream& operator<<(std::ostream& os, const Fraction& f);
	friend std::istream& operator>>(std::istream& is, Fraction& f);
};

