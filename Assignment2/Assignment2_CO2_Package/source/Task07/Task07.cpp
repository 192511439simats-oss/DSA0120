#include <iostream>
#include <array>
#include <chrono>
using namespace std;

class ShiftingHistory {
    static constexpr int K = 50;
    array<int, K> data{};
    int count = 0;
public:
    void add(int value) {
        if (count < K) data[count++] = value;
        else {
            for (int i = 1; i < K; ++i) data[i - 1] = data[i];
            data[K - 1] = value;
        }
    }
    long long checksum() const {
        long long sum = 0;
        for (int i = 0; i < count; ++i) sum += data[i];
        return sum;
    }
};

class CircularHistory {
    static constexpr int K = 50;
    array<int, K> data{};
    int next = 0, count = 0;
public:
    void add(int value) {
        data[next] = value;
        next = (next + 1) % K;
        if (count < K) ++count;
    }
    long long checksum() const {
        long long sum = 0;
        for (int i = 0; i < count; ++i) sum += data[i];
        return sum;
    }
};

template <typename History>
long long measure(int operations) {
    History history;
    for (int i = 0; i < operations; ++i) history.add(i % 1000);
    return history.checksum();
}
int main(int argc, char* argv[]) {
    int operations = 2000000;
    if (argc > 1) operations = max(1, atoi(argv[1]));
    auto start1 = chrono::steady_clock::now();
    volatile long long result1 = measure<ShiftingHistory>(operations);
    auto end1 = chrono::steady_clock::now();
    auto start2 = chrono::steady_clock::now();
    volatile long long result2 = measure<CircularHistory>(operations);
    auto end2 = chrono::steady_clock::now();
    auto shiftUs = chrono::duration_cast<chrono::microseconds>(end1 - start1).count();
    auto ringUs = chrono::duration_cast<chrono::microseconds>(end2 - start2).count();
    cout << "Operations: " << operations << '\n';
    cout << "Shifting history checksum: " << result1 << '\n';
    cout << "Circular history checksum: " << result2 << '\n';
    cout << "Shifting time (microseconds): " << shiftUs << '\n';
    cout << "Circular time (microseconds): " << ringUs << '\n';
    cout << "Both designs retain the latest 50 values.\n";
}
