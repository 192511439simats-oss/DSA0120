// TASK 06 - Control structures and completed fare calculation
#include <iostream>
#include <iomanip>
using namespace std;

enum class Zone { Inner, Middle, Outer };
long long calculateFare(Zone zone, bool peak) {
    long long fare;
    switch (zone) {
        case Zone::Inner: fare = 1000; break;
        case Zone::Middle: fare = 2000; break;
        case Zone::Outer: fare = 3000; break;
        default: return -1;
    }
    if (peak) fare += fare * 20 / 100;
    return fare;
}
bool canTravel(long long balance, long long fare) {
    return fare >= 0 && balance - fare >= 5000;
}
int main() {
    long long balance = 10000;
    struct Trip { Zone zone; bool peak; };
    Trip trips[] = {{Zone::Inner, false}, {Zone::Outer, true}, {Zone::Middle, false}};
    for (const Trip& trip : trips) {
        long long fare = calculateFare(trip.zone, trip.peak);
        if (canTravel(balance, fare)) {
            balance -= fare;
            cout << "Fare Rs " << fare / 100 << '.' << setw(2) << setfill('0') << fare % 100 << setfill(' ');
        } else cout << "Denied (low balance)";
        cout << " balance Rs " << balance / 100 << '\n';
    }
    return 0;
}