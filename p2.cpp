#include <iostream>
#include <string>
#include <vector>
class Course;
class Student {
private:
    std::string lastName;
    int studentID;
    Course* course;
public:
    Student(std::string name, int id);
    std::string getLastName();
    int getStudentID();
    Course* getCourse();
    void setCourse(Course*);


};
class Course 
{
private:
    int totalStudents;
    int maxStudents;

public:
    Course(int max) {
        totalStudents = 0;
        maxStudents = max;
    }

    int getTotalStudents() {
        return totalStudents;
    }

    int getMaxStudents() {
        return maxStudents;
    }

    bool isFull() {
        return totalStudents >= maxStudents;
    }

    void addStudent() {
        if (isFull()) {
            std::cout << "Ошибка: курс полон, невозможно добавить нового студента." << std::endl;
            return;
        }

        totalStudents++;
    }

    void removeStudent(Student &st) {
        if (totalStudents <= 0) {
            std::cout << "Ошибка: на курсе нет студентов, невозможно исключить студента." << std::endl;
            return;
        }
        st.setCourse(nullptr);
        totalStudents--;
    }
};

// class Student {
// private:
//     std::string lastName;
//     int studentID;
//     Course* course;

// public:
    Student:: Student(std::string name, int id) {
        lastName = name;
        studentID = id;
        course = nullptr;
    }

     std::string Student::getLastName() {
        return lastName;
    }

     int Student::getStudentID() {
        return studentID;
    }

    Course* Student::getCourse() {
        return course;
    }

    void Student::setCourse(Course* c) {
        course = c;
    }
// };

bool areOnSameCourse(Student* student1, Student* student2) {
    if (student1->getCourse() == nullptr || student2->getCourse() == nullptr) {
        return false;
    }

    return (student1->getCourse() == student2->getCourse());
}

int main() {
    Course englishCourse(30); // Создаем курс английского языка с максимальным количеством студентов 30
    Course frenchCourse(25); // Создаем курс французского языка с максимальным количеством студентов 25

    Student student1("Иванов", 1); // Создаем студента со студенческим билетом 1 и фамилией "Иванов"
    Student student2("Петров", 2); // Создаем студента со студенческим билетом 2 и фамилией "Петров"

    // Привязываем студентов к курсам
    student1.setCourse(&englishCourse);
    student2.setCourse(&frenchCourse);

    // Добавляем студентов на соответствующие курсы
    englishCourse.addStudent();
    frenchCourse.addStudent();
    printf("%d\n",englishCourse.getTotalStudents());
    // Проверяем, учатся ли студенты на одном курсе
    if (areOnSameCourse(&student1, &student2)) {
        std::cout << student1.getLastName() << " и " << student2.getLastName() << " учатся на одном курсе." << std::endl;
    } else {
        std::cout << student1.getLastName() << " и " << student2.getLastName() << " учатся на разных курсах." << std::endl;
    }
    std::cout << student1.getCourse() << std::endl;
    englishCourse.removeStudent(student1);
    printf("%d\n",englishCourse.getTotalStudents());
    std::cout << student1.getCourse() << std::endl;
    return 0;
}