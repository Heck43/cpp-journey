#include "Account.h"
#include <iomanip>

// ===== Account =====

Account::Account(const std::string& name, double initialBalance)
    : name(name), balance(initialBalance) {}

void Account::topUp(double amount) {
    if (amount <= 0) { std::cout << "Сумма пополнения должна быть положительной.\n"; return; }
    balance += amount;
    std::cout << "Счёт \"" << name << "\" пополнен на " << std::fixed << std::setprecision(2)
              << amount << " руб. Баланс: " << balance << " руб.\n";
}

bool Account::withdraw(double amount) {
    if (amount > balance) {
        std::cout << "Недостаточно средств на счёте \"" << name << "\".\n";
        return false;
    }
    balance -= amount;
    return true;
}

void Account::printInfo() const {
    std::cout << "  [" << getType() << "] " << name
              << " | Баланс: " << std::fixed << std::setprecision(2) << balance << " руб.\n";
}

// ===== Wallet =====

Wallet::Wallet(const std::string& name, double initialBalance)
    : Account(name, initialBalance) {}

// ===== DebitCard =====

DebitCard::DebitCard(const std::string& name, double initialBalance)
    : Account(name, initialBalance) {}

// ===== CreditCard =====

CreditCard::CreditCard(const std::string& name, double creditLimit, double initialBalance)
    : Account(name, initialBalance), creditLimit(creditLimit) {}

bool CreditCard::withdraw(double amount) {
    // Кредитная карта позволяет уходить в минус, но не ниже -creditLimit
    if (balance - amount < -creditLimit) {
        std::cout << "Превышен кредитный лимит на карте \"" << name << "\" (лимит: "
                  << std::fixed << std::setprecision(2) << creditLimit << " руб.).\n";
        return false;
    }
    balance -= amount;
    return true;
}

void CreditCard::printInfo() const {
    std::cout << "  [Кредитная карта] " << name
              << " | Баланс: " << std::fixed << std::setprecision(2) << balance << " руб."
              << " | Кредитный лимит: " << creditLimit << " руб.\n";
}
