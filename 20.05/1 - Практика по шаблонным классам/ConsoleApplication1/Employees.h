#pragma once
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Employees
{
protected:
	string name;
	int id;
	double baseSalary;

public:
	Employees(string name, int id, double baseSalary);
	virtual ~Employees();

	int getId() const;
	string getName() const;
	double getBaseSalary() const;

	virtual double calculateSalary() const;
	virtual string getinfo() const;
};

class Manager:public Employees
{
private:
	double bonusPercent;
	int subordinatesCount;

public:
	Manager(string name, int id, double baseSalary, double bonusPercent, int subordinatesCount); 
	double calculateSalary() const override;
	string getinfo() const override;
};

class Developer:public Employees
{
private:
	string programmingLanguage;
	int experienceYears;
public:
	Developer(string name, int id, double baseSalary, string programmingLanguage, int experienceYears);

	double calculateSalary() const override;
	string getinfo() const override;

};

class Inter :public Employees
{
private:
	bool hasMentor;
public:
	Inter(string name, int id, double baseSalary, bool hasMentor);

	double calculateSalary() const override;
	string getinfo() const override;
};
class Department :public Employees
{
private:
	string title;
	vector<Employees*> employees;
public:
	explicit Department(string title);
	void addEmployees(Employees* employees);
	void removeEmployeesById(int id);

	double getTotalSalary() const;
	Employees* findMaxSalaryEmployee() const;

	void sortBySalary();
	void printAll() const;
};


