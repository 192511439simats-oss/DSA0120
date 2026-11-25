#include <iostream>
#include <memory>
#include <string>
#include <vector>

class Vehicle {
protected:
    std::string registration;
    double dailyRate;
    bool rented = false;
public:
    Vehicle(std::string reg, double rate)
        : registration(std::move(reg)), dailyRate(rate) {}
    virtual ~Vehicle() = default;
    virtual double charge(int days) const = 0;
    virtual std::string type() const = 0;
    void rent() { rented = true; }
    double returnVehicle(int daysLate = 0) {
        rented = false;
        return charge(1) + daysLate * 200.0;
    }
    void list() const {
        std::cout << type() << " " << registration
                  << " | daily charge " << charge(1)
                  << " | " << (rented ? "Rented" : "Available") << '\n';
    }
};

class Bicycle : public Vehicle {
public:
    Bicycle(std::string r, double rate) : Vehicle(std::move(r), rate) {}
    double charge(int days) const override { return dailyRate * days; }
    std::string type() const override { return "Bicycle"; }
};

class TwoWheeler : public Vehicle {
    double fuelLevel;
public:
    TwoWheeler(std::string r, double rate, double fuel)
        : Vehicle(std::move(r), rate), fuelLevel(fuel) {}
    double charge(int days) const override { return dailyRate * days + (fuelLevel < 2 ? 50 : 0); }
    std::string type() const override { return "TwoWheeler"; }
};

class Car : public Vehicle {
protected:
    int seats;
public:
    Car(std::string r, double rate, int s) : Vehicle(std::move(r), rate), seats(s) {}
    double charge(int days) const override { return dailyRate * days + seats * 10; }
    std::string type() const override { return "Car"; }
};

class ElectricCar : public Car {
    double batteryKWh;
public:
    ElectricCar(std::string r, double rate, int s, double battery)
        : Car(std::move(r), rate, s), batteryKWh(battery) {}
    double charge(int days) const override { return dailyRate * days + batteryKWh * 8; }
    std::string type() const override { return "ElectricCar"; }
};

class ElectricBus : public Vehicle {
    int seats;
public:
    ElectricBus(std::string r, double rate, int s)
        : Vehicle(std::move(r), rate), seats(s) {}
    double charge(int days) const override { return dailyRate * days + seats * 5; }
    std::string type() const override { return "ElectricBus"; }
};

int main() {
    std::vector<std::unique_ptr<Vehicle>> fleet;
    fleet.push_back(std::make_unique<Bicycle>("BI-101", 100));
    fleet.push_back(std::make_unique<TwoWheeler>("TW-202", 250, 1.5));
    fleet.push_back(std::make_unique<Car>("CA-303", 1200, 5));
    fleet.push_back(std::make_unique<ElectricCar>("EV-404", 1500, 5, 40));
    fleet.push_back(std::make_unique<ElectricBus>("EB-505", 3000, 30));

    std::cout << "Fleet listing:\n";
    for (const auto& vehicle : fleet) vehicle->list();
    fleet[2]->rent();
    std::cout << "Car rented; status: ";
    fleet[2]->list();
    std::cout << "Return charge with 2 late days: " << fleet[2]->returnVehicle(2) << '\n';
    std::cout << "After return: ";
    fleet[2]->list();
    std::cout << "Electric bus added without modifying existing classes.\n";
}