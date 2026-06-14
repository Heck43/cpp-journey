#pragma once
#include "Product.h"
// Класс food, наследующийся от product, с дополнительным полем expirationDate
class food : public product
{
private:
	std::string expirationDate;

public:
	food(std::string& name, double price, int id, std::string& expirationDate);
	std::string getExpirationDate() const;
	void displayInfo() const override;
};
