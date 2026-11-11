// TASK 11 - Recommended final design and complexity demonstration
#include <iostream>
#include <array>
using namespace std;

enum class Zone { Inner, Middle, Outer };
constexpr array<long long, 3> FARE_PAISE{1000, 2000, 3000};
class FareTable {
public:
    static long long fare(Zone zone, bool peak) {
        long long amount = FARE_PAISE[static_cast<int>(zone)];
        return peak ? amount * 120 / 100 : amount;
    }
};
class SmartCard {
    long long balance;
public:
    explicit SmartCard(long long initial) : balance(initial) {}
    bool pay(long long fare) {
        if (fare < 0 || balance - fare < 5000) return false;
        balance -= fare;
        return true;
    }
    long long getBalance() const { return balance; }
};
int main() {
    SmartCard card(15000);
    long long fare = FareTable::fare(Zone::Middle, true);
    cout << "Peak middle-zone fare: Rs " << fare / 100 << '.' << (fare % 100 < 10 ? "0" : "") << fare % 100 << '\n';
    cout << "Journey: " << (card.pay(fare) ? "Accepted" : "Denied") << '\n';
    cout << "Remaining balance: Rs " << card.getBalance() / 100 << '\n';
    cout << "Fare calculation: O(1) time; card storage: O(1) space; n journeys: O(n) time.\n";
    return 0;
}