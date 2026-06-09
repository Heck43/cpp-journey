#pragma once
#include <string>

// базовый класс персонажа — общий для игрока и врага~~
class Character {
private:
    std::string name;
    int maxHp;
    int currentHp;
    int baseAttack;   // базовая атака
    int baseDefense;  // базовая защита

public:
    Character(const std::string& name, int maxHp, int baseAttack, int baseDefense);
    virtual ~Character() = default;

    // геттеры
    std::string getName() const;
    int getMaxHp() const;
    int getCurrentHp() const;
    int getBaseAttack() const;
    int getBaseDefense() const;

    // проверка живой ли персонаж
    bool isAlive() const;

    // получить урон (учитывает защиту)
    void takeDamage(int damage);

    // восстановить хп
    void heal(int amount);

    // виртуальный — у игрока и врага своя сила атаки
    virtual int getAttackPower() const;
    virtual int getDefenseValue() const;

    // вывод состояния в консоль
    virtual void printStatus() const;
};
