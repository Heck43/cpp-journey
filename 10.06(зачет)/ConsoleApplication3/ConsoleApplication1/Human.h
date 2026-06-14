#pragma once
#include "product.h"
#include <iostream>
#include <vector>
// Класс Human — покупатель с балансом и корзиной купленных товаров
class Human
{
private:
	std::string name;
	double balance;
	std::vector<product*> cart; // корзина — хранит купленные товары

public:
	Human(std::string& name, double balance);
	std::string getName() const;
	double getBalance() const;

	bool buyproduct(std::vector<product*> items);
	void showCart() const;
};
