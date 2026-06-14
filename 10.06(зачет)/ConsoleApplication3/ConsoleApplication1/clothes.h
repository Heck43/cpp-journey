#pragma once
#include "Product.h"
// Класс clothes, наследующийся от product, с дополнительным полем size
class clothes : public product
{
private:
	std::string size;

public:
	clothes(std::string& name, double price, int id, std::string& size);
	std::string getSize() const;
	void displayInfo() const override;
};
