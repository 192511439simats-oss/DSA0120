#include <iostream>
#include <memory>
#include <vector>

class Account {
public:
    double rate() const { return 3.5; }             // non-virtual: static binding
    virtual double vrate() const { return 3.5; }    // virtual: dynamic binding
    virtual ~Account() { std::cout << "Account destroyed\n"; }
};

class SeniorAccount : public Account {
    double* history;
public:
    SeniorAccount() : history(new double[100]{}) {}
    double rate() const { return 4.0; }
    double vrate() const override { return 4.0; }
    ~SeniorAccount() override {
        delete[] history;
        std::cout << "SeniorAccount destroyed\n";
    }
};

int main() {
    SeniorAccount senior;
    Account* p = &senior;
    Account slicedCopy = senior; // slicing: only Account subobject is copied
    std::cout << "Base pointer calls: " << p->rate() << " " << p->vrate() << '\n';
    std::cout << "Sliced copy virtual call: " << slicedCopy.vrate() << '\n';

    std::vector<std::unique_ptr<Account>> accounts;
    accounts.push_back(std::make_unique<Account>());
    accounts.push_back(std::make_unique<SeniorAccount>());
    std::cout << "Stored account rates:\n";
    for (const auto& account : accounts) std::cout << account->vrate() << '\n';
    std::cout << "Leaving main; virtual destructors release derived resources:\n";
}