#include "Date.h"
#include <ctime>
#include <sstream>
#include <string>

// Вспомогательная функция: конвертация даты в порядковый номер дня
// Используется для вычисления разницы между датами
static int toOrdinal(int d, int m, int y) {
  // Алгоритм Зеллера: считаем количество дней от условной точки отсчёта
  if (m < 3) {
    m += 12;
    y--;
  }
  return 365 * y + y / 4 - y / 100 + y / 400 + (153 * m + 8) / 5 + d;
}

Date::Date(int d, int m, int y) : day(d), month(m), year(y) {}

int Date::diffDays(const Date &other) const {
  // Разница в днях: this - other (положительное если this позже)
  return toOrdinal(day, month, year) -
         toOrdinal(other.day, other.month, other.year);
}

bool Date::isSameDay(const Date &other) const {
  return day == other.day && month == other.month && year == other.year;
}

bool Date::isInLastDays(const Date &today, int days) const {
  // Входит ли эта дата в промежуток [today - days + 1 ... today]
  int diff = today.diffDays(*this);
  return diff >= 0 && diff < days;
}

bool Date::isSameMonth(int m, int y) const { return month == m && year == y; }

void Date::print() const {
  // Вывод в формате ДД.ММ.ГГГГ с ведущими нулями
  std::cout << (day < 10 ? "0" : "") << day << "." << (month < 10 ? "0" : "")
            << month << "." << year;
}

std::string Date::toString() const {
  std::ostringstream oss;
  oss << (day < 10 ? "0" : "") << day << "." << (month < 10 ? "0" : "") << month
      << "." << year;
  return oss.str();
}

Date Date::today() {
  // Получаем системную дату через <ctime>
  time_t t = time(nullptr);
  tm local;
  localtime_s(&local, &t);
  return Date(local.tm_mday, local.tm_mon + 1, local.tm_year + 1900);
}
