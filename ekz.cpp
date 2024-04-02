#include <iostream>
#include <cstring>

class MyClass {
public:
    int* data;

    // Конструктор по умолчанию
    MyClass() {
        data = new int[5];
        for (int i = 0; i < 5; i++) {
            data[i] = i;
        }
    }

    // // Копирующий конструктор
    // MyClass(const MyClass& other) {
    //     // Выделяем новую память для копирования данных
    //     data = new int[5];

    //     // Копируем данные из другого объекта
    //     for (int i = 0; i < 5; i++) {
    //         data[i] = other.data[i];
    //     }
    // }

    // Деструктор
    ~MyClass() {
        delete[] data;
    }
};

int main() {
    // Создаем объект
    MyClass obj1;

    // Создаем новый объект с использованием копирующего конструктора
    MyClass obj2 = obj1;

    // Изменяем данные в obj1
    for (int i = 0; i < 5; i++) {
        obj2.data[i] = i * 2;
    }

    // Выводим данные из obj1 и obj2
    for (int i = 0; i < 5; i++) {
        std::cout << obj1.data[i] << " ";
    }
    std::cout << std::endl;
    for (int i = 0; i < 5; i++) {
        std::cout << obj2.data[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}
