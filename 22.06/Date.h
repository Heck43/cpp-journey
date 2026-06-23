#pragma once
#include <iostream>

// Вспомогательный класс для хранения и сравнения дат

class Date {
public:
    int day, month, year;

    Date(int d = 1, int m = 1, int y = 2024);

    // Разница в днях (this - other), нужна для фильтрации по неделе
    int diffDays(const Date& other) const;

    bool isSameDay(const Date& other) const;
    bool isInLastDays(const Date& today, int days) const; // входит ли в последние N дней
    bool isSameMonth(int m, int y) const;

    void print() const;
    std::string toString() const;

    // Получить текущую дату через системные часы
    static Date today();
};
