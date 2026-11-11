#include <iostream>
#include <chrono>
using namespace std;

class Time {
    int h, m;
public:
    Time(int hh, int mm) : h(hh), m(mm) {}
    friend inline int minutesBetween(const Time& a, const Time& b);
    friend inline bool earlier(const Time& a, const Time& b);
};
inline int minutesBetween(const Time& a, const Time& b) {
    int first = a.h * 60 + a.m;
    int second = b.h * 60 + b.m;
    return first > second ? first - second : second - first;
}
inline bool earlier(const Time& a, const Time& b) {
    return a.h * 60 + a.m < b.h * 60 + b.m;
}
int main() {
    Time departure(9, 45), arrival(13, 10);
    cout << minutesBetween(departure, arrival) << ' '
         << boolalpha << earlier(arrival, departure) << '\n';
    Time noonBefore(11, 59), noonAfter(12, 1);
    cout << minutesBetween(noonBefore, noonAfter) << ' '
         << earlier(noonBefore, noonAfter) << '\n';
    Time sameA(14, 30), sameB(14, 30);
    cout << minutesBetween(sameA, sameB) << ' '
         << earlier(sameA, sameB) << '\n';
    return 0;
}
