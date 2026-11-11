// TASK 01 - Object-oriented analysis: Metro Smart Card
#include <iostream>
#include <string>
using namespace std;

class SmartCard {
private:
    int balancePaise;
public:
    explicit SmartCard(int amount) : balancePaise(amount) {}
    int getBalance() const { return balancePaise; }
    bool makeJourney(int farePaise) {
        const int minimumBalance = 5000;
        if (farePaise < 0 || balancePaise - farePaise < minimumBalance)
            return false;
        balancePaise -= farePaise;
        return true;
    }
};

int main() {
    SmartCard card(10000);
    cout << "METRO SMART-CARD - OOP DEMONSTRATION\n";
    cout << "Initial balance: Rs " << card.getBalance() / 100 << '\n';
    if (card.makeJourney(2000)) cout << "Journey accepted\n";
    else cout << "Journey denied\n";
    cout << "Final balance: Rs " << card.getBalance() / 100 << '\n';
    cout << "Rule: balance must remain at least Rs 50.\n";
    return 0;
}