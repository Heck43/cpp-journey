//метод compare()
// он сравнивает строки и возвращает 0, если строки идентичные, отрицательное число, если строка меньше другой и положительное число, если строка больше другой.
#pragma once
#include <iostream>
#include <string>

void pass()
{
	std::string pass1, pass2;

	std::cout << "Введите пароль: " << std::endl;
	std::cin >> pass1;
	std::cout << "Подтвердите пароль: " << std::endl;
	std::cin >> pass2;

	//туть идет сравнение двух строк(паролей)
	if(pass1.compare(pass2) == 0)
	{
		std::cout << "Пароли совпадают!" << std::endl;
	}
	else
	{
		std::cout << "Пароли не совпадают!" << std::endl;
	}
};

