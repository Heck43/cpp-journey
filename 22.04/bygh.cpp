#include <iostream>
using namespace std;
class Product{
    public:
    // автосвойства
    string name;
    int Quantity;
    int price;
    // конструктор принимающий все
    Product(string name, int Quantity, int price){
        this-> name = name;
        this-> Quantity = Quantity;
        this-> price = price;
    }
    // метот возвращающий общую стоимость товара на складе
    int GetTotalValue(){
        return price * Quantity;
    }

    // который уменьшает количество товара на складе, если запрашиваемое количество доступно.
    bool Sell(int amount)
    {
        // Возвращает true , если продажа успешна
        if(Quantity >= amount){
            Quantity -= amount;
            cout  << "вы продали " << amount << " " << name << endl;
            return true;
        }
        // в противном случае он возвращает false
        cout << "нет столько товара" << endl;
        cout << "остаток товара " << name << " :" << Quantity << endl;
        return false;
    }
};

int main(){
    Product apple("apple", 10, 100);
    Product book("book", 5, 300);
    cout << "общая стоимость товара " << apple.GetTotalValue() << endl;
    cout << "общая стоимость товара " << book.GetTotalValue() << endl;
    apple.Sell(2);
    cout << "общая стоимость товара " << apple.GetTotalValue() << endl;
    book.Sell(30);

}