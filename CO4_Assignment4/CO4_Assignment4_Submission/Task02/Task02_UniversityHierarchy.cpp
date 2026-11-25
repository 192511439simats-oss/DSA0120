#include <iostream>
#include <string>

class Person {
protected:
    std::string name;
    int id;
    std::string phone;
public:
    Person(std::string n, int i, std::string p)
        : name(std::move(n)), id(i), phone(std::move(p)) {}
    virtual ~Person() = default;
    void showPerson() const { std::cout << name << " " << id << " " << phone; }
};

class Student : virtual public Person {
protected:
    std::string programme;
    double cgpa;
public:
    Student(std::string n, int i, std::string p, std::string prog, double c)
        : Person(std::move(n), i, std::move(p)),
          programme(std::move(prog)), cgpa(c) {}
};

class Staff : virtual public Person {
protected:
    std::string department;
    double salary;
public:
    Staff(std::string n, int i, std::string p, std::string d, double s)
        : Person(std::move(n), i, std::move(p)),
          department(std::move(d)), salary(s) {}
};

class TeachingAssistant : public Student, public Staff {
public:
    TeachingAssistant(std::string n, int i, std::string p, std::string prog,
                      double c, std::string d, double s)
        : Person(std::move(n), i, std::move(p)),
          Student("", 0, "", std::move(prog), c),
          Staff("", 0, "", std::move(d), s) {}
    void display() const {
        showPerson();
        std::cout << " | " << programme << " " << cgpa
                  << " | " << department << " " << salary << '\n';
    }
};

class ResearchScholar : public Student {
    double fellowship;
public:
    ResearchScholar(std::string n, int i, std::string p, std::string prog,
                    double c, double f)
        : Person(std::move(n), i, std::move(p)),
          Student("", 0, "", std::move(prog), c), fellowship(f) {}
    void display() const {
        showPerson();
        std::cout << " | " << programme << " " << cgpa
                  << " | Fellowship " << fellowship << '\n';
    }
};

int main() {
    TeachingAssistant ta("Kavya", 201, "9876543210", "CSE", 8.7, "CSE", 35000);
    ResearchScholar rs("Arun", 202, "9876501234", "AI", 9.1, 12000);
    std::cout << "Teaching Assistant: "; ta.display();
    std::cout << "Research Scholar: "; rs.display();

    // Construction order with a shared virtual Person base.
    struct P { P(){ std::cout << "Person "; } };
    struct S : virtual P { S(){ std::cout << "Student "; } };
    struct T : virtual P { T(){ std::cout << "Staff "; } };
    struct TA : S, T { TA(){ std::cout << "TA "; } };
    std::cout << "Constructor trace: ";
    TA sample;
    std::cout << '\n';
}