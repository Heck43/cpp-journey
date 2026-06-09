#pragma once
#include <iostream>
#include <string>
void clear()
{
	std::string text = "Это важное сообщение";
	std::cout << text << std::endl;
	std::cout << "Длина строки: " << text.length() << std::endl;


	//метод clear - очищяет строку, удаляя все символы и устанавливая длину строки в 0. После вызова clear() строка будет пустой, и ее длина будет равна 0.
	text.clear();
	std::cout << "строка очищенна. Длина: " << text.length() << std::endl;

	// туть проверка на то, пуста ли строчка?
	if (text.empty())
	{
		std::cout << "строка пустая" << std::endl;
	}
	else
	{
		std::cout << "строка не пустая" << std::endl;
	}
};

