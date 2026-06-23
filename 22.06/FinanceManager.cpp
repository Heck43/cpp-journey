#include "FinanceManager.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <map>
#include <iomanip>

// ===== Деструктор — освобождаем все счета =====

FinanceManager::~FinanceManager() {
    for (Account* a : accounts) delete a;
}

// ===== Управление счетами =====

void FinanceManager::addAccount(Account* acc) {
    accounts.push_back(acc);
    std::cout << "Добавлен счёт: [" << acc->getType() << "] " << acc->getName()
              << " | Начальный баланс: " << std::fixed << std::setprecision(2)
              << acc->getBalance() << " руб.\n";
}

void FinanceManager::showAccounts() const {
    if (accounts.empty()) { std::cout << "Счетов пока нет.\n"; return; }
    std::cout << "\n=== Счета и кошельки ===\n";
    for (const Account* a : accounts) a->printInfo();
}

Account* FinanceManager::findAccount(const std::string& name) const {
    for (Account* a : accounts)
        if (a->getName() == name) return a;
    return nullptr;
}

Account* FinanceManager::getAccountByIndex(int idx) const {
    if (idx < 0 || idx >= (int)accounts.size()) return nullptr;
    return accounts[idx];
}

int FinanceManager::getAccountCount() const {
    return (int)accounts.size();
}

void FinanceManager::topUp(const std::string& accountName, double amount) {
    Account* acc = findAccount(accountName);
    if (!acc) { std::cout << "Счёт \"" << accountName << "\" не найден.\n"; return; }
    acc->topUp(amount);
}

// ===== Добавление затраты =====

void FinanceManager::addExpense(const std::string& accountName, double amount,
                                const std::string& category, const std::string& description,
                                const Date& date) {
    Account* acc = findAccount(accountName);
    if (!acc) { std::cout << "Счёт \"" << accountName << "\" не найден.\n"; return; }
    if (!acc->withdraw(amount)) return;  // withdraw сам выведет ошибку если не хватает
    transactions.emplace_back(amount, category, description, accountName, date);
    std::cout << "Затрата " << std::fixed << std::setprecision(2) << amount
              << " руб. [" << category << "] добавлена. Баланс: " << acc->getBalance() << " руб.\n";
}

// ===== Фильтрация транзакций =====

std::vector<Transaction> FinanceManager::filterByDay(const Date& day) const {
    std::vector<Transaction> result;
    for (const auto& t : transactions)
        if (t.date.isSameDay(day)) result.push_back(t);
    return result;
}

std::vector<Transaction> FinanceManager::filterByWeek(const Date& today) const {
    std::vector<Transaction> result;
    for (const auto& t : transactions)
        if (t.date.isInLastDays(today, 7)) result.push_back(t);
    return result;
}

std::vector<Transaction> FinanceManager::filterByMonth(int month, int year) const {
    std::vector<Transaction> result;
    for (const auto& t : transactions)
        if (t.date.isSameMonth(month, year)) result.push_back(t);
    return result;
}

// ===== Вывод списка транзакций =====

void FinanceManager::printTransactions(const std::vector<Transaction>& list,
                                       const std::string& title) const {
    std::cout << "\n=== " << title << " ===\n";
    if (list.empty()) { std::cout << "  Затрат нет.\n"; return; }
    double total = 0;
    for (const auto& t : list) { t.print(); total += t.amount; }
    std::cout << "  " << std::string(50, '-') << "\n";
    std::cout << "  Итого: " << std::fixed << std::setprecision(2) << total << " руб.\n";
}

// ===== ТОП-3 затрат (самые крупные одиночные затраты) =====

void FinanceManager::printTop3Expenses(const std::vector<Transaction>& list,
                                       const std::string& period) const {
    std::cout << "\n--- ТОП-3 затрат за " << period << " ---\n";
    if (list.empty()) { std::cout << "  Затрат нет.\n"; return; }

    // Копируем и сортируем по убыванию суммы
    std::vector<Transaction> sorted = list;
    std::sort(sorted.begin(), sorted.end(),
        [](const Transaction& a, const Transaction& b) { return a.amount > b.amount; });

    int count = std::min((int)sorted.size(), 3);
    for (int i = 0; i < count; i++) {
        std::cout << "  #" << (i + 1) << " ";
        sorted[i].print();
    }
}

