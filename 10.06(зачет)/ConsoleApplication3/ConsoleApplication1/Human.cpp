#include "Human.h"
#include "product.h"
#include <vector>
#include <iostream>

// Реализация конструктора класса Human
Human::Human(std::string& name, double balance) : name(name), balance(balance) {}

// Геттер имени
std::string Human::getName() const { return name; }

// Геттер баланса
double Human::getBalance() const { return balance; }

// Метод покупки товара — проверяет баланс и добавляет в корзину
bool Human::buyproduct(std::vector<product*> items)
{
	// Если список пуст — сообщаем пользователю
	if (items.empty()) {
		std::cout << "Корзина пуста!" << std::endl;
		return false;
	}

	// Считаем общую стоимость переданных товаров
	double totalCost = 0.0;
	for (const auto& item : items) {
		if (item != nullptr) {
			totalCost += item->getPrice();
		}
	}

	// Проверяем, хватает ли баланса
	if (balance >= totalCost) {
		balance -= totalCost;
		for (const auto& item : items) {
			if (item != nullptr) {
				// Добавляем купленный товар в корзину пользователя
				cart.push_back(item);
				std::cout << "Куплено: " << item->getName()
					<< " за " << item->getPrice() << " руб." << std::endl;
			}
		}
		std::cout << "Остаток на счёте: " << balance << " руб." << std::endl;
		return true;
	}
	else {
		std::cout << "Недостаточно средств! Нужно: " << totalCost
			<< " руб., есть: " << balance << " руб." << std::endl;
		return false;
	}
}

// Метод показа корзины с купленными товарами
void Human::showCart() const
{
	// Если корзина пуста — сообщаем пользователю
	if (cart.empty()) {
		std::cout << "Ваша корзина пуста." << std::endl;
		return;
	}

	// Показываем все товары в корзине
	std::cout << "\n=== Ваши покупки ===" << std::endl;
	double total = 0.0;
	for (const auto& item : cart) {
		item->displayInfo();
		total += item->getPrice();
	}
	std::cout << "Итого потрачено: " << total << " руб." << std::endl;
	std::cout << "Остаток на счёте: " << balance << " руб." << std::endl;
}
