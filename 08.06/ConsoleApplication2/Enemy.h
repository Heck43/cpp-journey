#pragma once
#include "Character.h"

// враг — простой персонаж без инвентаря~~
class Enemy : public Character {
private:
    std::string type;  // тип врага для описания

public:
    Enemy(const std::string& name, const std::string& type,
          int maxHp, int baseAttack, int baseDefense);

    std::string getType() const;

    void printStatus() const override;
};
