#include "Account.h"
#include "FinanceManager.h"
#include <iostream>
#include <string>
#include <windows.h>

// ===== Вспомогательные функции для меню =====

// Прочитать целое число с валидацией
static int readInt(const std::string &prompt) {
  int val;
  while (true) {
    std::cout << prompt;
    if (std::cin >> val) {
      std::cin.ignore();
      return val;
    }
    std::cin.clear();
    while (std::cin.get() != '\n')
      ;
    std::cout << "Введи число -w-\n";
  }
}

// Прочитать вещественное число с валидацией
static double readDouble(const std::string &prompt) {
  double val;
  while (true) {
    std::cout << prompt;
    if (std::cin >> val && val > 0) {
      std::cin.ignore();
      return val;
    }
    std::cin.clear();
    while (std::cin.get() != '\n')
      ;
    std::cout << "Введи положительное число -w-\n";
  }
}

// Прочитать строку
static std::string readLine(const std::string &prompt) {
  std::cout << prompt;
  std::string s;
  std::getline(std::cin, s);
  return s;
}

// Прочитать дату
static Date readDate() {
  int d = readInt("  День (1-31): ");
  int m = readInt("  Месяц (1-12): ");
  int y = readInt("  Год (например, 2026): ");
  return Date(d, m, y);
}

// Выбрать счёт из списка по номеру — надёжнее чем вводить имя вручную
static Account *chooseAccount(FinanceManager &fm) {
  if (fm.getAccountCount() == 0) {
    std::cout << "Счетов нет.\n";
    return nullptr;
  }
  fm.showAccounts();
  std::cout << "\nВыбери номер счёта (1-" << fm.getAccountCount() << "): ";
  int idx = readInt("") - 1; // переводим в 0-based индекс
  Account *acc = fm.getAccountByIndex(idx);
  if (!acc) {
    std::cout << "Неверный номер.\n";
  }
  return acc;
}

// Меню категорий
static std::string chooseCategory() {
  std::cout << "\nКатегории:\n"
            << "1. Еда\n2. Транспорт\n3. Жильё\n4. Развлечения\n"
            << "5. Здоровье\n6. Одежда\n7. Связь\n8. Другое\n";
  int c = readInt("Выбери категорию: ");
  switch (c) {
  case 1:
    return "Еда";
  case 2:
    return "Транспорт";
  case 3:
    return "Жильё";
  case 4:
    return "Развлечения";
  case 5:
    return "Здоровье";
  case 6:
    return "Одежда";
  case 7:
    return "Связь";
  default:
    return "Другое";
  }
}

// ===== main =====

int main() {
  SetConsoleOutputCP(65001);
  SetConsoleCP(65001);

  FinanceManager fm;

  // Демонстрационные данные — чтобы сразу было что смотреть
  fm.addAccount(new Wallet("Наличные", 5000));
  fm.addAccount(new DebitCard("Сбербанк", 30000));
  fm.addAccount(new CreditCard("Тинькофф", 50000, 10000));

  Date today = Date::today();
  fm.addExpense("Наличные", 450, "Еда", "Обед", today);
  fm.addExpense("Сбербанк", 1200, "Транспорт", "Такси", today);
  fm.addExpense("Сбербанк", 3500, "Развлечения", "Кино + кафе",
                Date(today.day - 2, today.month, today.year));
  fm.addExpense("Тинькофф", 8900, "Одежда", "Кроссовки",
                Date(today.day - 5, today.month, today.year));
  fm.addExpense("Наличные", 280, "Еда", "Кофе",
                Date(today.day - 1, today.month, today.year));
  fm.addExpense("Сбербанк", 600, "Связь", "Интернет",
                Date(today.day - 3, today.month, today.year));

  int choice = 0;
  while (true) {
    std::cout << "\n====== Финансы ======\n"
              << "1. Показать счета\n"
              << "2. Добавить счёт\n"
              << "3. Пополнить счёт\n"
              << "4. Добавить затрату\n"
              << "5. Отчёт за день\n"
              << "6. Отчёт за неделю\n"
              << "7. Отчёт за месяц\n"
              << "8. ТОП-3 за неделю\n"
              << "9. ТОП-3 за месяц\n"
              << "10. Сохранить отчёт в файл\n"
              << "0. Выход\n"
              << "Выбор: ";

    if (!(std::cin >> choice)) {
      std::cin.clear();
      while (std::cin.get() != '\n')
        ;
      continue;
    }
    std::cin.ignore();

    if (choice == 0) {
      std::cout << "пока-пока!\n";
      break;
    }

    switch (choice) {

    case 1:
      fm.showAccounts();
      break;

    case 2: {
      std::cout << "Тип: 1. Кошелёк  2. Дебетовая  3. Кредитная\n";
      int type = readInt("Выбор: ");
      std::string name = readLine("Название: ");
      double bal = readDouble("Начальный баланс: ");
      if (type == 1)
        fm.addAccount(new Wallet(name, bal));
      else if (type == 2)
        fm.addAccount(new DebitCard(name, bal));
      else {
        double lim = readDouble("Кредитный лимит: ");
        fm.addAccount(new CreditCard(name, lim, bal));
      }
      break;
    }

    case 3: {
      // выбираем кошелёчек по номеру
      Account *acc = chooseAccount(fm);
      if (acc) {
        double amount = readDouble("Сумма пополнения: ");
        fm.topUp(acc->getName(), amount);
      }
      break;
    }

    case 4: {
      // тут добавляем затрату аккуратно
      Account *acc = chooseAccount(fm);
      if (acc) {
        double amount = readDouble("Сумма затраты: ");
        std::string cat = chooseCategory();
        std::string desc = readLine("Описание (Enter чтобы пропустить): ");
        std::cout << "Дата затраты (Enter = сегодня, или введи вручную):\n";
        int useDateChoice = readInt("1 = сегодня, 2 = ввести дату: ");
        Date d = (useDateChoice == 1) ? Date::today() : readDate();
        fm.addExpense(acc->getName(), amount, cat, desc, d);
      }
      break;
    }

    case 5: {
      std::cout << "Дата:\n";
      Date d = readDate();
      fm.reportByDay(d);
      break;
    }

    case 6:
      fm.reportByWeek(Date::today());
      break;

    case 7: {
      int m = readInt("Месяц (1-12): ");
      int y = readInt("Год: ");
      fm.reportByMonth(m, y);
      break;
    }

    case 8:
      fm.ratingsWeek(Date::today());
      break;

    case 9: {
      int m = readInt("Месяц (1-12): ");
      int y = readInt("Год: ");
      fm.ratingsMonth(m, y);
      break;
    }

    case 10: {
      std::cout << "1. Отчёт за день\n2. Отчёт за неделю\n3. Отчёт за месяц\n";
      int t = readInt("Выбор: ");
      if (t == 1) {
        Date d = readDate();
        fm.saveReportByDay(d);
      } else if (t == 2)
        fm.saveReportByWeek(Date::today());
      else {
        int m = readInt("Месяц: ");
        int y = readInt("Год: ");
        fm.saveReportByMonth(m, y);
      }
      break;
    }

    default:
      std::cout << "Нет такого пункта.\n";
    }
  }
  return 0;
}
