#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

// Базовый класс(абстрактный класс)
// Абстрактный класс, представляющий транспортное средство
class Vehicle {
protected:
    std::string name;
    double speed;
    double tariffper;

	// Конструктор и виртуальный деструктор
public:
	Vehicle(std::string n, double s, double t) : name(n), speed(s), tariffper(t) {}
	virtual ~Vehicle() {}

	// Чистые виртуальные функции для расчета времени и стоимости
    virtual double calculateTime(double distance) const = 0;
	virtual double calculateCost(double distance, int passengers, double, double cargoWeight) const = 0;

	// Геттер для имени транспортного средства
	std::string getName() const { return name; }
};

// производный класс, наследующий от Vehicle
class Car : public Vehicle
{
public:
	// Конструктор для автомобиля, устанавливающий имя, скорость и тариф
	Car() : Vehicle("Car", 60.0, 0.5) {}

	// Расчет времени для автомобиля: время = расстояние / скорость
	double calculateTime(double distance) const override {
		return distance / speed;
	}

	// Расчет стоимости для автомобиля: топливо + пассажиры + груз
	double calculateCost(double distance, int passengers, double fuelCostPerLiter, double cargoWeight) const override {
		double fuelCost = (distance / 15.0) * fuelCostPerLiter;
		double passengerCost = passengers * 10.0;
		double cargoCost = cargoWeight * 0.5;
		return fuelCost + passengerCost + cargoCost;
	}
};

// производный класс, наследующий от Vehicle
class Bicycle : public Vehicle
{
public:
	Bicycle() : Vehicle("Bicycle", 30.0, 0.2) {}
	double calculateTime(double distance) const override {
		return distance / speed;
	}
	double calculateCost(double distance, int passengers, double fuelCostPerLiter, double cargoWeight) const override {
		if (passengers > 1 || cargoWeight > 30)
		{
			return -1.0;
		}return distance * tariffper;
	}
};

// производный класс, наследующий от Vehicle
class Cart : public Vehicle
{
public:
	Cart() : Vehicle("Cart", 20.0, 0.3) {}
	double calculateTime(double distance) const override {
		return distance / speed;
	}
	double calculateCost(double distance, int passengers, double fuelCostPerLiter, double cargoWeight) const override {
		double cargoExtra = (cargoWeight / 100.0) * 1.5;
		return distance * (tariffper + cargoExtra) + (passengers * 10.0);
	}
};

int main() {
	setlocale(LC_ALL, "Russian");
	// Полиморфизм: контейнер указателей на базовый класс
	std::vector<Vehicle*> fleet;
	fleet.push_back(new Car());
	fleet.push_back(new Bicycle());
	fleet.push_back(new Cart());

	// Входные данные для расчета
	double distance = 50.0;     // 50 км
	int passengers = 2;         // 2 пассажир
	double fuelCostPerLiter = 1.0; // 1 рубль за литр топлива
	double cargoWeight = 25.0;  // 25 кг груза

	// Вывод заголовка таблицы
	std::cout << "Маршрут: " << distance << " км. Пассажиров: " << passengers << ". Груз: " << cargoWeight << " кг.\n";
	std::cout << "---------------------------------------------------------\n";

	for (const auto& vehicle : fleet) {
		// Виртуальные функции обеспечивают вызов правильной реализации для каждого типа транспортного средства
		double time = vehicle->calculateTime(distance);
		double cost = vehicle->calculateCost(distance, passengers, fuelCostPerLiter, cargoWeight);

		// setw() - устанавливает ширину поля для вывода, fixed и setprecision() - для форматирования чисел с плавающей запятой
		std::cout << std::setw(12) << vehicle->getName() << " | ";
		std::cout << "Время: " << std::setw(5) << std::fixed << std::setprecision(2) << time << " ч. | ";

		// Если стоимость отрицательная, это означает, что перевозка невозможна 
		// (например, для велосипеда с грузом более 30 кг или более 1 пассажира)
		if (cost < 0) {
			std::cout << "Перевозка невозможна\n";
		}
		else {
			std::cout << "Стоимость: " << std::setw(7) << cost << " руб.\n";
		}
	}

	// Очистка памяти, чтобы избежать утечек памяти
	for (auto& vehicle : fleet) {
		delete vehicle;
	}

	return 0;
}