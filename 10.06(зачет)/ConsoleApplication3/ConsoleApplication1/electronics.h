#pragma once
#include "Product.h"
// Класс electronics, наследующийся от product, с дополнительным полем model
class electronics : public product
{
private:
	std::string model;

public:
	electronics(std::string& name, double price, int id, std::string& model);
	std::string getModel() const;
	void displayInfo() const override;
};
