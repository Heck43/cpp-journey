#include <iostream>
#include <cstring>
#include <windows.h>

// ===== Задание 1: Класс «Человек» =====

// Вспомогательный класс для хранения даты рождения
class Date {
public:
    int day, month, year;

    Date(int d = 1, int m = 1, int y = 2000) : day(d), month(m), year(y) {}

    void print() const {
        std::cout << day << "." << month << "." << year;
    }
};

class Person {
private:
    int    id;
    char*  surname;     // фамилия — динамическая память
    char*  name;        // имя — динамическая память
    char*  patronymic;  // отчество — динамическая память
    Date   birthDate;

    // Статический счётчик — общий для всех объектов класса
    // static означает что эта переменная одна на весь класс, а не у каждого объекта своя
    static int count;

    // Вспомогательный метод: выделить память и скопировать строку
    static char* copyStr(const char* src) {
        char* dst = new char[strlen(src) + 1];
        strcpy_s(dst, strlen(src) + 1, src);
        return dst;
    }

public:
    // Конструктор с параметрами — список инициализаторов для id и birthDate
    Person(int id, const char* surname, const char* name, const char* patronymic, Date birthDate)
        : id(id), birthDate(birthDate)
    {
        // Строки копируем через вспомогательный метод
        this->surname    = copyStr(surname);
        this->name       = copyStr(name);
        this->patronymic = copyStr(patronymic);
        count++;  // увеличиваем счётчик при создании объекта
    }

    // Конструктор по умолчанию — делегирует основному
    Person() : Person(0, "Неизвестно", "Неизвестно", "Неизвестно", Date()) {}

    // Конструктор копирования — нужен потому что у нас char* (указатели)
    // Без него копия и оригинал делили бы одну и ту же память — при удалении одного крашился бы второй
    Person(const Person& other) : id(other.id), birthDate(other.birthDate) {
        surname    = copyStr(other.surname);
        name       = copyStr(other.name);
        patronymic = copyStr(other.patronymic);
        count++;
    }

    // Деструктор — освобождаем все три строки
    ~Person() {
        delete[] surname;
        delete[] name;
        delete[] patronymic;
        count--;
    }

    // Статический метод — возвращает текущий счётчик экземпляров
    static int getCount() { return count; }

    // Геттеры
    int         getId()          const { return id; }
    const char* getSurname()     const { return surname; }
    const char* getName()        const { return name; }
    const char* getPatronymic()  const { return patronymic; }
    Date        getBirthDate()   const { return birthDate; }

    // Сеттеры для строковых полей — освобождаем старую память перед записью новой
    void setSurname(const char* s) { delete[] surname; surname = copyStr(s); }
    void setName(const char* n)    { delete[] name;    name    = copyStr(n); }

    // Вывод информации о человеке
    void print() const {
        std::cout << "[ID: " << id << "] "
                  << surname << " " << name << " " << patronymic
                  << " | Дата рождения: ";
        birthDate.print();
        std::cout << std::endl;
    }
};

// Определение статического поля вне класса — обязательно для static
int Person::count = 0;

void task1() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    std::cout << "Экземпляров Person: " << Person::getCount() << std::endl;

    Person p1(1, "Иванов", "Иван", "Иванович", Date(15, 6, 1990));
    Person p2(2, "Петрова", "Мария", "Сергеевна", Date(3, 11, 1995));
    std::cout << "Экземпляров Person: " << Person::getCount() << std::endl;

    p1.print();
    p2.print();

    // Конструктор копирования
    Person p3(p1);
    p3.setSurname("Сидоров");
    std::cout << "\nОригинал: "; p1.print();
    std::cout << "Копия:    "; p3.print();

    std::cout << "Экземпляров Person: " << Person::getCount() << std::endl;
}
