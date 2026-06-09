#include <iostream>
#include <string>
#include <vector>
#include <limits>

// Абстрактный базовый класс служащего с чисто виртуальной функцией Print()
class Employer {
protected:
	std::string name;

public:
	Employer(std::string name) : name(name) {}
	virtual ~Employer() {}

	// Чистая виртуальная функция — каждый тип служащего выводит свою информацию
	virtual void Print() const = 0;

	std::string getName() const { return name; }
};

// Производный класс Президент
class President : public Employer {
private:
	std::string company;
	double salary;

public:
	President(std::string name, std::string company, double salary)
		: Employer(name), company(company), salary(salary) {}

	// Переопределяем вывод информации для президента
	void Print() const override {
		std::cout << "[Президент]" << std::endl;
		std::cout << "  Имя: " << name << std::endl;
		std::cout << "  Компания: " << company << std::endl;
		std::cout << "  Зарплата: " << salary << " руб." << std::endl;
	}
};

// Производный класс Менеджер
class Manager : public Employer {
private:
	std::string department;
	double salary;
	int teamSize;

public:
	Manager(std::string name, std::string department, double salary, int teamSize)
		: Employer(name), department(department), salary(salary), teamSize(teamSize) {}

	// Переопределяем вывод информации для менеджера
	void Print() const override {
		std::cout << "[Менеджер]" << std::endl;
		std::cout << "  Имя: " << name << std::endl;
		std::cout << "  Отдел: " << department << std::endl;
		std::cout << "  Зарплата: " << salary << " руб." << std::endl;
		std::cout << "  Размер команды: " << teamSize << " чел." << std::endl;
	}
};

// Производный класс Рабочий
class Worker : public Employer {
private:
	std::string position;
	double salary;
	int experience;

public:
	Worker(std::string name, std::string position, double salary, int experience)
		: Employer(name), position(position), salary(salary), experience(experience) {}

	// Переопределяем вывод информации для рабочего
	void Print() const override {
		std::cout << "[Рабочий]" << std::endl;
		std::cout << "  Имя: " << name << std::endl;
		std::cout << "  Должность: " << position << std::endl;
		std::cout << "  Зарплата: " << salary << " руб." << std::endl;
		std::cout << "  Стаж: " << experience << " лет" << std::endl;
	}
};

int main() {
	setlocale(LC_ALL, "Russian");

	// Список всех служащих через указатели на базовый класс
	std::vector<Employer*> staff;
	staff.push_back(new President("Иванов Иван", "ООО Рога и Копыта", 500000));
	staff.push_back(new Manager("Петров Пётр", "Отдел разработки", 150000, 8));
	staff.push_back(new Manager("Сидорова Анна", "Отдел маркетинга", 120000, 5));
	staff.push_back(new Worker("Козлов Алексей", "Программист", 80000, 3));
	staff.push_back(new Worker("Новикова Мария", "Тестировщик", 70000, 2));

	int choice;
	do {
		std::cout << "\n========== Меню ==========\n";
		std::cout << "1. Показать всех служащих\n";
		std::cout << "2. Показать только президентов\n";
		std::cout << "3. Показать только менеджеров\n";
		std::cout << "4. Показать только рабочих\n";
		std::cout << "0. Выход\n";
		std::cout << "> ";
		std::cin >> choice;

		// Защита от некорректного ввода
		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Некорректный ввод!\n";
			continue;
		}

		std::cout << "\n--------------------------\n";

		switch (choice) {
		case 1:
			// Полиморфизм: вызываем Print() через указатель на базовый класс
			for (const auto& emp : staff) {
				emp->Print();
				std::cout << "--------------------------\n";
			}
			break;
		case 2:
			// Фильтруем по типу через dynamic_cast
			for (const auto& emp : staff) {
				if (dynamic_cast<President*>(emp)) {
					emp->Print();
					std::cout << "--------------------------\n";
				}
			}
			break;
		case 3:
			for (const auto& emp : staff) {
				if (dynamic_cast<Manager*>(emp)) {
					emp->Print();
					std::cout << "--------------------------\n";
				}
			}
			break;
		case 4:
			for (const auto& emp : staff) {
				if (dynamic_cast<Worker*>(emp)) {
					emp->Print();
					std::cout << "--------------------------\n";
				}
			}
			break;
		case 0:
			std::cout << "Выход...\n";
			break;
		default:
			std::cout << "Нет такого пункта меню!\n";
			break;
		}
	} while (choice != 0);

	// Очистка памяти, чтобы избежать утечек
	for (auto& emp : staff) {
		delete emp;
	}

	return 0;
}
