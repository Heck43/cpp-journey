#pragma once
#include <vector>
#include <string>
#include "Account.h"
#include "Transaction.h"

// ===== Главный менеджер финансов =====
// Хранит все счета и транзакции, формирует отчёты и рейтинги

class FinanceManager {
private:
    std::vector<Account*>     accounts;      // все кошельки и карты
    std::vector<Transaction>  transactions;  // все затраты

    // Вспомогательные: отфильтровать транзакции по периоду
    std::vector<Transaction> filterByDay(const Date& day) const;
    std::vector<Transaction> filterByWeek(const Date& today) const;
    std::vector<Transaction> filterByMonth(int month, int year) const;

    // Вспомогательная: напечатать список транзакций + итог
    void printTransactions(const std::vector<Transaction>& list, const std::string& title) const;

    // Вспомогательная: ТОП-3 затрат и категорий из списка
    void printTop3Expenses(const std::vector<Transaction>& list, const std::string& period) const;
    void printTop3Categories(const std::vector<Transaction>& list, const std::string& period) const;

    // Записать блок отчёта в файл
    void writeToFile(const std::string& filename, const std::string& content) const;

public:
    ~FinanceManager();

    // Управление счетами
    void addAccount(Account* acc);
    void showAccounts() const;
    Account* findAccount(const std::string& name) const;
    Account* getAccountByIndex(int idx) const;  // для выбора по номеру из меню
    int  getAccountCount() const;
    void topUp(const std::string& accountName, double amount);

    // Добавить затрату
    void addExpense(const std::string& accountName, double amount,
                    const std::string& category, const std::string& description,
                    const Date& date);

    // Отчёты по периоду
    void reportByDay(const Date& date) const;
    void reportByWeek(const Date& today) const;
    void reportByMonth(int month, int year) const;

    // Рейтинги ТОП-3
    void ratingsWeek(const Date& today) const;
    void ratingsMonth(int month, int year) const;

    // Сохранить отчёт в файл
    void saveReportByDay(const Date& date) const;
    void saveReportByWeek(const Date& today) const;
    void saveReportByMonth(int month, int year) const;
};
