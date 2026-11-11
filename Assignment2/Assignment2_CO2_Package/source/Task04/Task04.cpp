#include <iostream>
#include <string>
using namespace std;

class SavingsAccount {
private:
    string accountNumber;
    double balance;
    double transactions[10];
    int count;

    void record(double amount) {
        if (count < 10) {
            transactions[count++] = amount;
        } else {
            for (int i = 1; i < 10; ++i) transactions[i - 1] = transactions[i];
            transactions[9] = amount;
        }
    }

public:
    SavingsAccount(const string& number, double openingBalance)
        : accountNumber(number), balance(openingBalance), count(0) {}

    void deposit(double amount) {
        if (amount <= 0) { cout << "Invalid deposit\n"; return; }
        balance += amount;
        record(amount);
    }
    bool withdraw(double amount);
    void miniStatement() const;
    double getBalance() const { return balance; }
};

bool SavingsAccount::withdraw(double amount) {
    if (amount <= 0 || amount > balance) return false;
    balance -= amount;
    record(-amount);
    return true;
}
void SavingsAccount::miniStatement() const {
    cout << "Account: " << accountNumber << "\nRecent transactions:\n";
    for (int i = 0; i < count; ++i)
        cout << (transactions[i] >= 0 ? "Deposit  +" : "Withdraw ") << transactions[i] << '\n';
    cout << "Balance: " << balance << '\n';
}

int main() {
    SavingsAccount account("SA1024", 1000);
    account.deposit(500);
    account.withdraw(200);
    account.deposit(100);
    account.withdraw(50);
    account.miniStatement();
    return 0;
}
