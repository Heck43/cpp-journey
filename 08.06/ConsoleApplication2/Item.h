#pragma once
#include <string>

// базовый класс для всех предметов~~ мрррр
class Item {
private:
    std::string name;
    std::string description;

public:
    Item(const std::string& name, const std::string& description);
    virtual ~Item() = default;

    std::string getName() const;
    std::string getDescription() const;

    // виртуальный метод - наследники могут переопределить
    virtual std::string getFullInfo() const;
};
