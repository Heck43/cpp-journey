#include <iostream>  // Для ввода-вывода в консоль (std::cin, std::cout)
#include <fstream>   // Для работы с файлами (std::ifstream, std::ofstream)
#include <vector>    // Для использования динамического массива (std::vector)
#include <string>    // Для работы с текстовыми строками (std::string)
#include <limits>    // Для очистки буфера ввода (std::numeric_limits)

// Класс "Book" — шаблон (модель) для создания объектов-книг
class Book
{
public:
	// Конструктор с параметрами по умолчанию (позволяет создавать как пустую книгу, так и с данными)
	// Инициализация полей выполнена через список инициализации : title{title}, author{author}
	Book(std::string title = "", std::string author = "") : title{ title }, author{ author } {}

	// Геттеры (Getters) — методы для безопасного получения значений приватных полей
	// Пометка const означает, что методы не изменяют состояние объекта
	std::string getTitle() const { return title; }
	std::string getAuthor() const { return author; }

	// Сеттеры (Setters) — методы для безопасного изменения значений приватных полей
	void setTitle(std::string t) { title = t; }
	void setAuthor(std::string a) { author = a; }

private:
	// Скрытые свойства (поля) класса — инкапсуляция данных
	std::string title;  // Название книги
	std::string author; // Автор книги
};

// Перегрузка оператора вывода <<
// Определяет, как объект Book будет записываться в поток вывода (в консоль или в файл)
std::ostream& operator<<(std::ostream& os, const Book& book)
{
	// Записывает данные в формате: Название|Автор и переводит строку
	return os << book.getTitle() << "|" << book.getAuthor() << std::endl;
}

// Перегрузка оператора ввода >>
// Определяет, как объект Book будет считываться из потока (например, из файла)
std::istream& operator>>(std::istream& in, Book& book) {
	std::string title, author;

	// Читаем название книги до тех пор, пока не встретим разделитель '|'
	std::getline(in, title, '|');
	// Читаем автора книги до конца текущей строки
	std::getline(in, author);

	// Очистка от скрытого символа '\r' (возврат каретки), который появляется при чтении файлов в Windows
	if (!author.empty() && author.back() == '\r') {
		author.pop_back(); // Удаляем последний символ, если это '\r'
	}

	// Если чтение прошло успешно (поток в порядке), записываем данные в объект книги
	if (in)
	{
		book.setTitle(title);
		book.setAuthor(author);
	}
	return in; // Возвращаем поток для цепочки вызовов
}

// Функция сохранения каталога в текстовый файл
void saveFromFile(std::vector<Book>& catalog, const std::string& filename)
{
	std::ofstream out(filename); // Открываем поток для записи в файл
	if (out.is_open()) // Проверяем, удалось ли успешно открыть файл
	{
		// Перебираем все книги в каталоге по константной ссылке (без копирования)
		for (const Book& book : catalog)
		{
			out << book; // Записываем книгу в файл, используя наш перегруженный оператор <<
		}
		out.close(); // Закрываем файл после записи
		std::cout << "Данные успешно сохранены в файл " << filename << std::endl;
	}
	else {
		std::cout << "Ошибка: не удалось открыть файл для записи!" << std::endl;
	}
}

// Функция загрузки каталога из текстового файла
void loadFromFile(std::vector<Book>& catalog, const std::string& filename)
{
	std::ifstream in(filename); // Открываем поток для чтения из файла
	if (in.is_open()) // Проверяем, существует ли файл и открылся ли он
	{
		catalog.clear(); // Полностью очищаем старый каталог в оперативной памяти
		Book book;

		// Цикл работает, пока оператор >> успешно считывает очередную книгу из файла
		while (in >> book)
		{
			// Проверяем, что считанная книга не полностью пустая
			if (!book.getTitle().empty() || !book.getAuthor().empty())
			{
				catalog.push_back(book); // Добавляем считанную книгу в конец вектора
			}
		}
		in.close(); // Закрываем файл после чтения
		std::cout << "Данные успешно загружены из файла " << filename << std::endl;
	}
	else
	{
		std::cout << "Файл не найден или не может быть открыт для чтения." << std::endl;
	}
}