// ===== ТОП-3 категорий (наибольшая суммарная трата по категории) =====

void FinanceManager::printTop3Categories(const std::vector<Transaction>& list,
                                         const std::string& period) const {
    std::cout << "\n--- ТОП-3 категорий за " << period << " ---\n";
    if (list.empty()) { std::cout << "  Затрат нет.\n"; return; }

    // Агрегируем суммы по категориям через map
    std::map<std::string, double> catTotals;
    for (const auto& t : list) catTotals[t.category] += t.amount;

    // Переносим в вектор пар и сортируем
    std::vector<std::pair<std::string, double>> sorted(catTotals.begin(), catTotals.end());
    std::sort(sorted.begin(), sorted.end(),
        [](const auto& a, const auto& b) { return a.second > b.second; });

    int count = std::min((int)sorted.size(), 3);
    for (int i = 0; i < count; i++) {
        std::cout << "  #" << (i + 1) << " " << std::setw(14) << std::left
                  << sorted[i].first << " — "
                  << std::fixed << std::setprecision(2) << sorted[i].second << " руб.\n";
    }
}

// ===== Публичные методы отчётов =====

void FinanceManager::reportByDay(const Date& date) const {
    auto list = filterByDay(date);
    printTransactions(list, "Отчёт за день " + date.toString());
}

void FinanceManager::reportByWeek(const Date& today) const {
    auto list = filterByWeek(today);
    printTransactions(list, "Отчёт за неделю (последние 7 дней)");
}

void FinanceManager::reportByMonth(int month, int year) const {
    auto list = filterByMonth(month, year);
    std::ostringstream title;
    title << "Отчёт за месяц " << (month < 10 ? "0" : "") << month << "." << year;
    printTransactions(list, title.str());
}

// ===== Публичные методы рейтингов =====

void FinanceManager::ratingsWeek(const Date& today) const {
    auto list = filterByWeek(today);
    printTop3Expenses(list, "неделю");
    printTop3Categories(list, "неделю");
}

void FinanceManager::ratingsMonth(int month, int year) const {
    auto list = filterByMonth(month, year);
    std::ostringstream period;
    period << (month < 10 ? "0" : "") << month << "." << year;
    printTop3Expenses(list, period.str());
    printTop3Categories(list, period.str());
}

// ===== Сохранение отчётов в файл =====

// Вспомогательная: собрать текст отчёта и записать в файл
static std::string buildReport(const std::vector<Transaction>& list, const std::string& title) {
    std::ostringstream oss;
    oss << "=== " << title << " ===\n";
    if (list.empty()) { oss << "  Затрат нет.\n"; return oss.str(); }
    double total = 0;
    for (const auto& t : list) { oss << "  " << t.toString() << "\n"; total += t.amount; }
    oss << std::string(52, '-') << "\n";
    oss << "  Итого: " << std::fixed << std::setprecision(2) << total << " руб.\n\n";
    return oss.str();
}

void FinanceManager::writeToFile(const std::string& filename, const std::string& content) const {
    std::ofstream file(filename, std::ios::app);  // дописываем в конец файла
    if (!file.is_open()) { std::cout << "Не удалось открыть файл " << filename << "\n"; return; }
    file << content;
    std::cout << "Отчёт сохранён в файл: " << filename << "\n";
}

void FinanceManager::saveReportByDay(const Date& date) const {
    auto list = filterByDay(date);
    std::string content = buildReport(list, "Отчёт за день " + date.toString());
    writeToFile("report_day_" + date.toString() + ".txt", content);
}

void FinanceManager::saveReportByWeek(const Date& today) const {
    auto list = filterByWeek(today);
    std::string content = buildReport(list, "Отчёт за неделю (последние 7 дней от " + today.toString() + ")");
    writeToFile("report_week.txt", content);
}

void FinanceManager::saveReportByMonth(int month, int year) const {
    auto list = filterByMonth(month, year);
    std::ostringstream title, filename;
    title    << "Отчёт за месяц " << (month < 10 ? "0" : "") << month << "." << year;
    filename << "report_month_" << (month < 10 ? "0" : "") << month << "_" << year << ".txt";
    std::string content = buildReport(list, title.str());
    writeToFile(filename.str(), content);
}
