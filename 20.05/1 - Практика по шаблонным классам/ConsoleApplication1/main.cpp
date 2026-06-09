#include <iostream>
#include <clocale>

#include "Fraction.h"
#include "Matrix.h"
#include "Shapes.h"
#include "Employees.h"
using namespace std;

void taskFracion()
{
	cout << "\n===1.1 fraction===\n" << endl;

	Fraction a(1, 2);
	Fraction b(3, 4);

	cout << "a = " << a << endl;
	cout << "b = " << b << endl;

	cout << "a + b = " << a + b << endl;
	cout << "a - b =  " << a - b << endl;
	cout << "a * b = " << a * b << endl;
	cout << "a / b = " << a / b << endl;

	cout << boolalpha;
	cout << "a == b = " << (a == b) << endl;
	cout << "a != b =  " << (a != b) << endl;
	cout << "a < b = " << (a < b) << endl;
	cout << "a > b = " << (a > b) << endl;
}

void taskMatrix()
{
	cout << "\n===1.2 Matrix===\n" << endl;
	Matrix a(2, 2);
	Matrix b(2, 2);
	a(0, 0) = 1;
	a(0, 1) = 2;
	a(1, 0) = 3;
	a(1, 1) = 4;

	b(0, 0) = 5;
	b(0, 1) = 6;
	b(1, 0) = 7;
	b(1, 1) = 8;

	cout << "matrix a:\n" << a << endl;
	cout << "matrix b:\n" << b << endl;

	cout << "a + b:\n" << a + b << endl;
	cout << "a - b:\n" << a - b << endl;
	cout << "a * b:\n" << a * b << endl;
	cout << "a * 2:\n" << a * 2 << endl;
	cout << "2 * a:\n" << 2 * a << endl;

	cout << "transpose !a:\n" << !a << endl;

	Matrix c = a;
	Matrix d(2, 2);
	d = b;

	cout << "copy c = a:\n" << c << endl;
	cout << "assignment d = b:\n" << d << endl;

	cout << boolalpha;
	cout << "a == c: " << (a == c) << endl;
	cout << "a != b: " << (a != b) << endl;

}

void taskShapes()
{
	cout << "\n=== task 2.1 shapes ===\n";

	Shape* shapes[] =
	{
		new Circle(5),
		new Rectangle(3, 4),
		new Triangle(3, 4, 5)
	};

	for (int i = 0; i < 3; i++)
	{
		shapes[i]->print();
		cout << "Радиус = " << shapes[i]->area() << endl;
		cout << "Периметр = " << shapes[i]->perimeter() << endl;
		cout << endl;
	}

	cout << "цифры считаются = " << Shape::getFigureCount() << endl;

	for (int i = 0; i < 3; i++)
	{
		delete shapes[i];
	}

	cout << "цифры считаются после удаления = " << Shape::getFigureCount() << endl;
}
void taskEmployees()
{
	cout << "\n=== task 2.2 employees ===\n";

	Manager manager("anna", 1, 90000, 10, 5);
	Developer developer("ivan", 2, 80000, "c++", 3);
	Inter intern("oleg", 3, 30000, true);

	Department department("it department");

	department.addEmployees(&manager);
	department.addEmployees(&developer);
	department.addEmployees(&intern);

	cout << "\nall employees:\n";
	department.printAll();

	cout << "\ntotal salary = " << department.getTotalSalary() << endl;

	Employees* maxEmployee = department.findMaxSalaryEmployee();
	if (maxEmployee != nullptr)
	{
		cout << "\nmax salary employee:\n";
		cout << maxEmployee->getinfo() << endl;
	}

	department.sortBySalary();

	cout << "\nafter sort by salary:\n";
	department.printAll();

	department.removeEmployeesById(3);

	cout << "\nafter remove intern:\n";
	department.printAll();
}

int main()
{

	try
	{
		int choise;
		do
		{
			setlocale(LC_ALL, "Russian");
			cout << "\n====================Menu===================\n";
			cout << "1. - Fraction\n";
			cout << "2. - Matrix\n";
			cout << "3. - Shapes\n";
			cout << "4. - Employees\n";
			cout << "0  - Exit\n";
			cin >> choise;

			switch (choise)
			{
			case 1:
				taskFracion();
				break;
			case 2:
				taskMatrix();
				break;
			case 3:
				taskShapes();
				break;
			case 4:
				taskEmployees();
				break;
			case 0:
				cout << "bye....\n";
				break;
			default:
				cout << "wrong choise....\n";
				break;
			}
		} while (choise != 0);
	}
	catch (const exception& ex)
	{
		cout << "error: " << ex.what() << endl;
	}
	return 0;
}