// Главная управляющая функция программы
int main() {
	setlocale(LC_ALL, "Russian"); // Включаем поддержку русского языка в консоли
	std::vector<Book> catalog;    // Наш динамический массив (база данных) для хранения книг
	std::string filename = "books.txt"; // Имя файла для хранения данных

	// Пытаемся автоматически загрузить сохраненные данные при самом старте программы
	loadFromFile(catalog, filename);

	int choice; // Переменная для хранения выбора пользователя в меню
	do {
		// Выводим текстовое меню в консоль
		std::cout << "\n=== Каталог библиотеки ===\n";
		std::cout << "1. Добавить новую книгу\n";
		std::cout << "2. Просмотреть список всех книг\n";
		std::cout << "3. Искать книгу по названию или автору\n";
		std::cout << "4. Сохранить данные в файл\n";
		std::cout << "5. Загрузить данные из файла\n";
		std::cout << "0. Выход\n";
		std::cout << "Выберите действие: ";

		std::cin >> choice; // Считываем цифру нажатого пункта меню

		// ВАЖНО: Очищаем буфер ввода. После ввода числа там остается символ '\n' (Enter).
		// Если его не проигнорировать, следующий std::getline прочитает пустую строку.
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		// Конструкция switch выполняет блок кода в зависимости от значения переменной choice
		switch (choice) {
		case 1: { // Добавление новой книги
			std::string title, author;
			std::cout << "Введите название книги: ";
			std::getline(std::cin, title); // Читаем всю строку с пробелами
			std::cout << "Введите автора книги: ";
			std::getline(std::cin, author); // Читаем всю строку с пробелами

			Book newBook(title, author); // Создаем объект новой книги
			catalog.push_back(newBook);   // Добавляем созданный объект в вектор
			std::cout << "Книга успешно добавлена!\n";
			break; // Выход из текущего кейса switch
		}
		case 2: { // Вывод списка всех книг
			std::cout << "\n--- Список всех книг ---\n";
			if (catalog.empty()) { // Проверка: если в векторе 0 элементов
				std::cout << "Каталог пуст.\n";
			}
			else {
				// Итерируемся по всему вектору книг
				for (const Book& book : catalog) {
					std::cout << book << std::endl; // Печатаем книгу через перегруженный <<
				}
			}
			break;
		}
		case 3: { // Поиск книги
			std::string query;
			std::cout << "Введите название или автора для поиска: ";
			std::getline(std::cin, query); // Считываем поисковый запрос

			bool found = false; // Флаг, определяющий, нашли ли мы хоть что-то
			std::cout << "\n--- Результаты поиска ---\n";

			for (const Book& book : catalog) {
				// Метод find() ищет подстроку query внутри названия или автора.
				// Если подстрока НЕ найдена, метод возвращает специальную константу std::string::npos.
				if (book.getTitle().find(query) != std::string::npos ||
					book.getAuthor().find(query) != std::string::npos) {
					std::cout << book << std::endl; // Если совпадение есть — выводим книгу
					found = true; // Отмечаем, что совпадение найдено
				}
			}
			if (!found) { // Если после проверки всех книг флаг остался false
				std::cout << "Книги по вашему запросу не найдены.\n";
			}
			break;
		}
		case 4: { // Принудительное сохранение в файл
			saveFromFile(catalog, filename);
			break;
		}
		case 5: { // Принудительная загрузка из файла
			loadFromFile(catalog, filename);
			break;
		}
		case 0: { // Выход из программы
			std::cout << "Выход из программы. До свидания!\n";
			break;
		}
		default: { // Если пользователь ввел цифру, которой нет в switch (например, 7 или -1)
			std::cout << "Неверный выбор. Попробуйте снова.\n";
		}
		}
	} while (choice != 0); // Цикл повторяется, пока choice не станет равен 0

	return 0; // Успешное завершение работы программы
}
