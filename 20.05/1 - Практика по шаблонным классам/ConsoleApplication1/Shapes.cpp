#include "Shapes.h"
#include <cmath>
#include <stdexcept>

int Shape::figureCount = 0;

Shape::Shape()
{
	figureCount++;
}

Shape::~Shape()
{
	figureCount--;
}
int Shape::getFigureCount()
{
	return figureCount;
}

Circle::Circle(double radius)
{
	if (radius <= 0)
	{
		throw invalid_argument("радиус должен быть положительным");
	}

	this->radius = radius;
}

double Circle::area() const
{
	const double pi = 3.141592653589793;
	return pi * radius * radius;
}

double Circle::perimeter() const
{
	const double pi = 3.141592653589793;
	return pi * 2 * radius;
}
void Circle::print() const
{
	cout << "Круг, Радиус = " << radius << endl;
}

Rectangle::Rectangle(double width, double height)
{
	if (width <=0|| height <=0)
	{
		throw invalid_argument("Стороны прямоугольника должны быть положительными");
	}
	this->width = width;
	this->height = height;
}
double Rectangle::area() const
{
	return width * height;
}

double Rectangle::perimeter() const
{
	return 2 * (width * height);
}

void Rectangle::print() const
{
	cout << " Прямоугольник, Ширина = " << width << ", Высота = " << height << endl;
}

Triangle::Triangle(double a, double b, double c)
{
	if (a <=0, b <=0, c<=0)
	{
		throw invalid_argument("Стороны треугольника должны быть положительными");
	}
	this->a = a;
	this->b = b;
	this->c = c;
}

double Triangle::area() const
{
	double p = perimeter() / 2.0;
	return sqrt(p * (p - a) * (p - b) * (p - c));
}

double Triangle::perimeter() const
{
	return a + b + c;
}
void Triangle::print() const
{
	cout << "Треугольник, Стороны = " << a << ", " << b << ", " << c << endl;
}
