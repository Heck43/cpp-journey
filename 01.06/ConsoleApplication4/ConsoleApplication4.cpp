#include <iostream>

// Базовый класс для колес, который будет наследоваться от класса Car
class Wheels
{
protected:
	int WheelsCount;
	int WheelsSize;

public:
	Wheels(int count, int size) : WheelsCount(count), WheelsSize(size) {}
	virtual ~Wheels() {}

	void display() const {
		std::cout << "Штук: " << WheelsCount << ", Размер: " << WheelsSize << std::endl;
	}
};

// класс для двигателя, который будет наследоваться от базового класса Engine
class Engine
{
protected:
	int horsePower;
	std::string fuelType;

public:
	Engine(int hp, std::string f) : horsePower(hp), fuelType(f) {}
	virtual ~Engine() {}

	void display() const {
		std::cout << "Мощность: " << horsePower << " л.с., Тип топлива: " << fuelType << std::endl;
	}
};

// класс для дверей, который будет наследоваться от базового класса Door
class Door
{
	protected:
	int DoorCount;

public:
	Door(int count) : DoorCount(count) {}
	virtual ~Door() {}

	void display() const {
		std::cout << "Количество дверей: " << DoorCount << std::endl;
	}
};

// самое интересное - класс автомобиля, который наследует от всех трех базовых классов
// Это пример множественного наследования, где класс Car наследует свойства и методы от Wheels, Engine и Door
class Car : public Wheels, public Engine, public Door
{
private:
	std::string model;
	std::string brand;

public:
	// Конструктор для класса Car, который инициализирует все базовые классы и свои собственные члены
	Car(std::string m, std::string b, int wc, int ws, int hp, std::string ft, int dc)
		: Wheels(wc, ws), Engine(hp, ft), Door(dc), model(m), brand(b) {
	}
	// Метод для отображения информации об автомобиле, который вызывает методы display всех базовых классов
	void display() const {
		std::cout << "Марка: " << brand << ", Модель: " << model << std::endl;
		Wheels::display();
		Engine::display();
		Door::display();
	}
};


int main() {
	setlocale(LC_ALL, "Russian");
	// Создаем объект автомобиля через множественное наследование
	Car myCar("Toyota", "Camry", 4, 17, 181.0, "Бензин", 4);

	// Выводим его характеристики, выводим уже все, так как в классе Car есть метод display, который вызывает методы display всех базовых классов
	std::cout << "======вывод автомобиля======" << std::endl; // вывод через класс Car, который наследует от всех базовых классов и вызывает их методы display
	myCar.display();
	std::cout << "======вывод отдельное компонента======" << std::endl;			// вывод через класс Car, который наследует от всех базовых классов 
	myCar.Engine::display(); // Выводим характеристики колес					// и вызывает их методы display отдельно для каждого компонента
	myCar.Wheels::display(); // Выводим характеристики двигателя

	return 0;
}