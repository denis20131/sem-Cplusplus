#include <iostream>

// Объявление класса B
class B;

class A;

class B {
public:
    void showA(A& ob);
};


// Класс A
class A {
private:
    int a;
public:
    A() : a(0) {}

    // Объявление B в качестве дружественного класса
    friend void B::showA(A & ob);
};

// Класс B

void B::showA(A & ob) {
        // Доступ к закрытому члену класса A
        std::cout << "Закрытый член класса A: " << ob.a << std::endl;
    }

int main() {
    A objA;
    B objB;

    objB.showA(objA); // Выводит закрытый член класса A

    return 0;
}
