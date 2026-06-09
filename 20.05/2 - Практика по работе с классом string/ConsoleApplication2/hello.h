#pragma once
#include <string>
#include <iostream>
using namespace std;

void hello()
{
			string name;
			cout << "enter your name: " << endl;
			cin >> name;

			cout << "hello " << name << endl;
			// length() - возвращает количество символов в строке
			cout << name.length() << " characters in your name" << endl;
			cout << "the first character of your name is: " << name.at(0) << endl;
}

