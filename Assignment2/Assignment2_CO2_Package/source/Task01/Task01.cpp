#include <iostream>
using namespace std;

void byValue(long long fee, int percent) {
    fee -= fee * percent / 100;
}
void byReference(long long& fee, int percent) {
    fee -= fee * percent / 100;
}
void byPointer(long long* fee, int percent) {
    if (fee != nullptr) *fee -= *fee * percent / 100;
}
void displayConst(const long long& fee) {
    cout << "Read-only fee: " << fee << '\n';
}

int main() {
    long long valueFee = 45000, referenceFee = 45000, pointerFee = 45000;
    byValue(valueFee, 10);
    byReference(referenceFee, 10);
    byPointer(&pointerFee, 25);

    cout << "After call by value    : " << valueFee << '\n';
    cout << "After call by reference: " << referenceFee << '\n';
    cout << "After call by pointer  : " << pointerFee << '\n';
    displayConst(referenceFee);
    return 0;
}
