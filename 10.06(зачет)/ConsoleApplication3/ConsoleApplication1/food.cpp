#include "food.h"
#include <iostream>

// Реализация конструктора класса food
food::food(std::string& name, double price, int id, std::string& expirationDate)
	: product(name, price, id), expirationDate(expirationDate) {}

std::string food::getExpirationDate() const { return expirationDate; }

// Выводим информацию о продукте питания, включая срок годности
void food::displayInfo() const {
	product::displayInfo();
	std::cout << "     Тип: Еда | Срок годности: " << expirationDate << std::endl;
}
