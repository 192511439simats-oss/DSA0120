// TASK 03 - Data types, sizeof and safe money representation
#include <iostream>
#include <climits>
#include <limits>
using namespace std;

int main() {
    cout << "DATA TYPE SIZES (bytes)\n";
    cout << "bool: " << sizeof(bool) << '\n';
    cout << "char: " << sizeof(char) << '\n';
    cout << "int: " << sizeof(int) << '\n';
    cout << "long long: " << sizeof(long long) << '\n';
    cout << "float: " << sizeof(float) << '\n';
    cout << "double: " << sizeof(double) << '\n';
    cout << "INT_MAX: " << INT_MAX << '\n';
    cout << "LLONG_MAX: " << LLONG_MAX << '\n';
    long long farePaise = 3000;
    long long journeys = 3000000;
    cout << "Network collection in paise: " << farePaise * journeys << '\n';
    cout << "Use long long because the total exceeds 32-bit int range.\n";
    return 0;
}