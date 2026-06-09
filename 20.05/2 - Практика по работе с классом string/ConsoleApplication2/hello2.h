#pragma once
#include <iostream>
#include <string>
void hello2()
	{
		std::string name;
		std::cout << "Введите ваше имя и фамилию: " << std::endl;
		std::cin.ignore(); // Очистка буфера ввода перед чтением строки
		// getline() позволяет считывать строку с пробелами, в отличие от оператора >>, который останавливается на первом пробеле
		std::getline(std::cin, name);
		std::string greeting = "Доброе утро, " + name + "!";
		std::cout << greeting << std::endl;
	}
