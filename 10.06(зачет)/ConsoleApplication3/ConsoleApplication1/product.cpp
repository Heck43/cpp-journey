#include "product.h"

// Реализация конструктора базового класса product
product::product(std::string& name, double price, int id) : name(name), price(price), id(id) {}

// Реализация метода getName для получения имени продукта
std::string product::getName() const {
	return name;
}

// Реализация метода getPrice для получения цены продукта
double product::getPrice() const {
	return price;
}

// Реализация метода getId для получения идентификатора продукта
int product::getId() const {
	return id;
}

// Реализация метода displayInfo для отображения информации о товаре
void product::displayInfo() const {
	std::cout << "  [ID: " << id << "] " << name << " — " << price << " руб." << std::endl;
}
