#include "Transaction.h"
#include <iostream>
#include <sstream>
#include <iomanip>

Transaction::Transaction(double amount, const std::string& category,
                         const std::string& description, const std::string& accountName,
                         const Date& date)
    : amount(amount), category(category), description(description),
      accountName(accountName), date(date) {}

void Transaction::print() const {
    std::cout << "  [" << date.toString() << "] "
              << std::setw(14) << std::left << category
              << " | " << std::setw(8) << std::right << std::fixed
              << std::setprecision(2) << amount << " руб."
              << "  (" << accountName << ")";
    if (!description.empty()) std::cout << "  — " << description;
    std::cout << std::endl;
}

std::string Transaction::toString() const {
    // Формат для записи в файл
    std::ostringstream oss;
    oss << date.toString() << " | "
        << std::setw(14) << std::left << category << " | "
        << std::setw(10) << std::right << std::fixed << std::setprecision(2) << amount << " руб. | "
        << accountName;
    if (!description.empty()) oss << " — " << description;
    return oss.str();
}
