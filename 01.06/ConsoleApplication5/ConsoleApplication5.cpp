#include <iostream>
#include <string>
#include <vector>

// Базовый класс домашнего животного
class Pet {
protected:
	std::string name;

public:
	Pet(std::string name) : name(name) {}
	virtual ~Pet() {}

	// Издает звук животного (чистая виртуальная — каждый класс реализует по-своему)
	virtual void Sound() const = 0;

	// Отображает имя животного
	virtual void Show() const {
		std::cout << "Имя: " << name << std::endl;
	}

	// Отображает название подвида (чистая виртуальная)
	virtual void Type() const = 0;
};

// Производный класс Собака
class Dog : public Pet {
public:
	Dog(std::string name) : Pet(name) {}

	// Собака лает
	void Sound() const override {
		std::cout << "Гав-гав!" << std::endl;
	}

	void Type() const override {
		std::cout << "Вид: Собака" << std::endl;
	}
};

// Производный класс Кошка
class Cat : public Pet {
public:
	Cat(std::string name) : Pet(name) {}

	// Кошка мяукает
	void Sound() const override {
		std::cout << "Мяу-мяу!" << std::endl;
	}

	void Type() const override {
		std::cout << "Вид: Кошка" << std::endl;
	}
};

// Производный класс Попугай
class Parrot : public Pet {
public:
	Parrot(std::string name) : Pet(name) {}

	// Попугай говорит
	void Sound() const override {
		std::cout << "Кра-кра! Попка дурак!" << std::endl;
	}

	void Type() const override {
		std::cout << "Вид: Попугай" << std::endl;
	}
};

// Производный класс Хомяк
class Hamster : public Pet {
public:
	Hamster(std::string name) : Pet(name) {}

	// Хомяк пищит
	void Sound() const override {
		std::cout << "Пи-пи-пи!" << std::endl;
	}

	void Type() const override {
		std::cout << "Вид: Хомяк" << std::endl;
	}
};

int main() {
	setlocale(LC_ALL, "Russian");

	// Полиморфизм: контейнер указателей на базовый класс
	std::vector<Pet*> pets;
	pets.push_back(new Dog("Шарик"));
	pets.push_back(new Cat("Мурка"));
	pets.push_back(new Parrot("Кеша"));
	pets.push_back(new Hamster("Пушок"));

	std::cout << "=== Домашние животные ===" << std::endl;
	std::cout << "-------------------------" << std::endl;

	// Вызов виртуальных методов через указатели на базовый класс
	for (const auto& pet : pets) {
		pet->Type();
		pet->Show();
		std::cout << "Звук: ";
		pet->Sound();
		std::cout << "-------------------------" << std::endl;
	}

	// Очистка памяти, чтобы избежать утечек
	for (auto& pet : pets) {
		delete pet;
	}

	return 0;
}
