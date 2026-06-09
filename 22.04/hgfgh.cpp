#include <iostream>
using namespace std;
// класс ученик
class student
{
    // закрытые поля 
    // имя, группа, массив из 5 элементов для оценок
    private:
    string fullname;
    int group;
    int grades[5];

    // Конструктор, принимающий имя, группу и массив оценок. 
    public:
    student(string fullname, int group, int grades[5]){
        
        this->fullname = fullname;
        this->group = group;
        for (int i = 0; i < 5; i++)
        {
            this->grades[i] = grades[i];
        }

    }
    // Свойства для доступа к имени и группе (только для чтения — get ).
    string get_fullname()
    {
        return fullname;
    }
    // Метод GetAverageGrade() , возвращающий средний балл студента.
    double GetAverageGrade(){
        
        double avr = 0;
        for (int i = 0; i < 5; i++)
        {
            avr += grades[i];
        }
        return avr / 5;
    }
    // Метод DisplayInfo() , выводящий информацию о студенте.
    void DisplayInfo()
    {
        cout << "Имя: " << get_fullname() << "\nГруппа: " << group << "\nОценки: ";
        for (int i = 0; i < 5; i++)
        {
            cout << grades[i] << " ";
        }
        cout << "\nСредний балл: " << GetAverageGrade() << "\n";
    }
};

int main()
{
    // Создаем массив из 3 студентов.
    int gr1[5] = {5, 5, 5, 5, 5};
    int gr2[5] = {4, 5, 3, 2, 2};
    int gr3[5] = {3, 3, 3, 3, 3};
    student s1("Иванов", 101, gr1);
    student s2("Петров", 101, gr2);
    student s3("Сидоров", 102, gr3);

    // Выводим информацию о студентах.
    s1.DisplayInfo();
    s2.DisplayInfo();
    s3.DisplayInfo();
}