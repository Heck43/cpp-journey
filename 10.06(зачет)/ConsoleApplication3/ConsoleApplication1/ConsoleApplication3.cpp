#include <iostream>
// #define NOMINMAX — это директива препроцессора, которая предотвращает определение макросов min и max в Windows.h.
// Это полезно, чтобы избежать конфликтов с функциями std::min и std::max из стандартной библиотеки C++.
// Но мы используем Windows.h для настройки кодировки консоли, чтобы корректно отображать русский текст.
// Поэтому мы определяем NOMINMAX перед включением Windows.h, чтобы избежать проблем с макросами min и max,
// которые могут возникать при использовании стандартных функций C++.
#define NOMINMAX
#include <Windows.h>
#include <vector>
#include <limits>

#include "product.h"
#include "electronics.h"
#include "clothes.h"
#include "food.h"
#include "Human.h"

// Показываем каталог доступных товаров
void showCatalog(const std::vector<product*>& catalog) {
	std::cout << "\n========== Каталог товаров ==========" << std::endl;
	for (const auto& item : catalog) {
		item->displayInfo();
	}
	std::cout << "=====================================" << std::endl;
}

int main() {
	// Устанавливаем UTF-8 для корректного вывода русского текста
	SetConsoleCP(65001);
	SetConsoleOutputCP(65001);

	// Наполняем витрину магазина товарами разных классов
	std::vector<product*> shopShowcase;

	std::string n1 = "Смартфон Samsung";   std::string m1 = "Galaxy A55";
	std::string n2 = "Ноутбук Lenovo";     std::string m2 = "IdeaPad 3";
	std::string n3 = "Куртка зимняя";      std::string s1 = "XL";
	std::string n4 = "Джинсы Levis";       std::string s2 = "M";
	std::string n5 = "Шоколад Lindt";      std::string e1 = "2025-12-01";
	std::string n6 = "Кофе Lavazza";       std::string e2 = "2026-06-15";

	// Добавляем электронику (класс electronics)
	shopShowcase.push_back(new electronics(n1, 35990.0, 1, m1));
	shopShowcase.push_back(new electronics(n2, 52500.0, 2, m2));

	// Добавляем одежду (класс clothes)
	shopShowcase.push_back(new clothes(n3, 4800.0, 3, s1));
	shopShowcase.push_back(new clothes(n4, 3200.0, 4, s2));

	// Добавляем еду (класс food)
	shopShowcase.push_back(new food(n5, 280.0, 5, e1));
	shopShowcase.push_back(new food(n6, 650.0, 6, e2));

	// Создаём покупателя с начальным балансом
	std::string customerName = "Иван";
	Human customer(customerName, 15000.0);

	std::cout << "Добро пожаловать в магазин!" << std::endl;
	std::cout << "Покупатель: " << customer.getName()
		<< " | Баланс: " << customer.getBalance() << " руб." << std::endl;

	// Главный цикл — интерактивный интерфейс для покупателя
	int choice = -1;
	while (choice != 0) {
		showCatalog(shopShowcase);
		std::cout << "\nВведите ID товара для покупки (0 - завершить): ";
		std::cin >> choice;

		// Защита от некорректного ввода
		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Некорректный ввод, попробуйте ещё раз." << std::endl;
			continue;
		}

		if (choice == 0) break;

		// Ищем товар с нужным ID в витрине
		product* selected = nullptr;
		for (const auto& item : shopShowcase) {
			if (item->getId() == choice) {
				selected = item;
				break;
			}
		}

		if (selected == nullptr) {
			std::cout << "Товар с таким ID не найден." << std::endl;
			continue;
		}

		// Передаём выбранный товар в корзину для покупки
		std::vector<product*> singleItem = { selected };
		customer.buyproduct(singleItem);
	}

	// Показываем итоговую корзину покупателя
	customer.showCart();

	// Освобождаем память
	for (auto ptr : shopShowcase) delete ptr;

	return 0;
}
