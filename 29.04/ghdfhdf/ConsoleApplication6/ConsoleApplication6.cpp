
#include <iostream>

// Задача 6: «Прямоугольник»
// Inline-методы пишем прямо в теле класса — компилятор вставляет их код на месте вызова
// const после метода — гарантия что метод не меняет поля объекта (инспектор)

class Rectangle {
private:
    double width;   // ширина
    double height;  // высота

public:
    // Конструктор с проверкой — отрицательные и нулевые размеры не допускаются
    Rectangle(double w, double h) {
        width  = (w > 0) ? w : 1.0;
        height = (h > 0) ? h : 1.0;
    }

    // Inline-методы: реализованы прямо в теле класса
    // const — эти методы только читают поля, не изменяют их

    double getWidth()     const { return width; }
    double getHeight()    const { return height; }
    double getArea()      const { return width * height; }
    double getPerimeter() const { return 2 * (width + height); }
    bool   isSquare()     const { return width == height; }

    // printInfo тоже const — только выводит данные, ничего не меняет
    void printInfo() const {
        std::cout << "Rectangle: " << width << " x " << height << std::endl;
        std::cout << "Square: "       << getArea()      << std::endl;
        std::cout << "Perimeter: "      << getPerimeter() << std::endl;
        std::cout << "Is a square: " << (isSquare() ? "yes" : "no") << std::endl;
    }
};

void task6() {

    Rectangle rect(5.0, 3.0);
    std::cout << "--- Rectangle ---" << std::endl;
    rect.printInfo();

    std::cout << std::endl;

    Rectangle square(4.0, 4.0);
    std::cout << "--- Square ---" << std::endl;
    square.printInfo();

}
