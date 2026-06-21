#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>  // Для std::sort
#include <windows.h>

// ===== Задание 2.2: Иерархия сотрудников + класс Department =====

class Employee {
protected:
    char*  name;
    int    id;
    double baseSalary;

    static char* copyStr(const char* src) {
        char* dst = new char[strlen(src) + 1];
        strcpy_s(dst, strlen(src) + 1, src);
        return dst;
    }

public:
    Employee(const char* name, int id, double baseSalary)
        : id(id), baseSalary(baseSalary)
    {
        this->name = copyStr(name);
    }

    // Конструктор копирования — имя в куче, нужна глубокая копия
    Employee(const Employee& o) : id(o.id), baseSalary(o.baseSalary) {
        name = copyStr(o.name);
    }

    virtual ~Employee() { delete[] name; }

    // Виртуальные методы — переопределяются в каждом наследнике
    virtual double calculateSalary() const { return baseSalary; }

    virtual void getInfo() const {
        std::cout << "[ID:" << id << "] " << name
                  << " | Зарплата: " << calculateSalary() << " руб.";
    }

    // Геттеры для использования в Department
    const char* getName()   const { return name; }
    int         getId()     const { return id; }
    double      getSalary() const { return calculateSalary(); }
};

// --------- Менеджер ---------
// Зарплата = базовая + бонус * 100 за каждого подчинённого
class Manager : public Employee {
private:
    double bonusPercent;    // бонус в процентах
    int    subordinates;    // количество подчинённых
public:
    Manager(const char* name, int id, double base, double bonus, int subs)
        : Employee(name, id, base), bonusPercent(bonus), subordinates(subs) {}

    double calculateSalary() const override {
        return baseSalary + bonusPercent * 100 * subordinates;
    }

    void getInfo() const override {
        Employee::getInfo();
        std::cout << " [Менеджер, подчинённых: " << subordinates
                  << ", бонус: " << bonusPercent << "%]" << std::endl;
    }
};

// --------- Разработчик ---------
// Зарплата = базовая + опыт * 5000
class Developer : public Employee {
private:
    char* language;   // язык программирования — в куче
    int   experience; // опыт в годах
public:
    Developer(const char* name, int id, double base, const char* lang, int exp)
        : Employee(name, id, base), experience(exp)
    {
        language = copyStr(lang);
    }

    Developer(const Developer& o) : Employee(o), experience(o.experience) {
        language = copyStr(o.language);
    }

    ~Developer() override { delete[] language; }

    double calculateSalary() const override {
        return baseSalary + experience * 5000;
    }

    void getInfo() const override {
        Employee::getInfo();
        std::cout << " [Разработчик, " << language
                  << ", опыт: " << experience << " лет]" << std::endl;
    }
};

// --------- Стажёр ---------
// Зарплата = 70% от базовой
class Intern : public Employee {
private:
    bool hasMentor;  // есть ли наставник
public:
    Intern(const char* name, int id, double base, bool mentor)
        : Employee(name, id, base), hasMentor(mentor) {}

    double calculateSalary() const override {
        return baseSalary * 0.70;
    }

    void getInfo() const override {
        Employee::getInfo();
        std::cout << " [Стажёр, наставник: "
                  << (hasMentor ? "есть" : "нет") << "]" << std::endl;
    }
};

// --------- Отдел ---------
class Department {
private:
    std::vector<Employee*> employees;

public:
    ~Department() {
        for (Employee* e : employees) delete e;
    }

    void add(Employee* e) {
        employees.push_back(e);
        std::cout << "Добавлен: " << e->getName() << std::endl;
    }

    void remove(int id) {
        for (auto it = employees.begin(); it != employees.end(); ++it) {
            if ((*it)->getId() == id) {
                std::cout << "Удалён: " << (*it)->getName() << std::endl;
                delete *it;
                employees.erase(it);
                return;
            }
        }
        std::cout << "Сотрудник ID=" << id << " не найден." << std::endl;
    }

    // Общая зарплата всех сотрудников
    double totalSalary() const {
        double total = 0;
        for (const Employee* e : employees) total += e->getSalary();
        return total;
    }

    // Сотрудник с максимальной зарплатой
    const Employee* maxSalaryEmployee() const {
        if (employees.empty()) return nullptr;
        const Employee* best = employees[0];
        for (const Employee* e : employees)
            if (e->getSalary() > best->getSalary()) best = e;
        return best;
    }

    // Сортировка по зарплате (по возрастанию)
    void sortBySalary() {
        std::sort(employees.begin(), employees.end(),
            [](const Employee* a, const Employee* b) {
                return a->getSalary() < b->getSalary();
            });
    }

    void showAll() const {
        std::cout << "\n=== Сотрудники отдела (" << employees.size() << ") ===" << std::endl;
        for (const Employee* e : employees) e->getInfo();
    }
};

void task5() {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    Department dept;

    dept.add(new Manager  ("Иванов Иван",   1, 80000, 15, 5));
    dept.add(new Developer("Петров Алексей", 2, 70000, "C++", 4));
    dept.add(new Developer("Сидорова Мария", 3, 70000, "Python", 2));
    dept.add(new Intern   ("Козлов Дмитрий", 4, 40000, true));

    dept.showAll();

    std::cout << "\nОбщая зарплата: " << dept.totalSalary() << " руб." << std::endl;

    const Employee* best = dept.maxSalaryEmployee();
    std::cout << "Макс. зарплата у: " << best->getName()
              << " (" << best->getSalary() << " руб.)" << std::endl;

    dept.sortBySalary();
    std::cout << "\nПосле сортировки по зарплате:";
    dept.showAll();

    dept.remove(4);
    dept.showAll();
}
