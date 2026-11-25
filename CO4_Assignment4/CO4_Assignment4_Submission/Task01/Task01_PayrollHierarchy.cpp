#include <iostream>
#include <memory>
#include <string>
#include <vector>

class Staff {
protected:
    std::string name;
    int id;
    double basic;
public:
    Staff(std::string n, int i, double b) : name(std::move(n)), id(i), basic(b) {}
    virtual ~Staff() = default;
    virtual double pay() const = 0;
    virtual void display() const {
        std::cout << name << " (" << id << "): " << pay() << '\n';
    }
};

class Professor : public Staff {
    double research;
public:
    Professor(std::string n, int i, double b, double r)
        : Staff(std::move(n), i, b), research(r) {}
    double pay() const override { return basic * 1.42 + research; }
};

class LabAssistant : public Staff {
public:
    LabAssistant(std::string n, int i, double b)
        : Staff(std::move(n), i, b) {}
    double pay() const override { return basic * 1.42; }
};

class GuestFaculty : public Staff {
    double hours, rate;
public:
    GuestFaculty(std::string n, int i, double h, double r)
        : Staff(std::move(n), i, 0.0), hours(h), rate(r) {}
    double pay() const override { return hours * rate; }
};

int main() {
    std::vector<std::unique_ptr<Staff>> staff;
    staff.push_back(std::make_unique<Professor>("Anita", 101, 50000, 8000));
    staff.push_back(std::make_unique<LabAssistant>("Ravi", 102, 30000));
    staff.push_back(std::make_unique<GuestFaculty>("Meena", 103, 20, 1000));
    for (const auto& person : staff) person->display();
}