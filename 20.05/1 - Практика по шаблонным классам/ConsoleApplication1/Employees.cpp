#include "Employees.h"
#include <sstream>
#include <algorithm>

Employees::Employees(string name, int id, double baseSalary)
{
	this->name = name;
	this->id = id;
	this->baseSalary = baseSalary;
}
Employees::~Employees()
{
}
int Employees::getId() const
{
	return id;
}
string Employees::getName() const
{
	return name;
}
double Employees::getBaseSalary() const
{
	return baseSalary;
}
double Employees::calculateSalary() const
{
	return baseSalary;
}
string Employees::getinfo() const
{
	ostringstream out;
	out << "employee: "
		<< "id = " << id
		<< ", name = " << name
		<< ", salary = " << calculateSalary();

	return out.str();
}

Manager::Manager(string name, int id, double baseSalary, double bonusPercent, int subordinatesCount) :Employees(name,id,baseSalary)
{
	this->bonusPercent = bonusPercent;
	this->subordinatesCount = subordinatesCount;
}
double Manager::calculateSalary() const
{
	return baseSalary + bonusPercent * 100 * subordinatesCount;
}

string Manager::getinfo() const
{
	ostringstream out;

	out << "manager: "
		<< "id = " << id
		<< ", name = " << name
		<< ", base salary = " << baseSalary
		<< ", bonus percent = " << bonusPercent
		<< ", subordinates = " << subordinatesCount
		<< ", salary = " << calculateSalary();

	return out.str();
}

Developer::Developer(string name, int id, double baseSalary, string programmingLanguage, int experienceYears) : Employees(name, id, baseSalary)
{
	this->programmingLanguage = programmingLanguage;
	this->experienceYears = experienceYears;
}
double Developer::calculateSalary() const
{
	return baseSalary + experienceYears * 5000;
}
string Developer::getinfo() const
{
	ostringstream out;

	out << "developer: "
		<< "id = " << id
		<< ", name = " << name
		<< ", language = " << programmingLanguage
		<< ", experience = " << experienceYears
		<< ", salary = " << calculateSalary();

	return out.str();
}
Inter::Inter(string name, int id, double baseSalary, bool hasMentor) :Employees(name, id, baseSalary)
{
	this->hasMentor;
}
double Inter::calculateSalary() const
{
	return baseSalary * 0.7;
}
string Inter::getinfo() const
{
	ostringstream out;

	out << "intern: "
		<< "id = " << id
		<< ", name = " << name
		<< ", has mentor = " << boolalpha << hasMentor
		<< ", salary = " << calculateSalary();

	return out.str();
}

Department::Department(string title) :Employees(name, id, baseSalary)
{
	this->title = title;
}
void Department::addEmployees(Employees* employees)
{
	if (employees != nullptr)
	{
		this->employees.push_back(employees);
	}
}
void Department::removeEmployeesById(int id)
{
	employees.erase(
		remove_if(
			employees.begin(),
			employees.end(),
			[id](Employees* employees)
			{
				return employees != nullptr && employees->getId() == id;
			}
		),
		employees.end()
	);
}
double Department::getTotalSalary() const
{
	double sum = 0;
	
	for (Employees* employees:employees)
	{
		if (employees!=nullptr)
		{
			sum += employees->calculateSalary();
		}
	}
	return sum;
}
Employees* Department::findMaxSalaryEmployee() const
{
	if (employees.empty())
	{
		return nullptr;
	}

	Employees* maxEmployee = employees[0];

	for (Employees* employees:employees)
	{
		if (employees != nullptr && employees->calculateSalary()>maxEmployee->calculateSalary())
		{
			maxEmployee = employees;
		}
	}
	return maxEmployee;
}
void Department::sortBySalary()
{
	sort(
		employees.begin(),
		employees.end(),
		[](Employees* a, Employees* b)
		{
			return a->calculateSalary() > b->calculateSalary();
		}
	);
}

void Department::printAll() const
{
	cout << "department: " << title << endl;
	for (Employees* employees : employees)
	{
		if (employees != nullptr)
		{
			cout << employees->getinfo() << endl;
		}
	}
}