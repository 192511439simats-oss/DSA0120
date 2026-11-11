// TASK 10 - Compare expected totals and integer range
#include <iostream>
#include <climits>
using namespace std;
int main() {
    const long long maxFarePaise = 3000;
    const long long journeyCounts[] = {20000, 500000, 3000000};
    cout << "NETWORK COLLECTION ESTIMATE\n";
    for (long long journeys : journeyCounts) {
        long long totalPaise = journeys * maxFarePaise;
        cout << journeys << " journeys: Rs " << totalPaise / 100 << '\n';
    }
    long long wholeNetworkPaise = journeyCounts[2] * maxFarePaise;
    cout << "Whole network total in paise: " << wholeNetworkPaise << '\n';
    cout << "INT_MAX: " << INT_MAX << '\n';
    cout << (wholeNetworkPaise > INT_MAX ? "Use long long for total collection.\n" : "int is sufficient.\n");
    return 0;
}