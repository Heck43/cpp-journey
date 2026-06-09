#pragma once
#include <iostream>

using namespace std;
class Shape
{
private: 
	static int figureCount;

public:
	Shape();
	virtual ~Shape();
	virtual double area() const = 0;
	virtual double perimeter() const = 0;
	virtual void print() const = 0;

	static int getFigureCount();
};

class Circle:public Shape
{
private:
	double radius;
public:
	explicit Circle(double radius);

	double area() const override;
	double perimeter() const override;
	void print() const override;
};
class Rectangle:public Shape
{
private:
	double width;
	double height;
public:
	Rectangle(double width, double height);

	double area() const override;
	double perimeter() const override;
	void print() const override;
};

class Triangle:public Shape
{
private:
	double a;
	double b;
	double c;
public:
	Triangle(double a, double b, double c);

	double area() const override;
	double perimeter() const override;
	void print() const override;
};

