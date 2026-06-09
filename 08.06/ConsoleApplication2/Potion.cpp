#include "Potion.h"

Potion::Potion(const std::string& name, const std::string& description, int healAmount)
    : Item(name, description), healAmount(healAmount), used(false) {}

int Potion::getHealAmount() const {
    return healAmount;
}

bool Potion::isUsed() const {
    return used;
}

void Potion::use() {
    used = true;
}

std::string Potion::getFullInfo() const {
    std::string status = used ? " [ИСПОЛЬЗОВАНО]" : "";
    return "[Зелье] " + getName() + " (+" + std::to_string(healAmount) + " хп)" + status + " — " + getDescription();
}
