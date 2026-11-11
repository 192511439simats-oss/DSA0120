// TASK 08 - Read and print data safely
#include <iostream>
#include <iomanip>
#include <limits>
using namespace std;

int main() {
    int zone, hour, balanceRupees;
    cout << "Enter zone (1-3), hour (0-23), and balance in rupees: ";
    if (!(cin >> zone >> hour >> balanceRupees)) {
        cout << "Invalid input: enter integers only.\n";
        return 1;
    }
    if (zone < 1 || zone > 3 || hour < 0 || hour > 23 || balanceRupees < 0) {
        cout << "Invalid input: check zone, hour and balance.\n";
        return 1;
    }
    const int baseFarePaise[] = {1000, 2000, 3000};
    int fare = baseFarePaise[zone - 1];
    bool peak = (hour >= 8 && hour < 10) || (hour >= 17 && hour < 20);
    if (peak) fare += fare * 20 / 100;
    long long balancePaise = static_cast<long long>(balanceRupees) * 100;
    cout << fixed << setprecision(2);
    cout << "Fare: Rs " << fare / 100.0 << '\n';
    if (balancePaise - fare >= 5000)
        cout << "Journey accepted. Remaining: Rs " << (balancePaise - fare) / 100.0 << '\n';
    else cout << "Journey denied: minimum Rs 50 must remain.\n";
    return 0;
}