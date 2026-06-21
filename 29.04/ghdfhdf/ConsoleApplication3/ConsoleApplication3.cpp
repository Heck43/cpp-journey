#include <iostream>
#include <cstring>  // Для strlen, strcpy_s — безопасная работа с char*
#include <windows.h>

// Задача 3: «Веб-ссылка»
// Демонстрируем конструктор с параметрами и ручное управление памятью через new/delete

class WebLink {
private:
    // Указатели на строки в куче — память выделяем сами в конструкторе
    char* url;
    char* description;

public:
    // Конструктор с параметрами — объект сразу создаётся с заполненными данными
    // strlen + 1: +1 нужен для нулевого символа \0 в конце строки
    WebLink(const char* linkUrl, const char* linkDesc) {
        url = new char[strlen(linkUrl) + 1];
        strcpy_s(url, strlen(linkUrl) + 1, linkUrl);

        description = new char[strlen(linkDesc) + 1];
        strcpy_s(description, strlen(linkDesc) + 1, linkDesc);
    }

    // Деструктор — освобождаем память когда объект уничтожается
    // Без этого будет утечка памяти, потому что new без delete = память не возвращается
    ~WebLink() {
        delete[] url;
        delete[] description;
    }

    // Аксессор: выводит информацию о ссылке в нужном формате
    void print() const {
        std::cout << "Описание: " << description << std::endl;
        std::cout << "Адрес: " << url << std::endl;
    }
};

void task3() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    // Создаём объект одной строкой — конструктор сам выделяет память и копирует строки
    WebLink mySite("https://academy.top", "Сайт Компьютерной Академии");

    mySite.print();

}
