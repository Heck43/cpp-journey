#include "Fraction.h"
#include <stdexcept>
#include <iostream>
#include <cstdlib>

long long Fraction::gcd(long long a, long long b)
{
	a = llabs(a);
	b = llabs(b);

	while (b != 0) {
		long long temp = b;
		b = a % b;
		a = temp;
	}
	return a;
}

void Fraction::reduce()
{
	if (denominator == 0)
	{
		throw std::invalid_argument("error");
	}
	if (denominator < 0)
	{
		numerator = -numerator;
		denominator = -denominator;
	}
	long long divisor = gcd(numerator, denominator);

	if (divisor != 0)
	{
		numerator /= divisor;
		denominator /= divisor;
	}
}
Fraction::Fraction(long long numerator, long long denominator)
{
	this->numerator = numerator;
	this->denominator = denominator;
	reduce();
}

	long long Fraction::getNumerator() const 
	{
		return numerator;
	}

	long long Fraction::getDenominator() const
	{
		return denominator;
	}

	Fraction operator+(const Fraction& a, const Fraction& b)
	{
		return Fraction(
			a.numerator * b.denominator + b.numerator * a.denominator,
			a.denominator * b.denominator
		);
	}
	Fraction operator-(const Fraction& a, const Fraction& b) 
	{
		return Fraction(
			a.numerator * b.denominator - b.numerator * a.denominator,
			a.denominator * b.denominator
		);
	}
	Fraction operator*(const Fraction& a, const Fraction& b)
	{
		return Fraction(
			a.numerator * b.numerator,
			a.denominator * b.denominator
		);

	}
	Fraction operator/(const Fraction& a, const Fraction& b)
	{
		if (b.numerator == 0)
		{
			throw std::invalid_argument("error");
		}

		return Fraction(
			a.numerator * b.denominator,
			a.denominator * b.numerator
		);

	}

	bool operator==(const Fraction& a, const Fraction& b)
	{
		return a.numerator == b.numerator && a.denominator == b.denominator;
	}
	bool operator!=(const Fraction& a, const Fraction& b)
	{
		return!(a == b);
	}
	bool operator<(const Fraction& a, const Fraction& b)
	{
		return a.numerator * b.denominator < b.numerator * a.denominator;
	}
	bool operator>(const Fraction& a, const Fraction& b)
	{
		return b < a;
	}

	std::ostream& operator<<(std::ostream& os, const Fraction& f)
	{
		os << f.getNumerator() << "/" << f.getDenominator();
		return os;
	}
	std::istream& operator>>(std::istream& is, Fraction & f)
	{
		long long n;
		long long d;

		std::cout << "enter num: ";
		is >> n;

		std::cout << "enter den: ";
		is >> d;

		return is;
	}

