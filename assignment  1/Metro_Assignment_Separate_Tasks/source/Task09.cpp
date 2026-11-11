// TASK 09 - Implement and test the three-zone fare logic
#include <iostream>
#include <iomanip>
using namespace std;

enum class Zone { Inner, Middle, Outer };
constexpr long long FARES[] = {1000, 2000, 3000};
bool isPeak(int hour) { return (hour >= 8 && hour < 10) || (hour >= 17 && hour < 20); }
long long fareFor(Zone zone, int hour) {
    long long fare = FARES[static_cast<int>(zone)];
    if (isPeak(hour)) fare += fare * 20 / 100;
    return fare;
}
void printMoney(long long amount) {
    cout << "Rs " << amount / 100 << '.' << setw(2) << setfill('0') << amount % 100 << setfill(' ');
}
int main() {
    struct Test { Zone zone; int hour; const char* label; };
    Test tests[] = {{Zone::Inner, 7, "Inner off-peak"}, {Zone::Outer, 18, "Outer peak"}, {Zone::Middle, 12, "Middle off-peak"}};
    long long balance = 10000;
    cout << "FARE TEST REPORT\n";
    for (const auto& test : tests) {
        long long fare = fareFor(test.zone, test.hour);
        cout << test.label << ": ";
        if (balance - fare >= 5000) { balance -= fare; printMoney(fare); cout << ", remaining "; printMoney(balance); }
        else cout << "Denied, minimum balance rule";
        cout << '\n';
    }
    cout << "Peak boundary checks: 08:00=" << isPeak(8) << ", 10:00=" << isPeak(10)
         << ", 17:00=" << isPeak(17) << ", 20:00=" << isPeak(20) << '\n';
    return 0;
}