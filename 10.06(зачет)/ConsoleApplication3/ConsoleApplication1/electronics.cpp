#include "electronics.h"
#include <iostream>

// Реализация конструктора класса electronics
electronics::electronics(std::string& name, double price, int id, std::string& model)
	: product(name, price, id), model(model) {}

std::string electronics::getModel() const { return model; }

// Выводим информацию об электронике, включая модель
void electronics::displayInfo() const {
	product::displayInfo();
	std::cout << "     Тип: Электроника | Модель: " << model << std::endl;
}
