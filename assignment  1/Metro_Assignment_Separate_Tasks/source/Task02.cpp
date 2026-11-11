// TASK 02 - Tokens, identifiers, constants and enum class
#include <iostream>
#include <array>
using namespace std;

enum class Zone { Inner, Middle, Outer };
constexpr array<int, 3> FARE_PAISE{1000, 2000, 3000};
constexpr int PEAK_SURCHARGE_PERCENT = 20;
constexpr int MIN_BALANCE_PAISE = 5000;

int main() {
    cout << "METRO FARE CONSTANTS\n";
    cout << "Inner fare: Rs " << FARE_PAISE[static_cast<int>(Zone::Inner)] / 100 << '\n';
    cout << "Middle fare: Rs " << FARE_PAISE[static_cast<int>(Zone::Middle)] / 100 << '\n';
    cout << "Outer fare: Rs " << FARE_PAISE[static_cast<int>(Zone::Outer)] / 100 << '\n';
    cout << "Peak surcharge: " << PEAK_SURCHARGE_PERCENT << "%\n";
    cout << "Minimum remaining balance: Rs " << MIN_BALANCE_PAISE / 100 << '\n';
    return 0;
}