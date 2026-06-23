#pragma once
#include <string>
#include "Date.h"

// Одна запись о затрате

struct Transaction {
    double      amount;       // сумма затраты
    std::string category;     // категория (Еда, Транспорт и т.д.)
    std::string description;  // краткое описание
    std::string accountName;  // с какого счёта списана
    Date        date;         // дата затраты

    Transaction(double amount, const std::string& category,
                const std::string& description, const std::string& accountName,
                const Date& date);

    void print() const;
    std::string toString() const;  // для записи в файл
};
