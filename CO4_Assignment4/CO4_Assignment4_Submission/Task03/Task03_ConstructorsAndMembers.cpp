#include <iostream>
#include <string>

class Address {
    std::string city;
    int pin;
public:
    Address(std::string c, int p) : city(std::move(c)), pin(p) {
        std::cout << "Address constructed ";
    }
    ~Address() { std::cout << "Address destroyed "; }
    std::string str() const { return city + "-" + std::to_string(pin); }
};

class Person {
protected:
    std::string name;
    int age;
    Address home;
public:
    Person(const std::string& n, int a, const std::string& city, int pin)
        : name(n), age(a), home(city, pin) {
        std::cout << "Person constructed ";
    }
    virtual ~Person() { std::cout << "Person destroyed "; }
};

class Student : public Person {
    long long regNo;
    std::string course;
public:
    Student(const std::string& n, int a, long long r, const std::string& city,
            int pin, std::string c)
        : Person(n, a, city, pin), regNo(r), course(std::move(c)) {
        std::cout << "Student constructed ";
    }
    ~Student() override { std::cout << "Student destroyed "; }
    void print() const {
        std::cout << "\n" << regNo << " " << name << " (" << age << ") "
                  << home.str() << " " << course << '\n';
    }
};

class Engine {
public:
    Engine() { std::cout << "Engine "; }
    ~Engine() { std::cout << "~Engine "; }
};
class Vehicle {
public:
    Vehicle() { std::cout << "Vehicle "; }
    ~Vehicle() { std::cout << "~Vehicle "; }
};
class Car : public Vehicle {
    Engine engine;
public:
    Car() { std::cout << "Car "; }
    ~Car() { std::cout << "~Car "; }
};

int main() {
    Student s("Kavya", 19, 192311001, "Salem", 636001, "CSE");
    s.print();
    std::cout << "Construction/destruction trace: ";
    { Car c; std::cout << "| "; }
    std::cout << '\n';
}