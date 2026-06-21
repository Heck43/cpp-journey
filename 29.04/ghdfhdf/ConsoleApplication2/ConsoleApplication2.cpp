#include <iostream>
#include <windows.h>

// Задача 2: «Лампочка с выключателем»
// Демонстрируем инкапсуляцию — поле isOn скрыто, снаружи его не видно
// Управлять лампочкой можно только через публичные методы

class LightBulb {
private:
  // Скрытое поле — хранит текущее состояние лампочки
  // false = выключена, true = включена
  bool isOn;

public:
  // Конструктор — при создании лампочка выключена по умолчанию
  LightBulb() : isOn(false) {}

  // Мутатор: включает лампочку (устанавливает isOn в true)
  void turnOn() { isOn = true; }

  // Мутатор: выключает лампочку (устанавливает isOn в false)
  void turnOff() { isOn = false; }

  // Мутатор: переключает состояние на противоположное
  // Если была включена — выключит, если выключена — включит
  void toggle() { isOn = !isOn; }

  // Аксессор: возвращает текущее состояние в виде строки
  // const — метод не изменяет объект, только читает
  const char *getState() const {
    if (isOn) {
      return "ON";
    }
    return "OFF";
  }
};

void task2() {

    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

  LightBulb bulb; // Создаём лампочку — по умолчанию выключена

  std::cout << "Начальное состояние: " << bulb.getState() << std::endl;

  bulb.turnOn(); // Включаем
  std::cout << "После turnOn():  " << bulb.getState() << std::endl;

  bulb.toggle(); // Переключаем — станет выключена
  std::cout << "После toggle():  " << bulb.getState() << std::endl;

  bulb.toggle(); // Переключаем ещё раз — снова включена
  std::cout << "После toggle():  " << bulb.getState() << std::endl;

  bulb.turnOff(); // Выключаем
  std::cout << "После turnOff(): " << bulb.getState() << std::endl;
}
