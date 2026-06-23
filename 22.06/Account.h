#pragma once
#include <string>
#include <iostream>

// ===== Базовый абстрактный класс счёта =====

class Account {
protected:
    std::string name;     // название счёта
    double      balance;  // текущий баланс

public:
    Account(const std::string& name, double initialBalance = 0.0);
    virtual ~Account() = default;

    virtual std::string getType() const = 0;  // "Кошелёк" / "Дебетовая" / "Кредитная"
    virtual bool        withdraw(double amount);  // списать деньги (с проверкой)
    virtual void        printInfo() const;

    void        topUp(double amount);  // пополнить
    std::string getName()    const { return name; }
    double      getBalance() const { return balance; }
};

// ===== Наличные кошелёк =====

class Wallet : public Account {
public:
    Wallet(const std::string& name, double initialBalance = 0.0);
    std::string getType() const override { return "Кошелёк"; }
};

// ===== Дебетовая карта =====

class DebitCard : public Account {
public:
    DebitCard(const std::string& name, double initialBalance = 0.0);
    std::string getType() const override { return "Дебетовая карта"; }
};

// ===== Кредитная карта =====
// Баланс может уходить в минус — до уровня кредитного лимита

class CreditCard : public Account {
private:
    double creditLimit;  // максимально допустимый минус
public:
    CreditCard(const std::string& name, double creditLimit, double initialBalance = 0.0);

    std::string getType()    const override { return "Кредитная карта"; }
    bool        withdraw(double amount) override;  // позволяет уходить в минус до лимита
    void        printInfo()  const override;
};
