#include "clothes.h"
#include <iostream>

// Реализация конструктора класса clothes
clothes::clothes(std::string& name, double price, int id, std::string& size)
	: product(name, price, id), size(size) {}

std::string clothes::getSize() const { return size; }

// Выводим информацию об одежде, включая размер
void clothes::displayInfo() const {
	product::displayInfo();
	std::cout << "     Тип: Одежда | Размер: " << size << std::endl;
}
