// TASK 12 - Fourth zone, weekend discount and monthly pass
#include <iostream>
#include <array>
using namespace std;

enum class Zone { Inner, Middle, Outer, Airport };
constexpr array<long long, 4> FARES{1000, 2000, 3000, 6000};
class MonthlyPass {
    Zone first, second;
    bool active;
public:
    MonthlyPass(Zone a, Zone b, bool enabled) : first(a), second(b), active(enabled) {}
    bool covers(Zone zone) const { return active && (zone == first || zone == second); }
};
long long calculateFare(Zone zone, bool peak, bool weekend, bool pass) {
    if (pass) return 0;
    long long base = FARES[static_cast<int>(zone)];
    if (weekend) return base * 90 / 100; // weekend discount replaces peak surcharge
    if (peak) return base * 120 / 100;
    return base;
}
int main() {
    MonthlyPass pass(Zone::Inner, Zone::Airport, true);
    cout << "Airport weekday peak: Rs " << calculateFare(Zone::Airport, true, false, false) / 100 << '\n';
    cout << "Airport weekend: Rs " << calculateFare(Zone::Airport, true, true, false) / 100 << '\n';
    cout << "Airport covered by monthly pass: Rs " << calculateFare(Zone::Airport, false, false, pass.covers(Zone::Airport)) / 100 << '\n';
    return 0;
}