#include <iostream>
#include <string>
using namespace std;

struct Parcel {
    double weightKg;
    bool express;
    bool insured;
};

double charge(int weightGrams) {
    return (weightGrams / 1000.0) * 50.0;
}
double charge(double weightKg, bool express = false, bool insured = false) {
    double amount = weightKg * 50.0;
    if (express) amount += amount * 0.50;
    if (insured) amount += 20.0;
    return amount;
}
double charge(const Parcel& p) {
    return charge(p.weightKg, p.express, p.insured);
}

int main() {
    cout << "charge(2)       [int grams] : " << charge(2) << '\n';
    cout << "charge(2.0f)    [float]     : " << charge(2.0f) << '\n';
    cout << "charge(2.0)     [double]    : " << charge(2.0) << '\n';
    cout << "charge(2.0,true): " << charge(2.0, true) << '\n';
    cout << "charge(2.0,false,true): " << charge(2.0, false, true) << '\n';
    Parcel p{3.0, true, true};
    cout << "charge(Parcel)  : " << charge(p) << '\n';
    return 0;
}
