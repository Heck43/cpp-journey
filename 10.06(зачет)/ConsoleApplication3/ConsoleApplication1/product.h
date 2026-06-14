#include <iostream>
#pragma once
// Базовый класс product — хранит общие данные любого товара
class product {
protected:
	std::string name;
	double price;
	int id;
public:
	product(std::string& name, double price, int id);
	virtual ~product() = default;

	int getId() const;
	std::string getName() const;
	double getPrice() const;

	virtual void displayInfo() const;
};
