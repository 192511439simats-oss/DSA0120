#include <iostream>
#include <string>

class Prescription {
    int n;
    std::string* medicines;

public:
    explicit Prescription(int count)
        : n(count < 0 ? 0 : count),
          medicines(new std::string[n]) {}

    // Deep-copy constructor
    Prescription(const Prescription& other)
        : n(other.n), medicines(new std::string[other.n]) {
        for (int i = 0; i < n; ++i) medicines[i] = other.medicines[i];
    }

    // Deep-copy assignment with self-assignment protection
    Prescription& operator=(const Prescription& other) {
        if (this != &other) {
            std::string* fresh = new std::string[other.n];
            for (int i = 0; i < other.n; ++i) fresh[i] = other.medicines[i];
            delete[] medicines;
            medicines = fresh;
            n = other.n;
        }
        return *this;
    }

    ~Prescription() {
        delete[] medicines;
    }

    void set(int i, const std::string& medicine) {
        if (i >= 0 && i < n) medicines[i] = medicine;
    }

    std::string get(int i) const {
        return (i >= 0 && i < n) ? medicines[i] : "INVALID";
    }
};

int main() {
    Prescription p(2);
    p.set(0, "Paracetamol");
    p.set(1, "ORS");

    Prescription q = p;
    q.set(1, "Cetirizine");

    Prescription r(1);
    r = p;
    p.set(0, "Ibuprofen");
    p = p; // self-assignment test

    std::cout << p.get(0) << ' ' << p.get(1) << " | "
              << q.get(0) << ' ' << q.get(1) << " | "
              << r.get(0) << ' ' << r.get(1) << '\n';
    return 0;
}
