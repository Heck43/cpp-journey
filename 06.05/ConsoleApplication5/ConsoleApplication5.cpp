#include <iostream>
#include <cstring>
#include <vector>
#include <windows.h>

// ===== Задание 5: «Телефонная книга» =====

class Contact {
private:
    char*  fullName;    // ФИО — динамическая память
    char   homePhone[20];
    char   workPhone[20];
    char   mobilePhone[20];
    char   extraInfo[100];

    // Вспомогательный метод копирования строки
    static char* copyStr(const char* src) {
        char* dst = new char[strlen(src) + 1];
        strcpy_s(dst, strlen(src) + 1, src);
        return dst;
    }

public:
    // Конструктор с параметрами
    Contact(const char* name, const char* home, const char* work,
            const char* mobile, const char* extra)
    {
        fullName = copyStr(name);
        strcpy_s(homePhone,   sizeof(homePhone),   home);
        strcpy_s(workPhone,   sizeof(workPhone),   work);
        strcpy_s(mobilePhone, sizeof(mobilePhone), mobile);
        strcpy_s(extraInfo,   sizeof(extraInfo),   extra);
    }

    // Конструктор копирования — fullName на куче, нужно копировать отдельно
    Contact(const Contact& other) {
        fullName = copyStr(other.fullName);
        strcpy_s(homePhone,   sizeof(homePhone),   other.homePhone);
        strcpy_s(workPhone,   sizeof(workPhone),   other.workPhone);
        strcpy_s(mobilePhone, sizeof(mobilePhone), other.mobilePhone);
        strcpy_s(extraInfo,   sizeof(extraInfo),   other.extraInfo);
    }

    ~Contact() {
        delete[] fullName;
    }

    // Геттеры
    const char* getFullName()    const { return fullName; }
    const char* getMobile()      const { return mobilePhone; }

    // Inline вывод одного контакта
    void print() const {
        std::cout << "  ФИО:      " << fullName     << std::endl;
        std::cout << "  Дом.:     " << homePhone    << std::endl;
        std::cout << "  Раб.:     " << workPhone    << std::endl;
        std::cout << "  Моб.:     " << mobilePhone  << std::endl;
        if (extraInfo[0] != '\0')
            std::cout << "  Доп.:     " << extraInfo << std::endl;
    }
};

// Класс телефонной книги — хранит вектор контактов
class PhoneBook {
private:
    std::vector<Contact*> contacts;

public:
    ~PhoneBook() {
        for (Contact* c : contacts) delete c;
    }

    // Добавить новый контакт
    void add(const char* name, const char* home, const char* work,
             const char* mobile, const char* extra = "")
    {
        contacts.push_back(new Contact(name, home, work, mobile, extra));
        std::cout << "Контакт \"" << name << "\" добавлен." << std::endl;
    }

    // Удалить контакт по ФИО (удаляет первое совпадение)
    void remove(const char* name) {
        for (auto it = contacts.begin(); it != contacts.end(); ++it) {
            if (strcmp((*it)->getFullName(), name) == 0) {
                delete *it;
                contacts.erase(it);
                std::cout << "Контакт \"" << name << "\" удалён." << std::endl;
                return;
            }
        }
        std::cout << "Контакт \"" << name << "\" не найден." << std::endl;
    }

    // Поиск по ФИО — ищет подстроку, выводит все совпадения
    void search(const char* query) const {
        std::cout << "\n--- Результаты поиска \"" << query << "\" ---" << std::endl;
        bool found = false;
        for (const Contact* c : contacts) {
            // strstr — ищет подстроку query внутри fullName
            if (strstr(c->getFullName(), query) != nullptr) {
                c->print();
                std::cout << std::endl;
                found = true;
            }
        }
        if (!found) std::cout << "Ничего не найдено." << std::endl;
    }

    // Показать всех абонентов
    void showAll() const {
        if (contacts.empty()) {
            std::cout << "Телефонная книга пуста." << std::endl;
            return;
        }
        std::cout << "\n=== Все контакты (" << contacts.size() << ") ===" << std::endl;
        for (int i = 0; i < (int)contacts.size(); i++) {
            std::cout << "#" << (i + 1) << ":" << std::endl;
            contacts[i]->print();
            std::cout << std::endl;
        }
    }
};

void task5() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    PhoneBook book;

    book.add("Иванов Иван Иванович",   "8-800-111-11-11", "8-800-222-22-22", "+7-999-111-11-11", "Друг");
    book.add("Петрова Мария Сергеевна", "8-800-333-33-33", "",                "+7-999-333-33-33");
    book.add("Сидоров Алексей Петрович","",                "8-800-444-44-44", "+7-999-444-44-44", "Коллега");

    book.showAll();

    book.search("Иванов");

    book.remove("Петрова Мария Сергеевна");

    book.showAll();
}
