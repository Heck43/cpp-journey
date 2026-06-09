#include <iostream>
using namespace std;
class BankAccount{
    //Закрытые поля
    private:
    int accountNumber;
    int balace;
    string ownerName;
    
    // Конструктор, принимающий номер счета, имя владельца и начальный баланс (поумолчанию 0).
    public:
    BankAccount(int number, string name, int balace = 0){
        this->accountNumber = number;
        this->balace = balace;
        this->ownerName = name;
    }
    //Свойства
    int  getAccountNumber(){
        return accountNumber;
    }

    string getownerName(){
        return ownerName;
    }

    void setownerName(string name){
        ownerName = name;
    }
    int getbalace(){
        
        return balace;
    }

    //пополнение счета (сумма должна быть положительной).
    void Deposit(int amount){
        
        if (amount > 0) {
            balace += amount; 
            cout << "вы пополнили счет на " << amount << endl;
        }
        else cout << "поплонение должно быть положительным" << endl;
    }
    // снятие средств со счета ((сумма не может превышать баланс).
    void Withdraw(int amount){
        if (amount <= balace){
        balace -= amount;
        cout << "вы сняли со счета " << amount << endl;
        }
        else cout << "На счету недостаточно средств" << endl;
    }

    // показ информации
    void DisplayInfo(){
        
        cout << "Номер счета: " << accountNumber << endl;
        cout << "Владелец: " << ownerName << endl;
        cout << "Баланс: " << balace << endl;

    }
};


int main(){
    BankAccount acc(12345, "Ivan Ivanov", 1000);
    acc.DisplayInfo();
    acc.Deposit(500);
    acc.Withdraw(200);
    acc.DisplayInfo();
}