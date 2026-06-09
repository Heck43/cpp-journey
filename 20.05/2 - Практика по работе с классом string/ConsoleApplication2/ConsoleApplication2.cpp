#include <iostream>
#include <string>


#include "hello.h"
#include "hello2.h"
#include "find.h"
#include "toupper.h"
#include "insert_replace.h"
#include "error404.h"
#include "ABCDEFGHIJKLMNOPQRSTUVWXYZ.h"
#include "pass.h"
#include "clear.h"
using namespace std;

int main()
{
	try
	{
		int num;
		do
		{
			setlocale(LC_ALL, "Russian");
			cout << endl;
			cout << "1. Привет Мир!" << endl;
			cout << "2. Доброе утро!" << endl;
			cout << "3. Найти слово в тексте" << endl;
			cout << "4. Преобразовать строку в верхний регистр" << endl;
			cout << "5. Вставить и заменить слово в тексте" << endl;
			cout << "6. Извлечь код ошибки из строки" << endl;
			cout << "7. Удалить буквы из алфавита" << endl;
			cout << "8. Сравнить пароли" << endl;
			cout << "9. Очистить строку" << endl;
			cout << "0. Exit" << endl;
			cin >> num;

			switch (num)
			{
			case 1:
				hello();
				break;

			case 2:
				hello2();
				break;

			case 3:
				fund();
				break;

			case 4:
				toupper1();
				break;

			case 5:
				insert_replace();
				break;

			case 6:
				error404();
				break;

			case 7:
				ABCDEFGHIJKLMNOPQRSTUVWXYZ();
				break;

			case 8:
				pass();
				break;

			case 9:
				clear();
				break;

			case 0:
				cout << "bye!.." << endl;
				break;

			default:
				cout << "error" << endl;
				break;
			} 
		} while (num != 0);
	}
	catch (const exception& ex)
	{
		cout << "error: " << ex.what() << endl;
	}
	return 0;
}