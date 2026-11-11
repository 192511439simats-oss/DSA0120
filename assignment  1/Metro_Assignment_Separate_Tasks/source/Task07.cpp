// TASK 07 - Procedural and object-oriented SmartCard comparison
#include <iostream>
using namespace std;

// Procedural approach: balance is passed to free functions.
bool proceduralTravel(long long& balance, long long fare) {
    if (fare < 0 || balance - fare < 5000) return false;
    balance -= fare;
    return true;
}

// OOP approach: balance and its operations are grouped in a class.
class SmartCard {
private:
    long long balance;
public:
    explicit SmartCard(long long amount) : balance(amount) {}
    bool travel(long long fare) {
        if (fare < 0 || balance - fare < 5000) return false;
        balance -= fare;
        return true;
    }
    long long getBalance() const { return balance; }
};

int main() {
    long long proceduralBalance = 10000;
    SmartCard objectCard(10000);
    cout << "Procedural journey: " << (proceduralTravel(proceduralBalance, 2000) ? "Accepted" : "Denied") << '\n';
    cout << "Procedural balance: Rs " << proceduralBalance / 100 << '\n';
    cout << "OOP journey: " << (objectCard.travel(2000) ? "Accepted" : "Denied") << '\n';
    cout << "OOP balance: Rs " << objectCard.getBalance() / 100 << '\n';
    return 0;
}