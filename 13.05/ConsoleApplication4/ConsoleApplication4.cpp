#include <cmath> // Для M_PI и sqrt
#include <iostream>
#include <vector>
// windows.h не подключаем — там Rectangle объявлен как WinGDI-функция,
// что конфликтует с нашим классом Rectangle. SetConsoleOutputCP уже вызван в
// main.cpp

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// ===== Задание 2.1: Иерархия геометрических фигур =====

class Shape {
protected:
  static int count; // счётчик всех фигур

public:
  Shape() { count++; }
  virtual ~Shape() { count--; }

  // Чистые виртуальные методы — Shape нельзя создать напрямую
  virtual double area() const = 0;
  virtual double perimeter() const = 0;
  virtual void print() const = 0;

  static int getCount() { return count; }
};

int Shape::count = 0;

// --------- Круг ---------
class Circle : public Shape {
private:
  double radius;

public:
  Circle(double r) : radius(r) {}

  double area() const override { return M_PI * radius * radius; }
  double perimeter() const override { return 2 * M_PI * radius; }
  void print() const override {
    std::cout << "Круг (r=" << radius << "): "
              << "площадь=" << area() << ", периметр=" << perimeter()
              << std::endl;
  }
};

// --------- Прямоугольник ---------
class Rectangle : public Shape {
private:
  double width, height;

public:
  Rectangle(double w, double h) : width(w), height(h) {}

  double area() const override { return width * height; }
  double perimeter() const override { return 2 * (width + height); }
  void print() const override {
    std::cout << "Прямоугольник (" << width << "x" << height << "): "
              << "площадь=" << area() << ", периметр=" << perimeter()
              << std::endl;
  }
};

// --------- Треугольник ---------
class Triangle : public Shape {
private:
  double a, b, c; // три стороны
public:
  Triangle(double a, double b, double c) : a(a), b(b), c(c) {}

  double perimeter() const override { return a + b + c; }

  // Формула Герона: S = sqrt(s*(s-a)*(s-b)*(s-c)), где s = периметр/2
  double area() const override {
    double s = perimeter() / 2.0;
    return std::sqrt(s * (s - a) * (s - b) * (s - c));
  }

  void print() const override {
    std::cout << "Треугольник (a=" << a << ", b=" << b << ", c=" << c << "): "
              << "площадь=" << area() << ", периметр=" << perimeter()
              << std::endl;
  }
};

void task4() {

  std::cout << "Фигур: " << Shape::getCount() << std::endl;

  // Массив указателей на базовый класс — полиморфизм
  std::vector<Shape *> shapes = {new Circle(5), new Rectangle(3, 4),
                                 new Triangle(3, 4, 5)};

  std::cout << "Фигур: " << Shape::getCount() << std::endl;

  for (const Shape *s : shapes) {
    s->print(); // вызывается нужный метод благодаря virtual
  }

  // Находим фигуру с максимальной площадью
  const Shape *maxShape = shapes[0];
  for (const Shape *s : shapes)
    if (s->area() > maxShape->area())
      maxShape = s;

  std::cout << "\nФигура с макс. площадью: ";
  maxShape->print();

  for (Shape *s : shapes)
    delete s;
  std::cout << "Фигур после удаления: " << Shape::getCount() << std::endl;
}
