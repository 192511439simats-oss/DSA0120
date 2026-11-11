#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int& highestMark(int marks[], int n) {
    int index = 0;
    for (int i = 1; i < n; ++i)
        if (marks[i] > marks[index]) index = i;
    return marks[index];
}
int highestIndex(const int marks[], int n) {
    int index = 0;
    for (int i = 1; i < n; ++i)
        if (marks[i] > marks[index]) index = i;
    return index;
}
int* highestPointer(int marks[], int n) {
    return &marks[highestIndex(marks, n)];
}
// Deliberately unsafe example: never call this function.
// int& danglingReference() { int local = 10; return local; }

int main() {
    int marks[] = {78, 91, 85, 88, 91};
    int n = sizeof(marks) / sizeof(marks[0]);
    cout << "Highest before moderation: " << highestMark(marks, n) << '\n';
    highestMark(marks, n) += 2;
    cout << "Highest after moderation : " << highestMark(marks, n) << '\n';

    int idx = highestIndex(marks, n);
    cout << "Index of highest mark    : " << idx << '\n';
    int* ptr = highestPointer(marks, n);
    cout << "Pointer value             : " << *ptr << '\n';

    const int& readOnlyHighest = highestMark(marks, n);
    cout << "Const reference           : " << readOnlyHighest << '\n';

    vector<int> growing = {60, 75, 90};
    int* oldAddress = &growing[2];
    growing.push_back(95); // may reallocate; oldAddress may now be invalid
    cout << "Vector highest after growth: " << *max_element(growing.begin(), growing.end()) << '\n';
    (void)oldAddress; // do not dereference an invalidated pointer/reference
    return 0;
}
