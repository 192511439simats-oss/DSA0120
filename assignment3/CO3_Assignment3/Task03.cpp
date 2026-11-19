#include <iostream>
#include <vector>
#include <string>

class Event {
    int rows, seatsPerRow;
    char** seats;
    std::string name;

public:
    Event(const std::string& eventName, int r, int s)
        : rows(r > 0 ? r : 0),
          seatsPerRow(s > 0 ? s : 0),
          seats(nullptr), name(eventName) {
        if (rows > 0 && seatsPerRow > 0) {
            seats = new char*[rows];
            int made = 0;
            try {
                for (; made < rows; ++made) {
                    seats[made] = new char[seatsPerRow];
                    for (int j = 0; j < seatsPerRow; ++j) seats[made][j] = 'O';
                }
            } catch (...) {
                while (made > 0) delete[] seats[--made];
                delete[] seats;
                throw;
            }
        }
        std::cout << "Created: " << name << '\n';
    }

    Event(const Event&) = delete;
    Event& operator=(const Event&) = delete;

    bool book(int r, int s) {
        if (!seats || r < 0 || r >= rows || s < 0 || s >= seatsPerRow ||
            seats[r][s] == 'X') return false;
        seats[r][s] = 'X';
        return true;
    }

    bool cancel(int r, int s) {
        if (!seats || r < 0 || r >= rows || s < 0 || s >= seatsPerRow ||
            seats[r][s] == 'O') return false;
        seats[r][s] = 'O';
        return true;
    }

    void display() const {
        std::cout << name << " seat map:\n";
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < seatsPerRow; ++j) std::cout << seats[i][j] << ' ';
            std::cout << '\n';
        }
    }

    ~Event() {
        if (seats) {
            for (int i = 0; i < rows; ++i) delete[] seats[i];
            delete[] seats;
        }
        std::cout << "Closed: " << name << '\n';
    }
};

int main() {
    Event local("Local Event", 2, 3);
    local.book(0, 1);
    local.display();

    {
        Event blockEvent("Block Event", 1, 2);
        blockEvent.book(0, 0);
    }

    Event* heapEvent = new Event("Heap Event", 2, 2);
    heapEvent->book(1, 1);
    heapEvent->display();
    delete heapEvent;

    Event zeroRows("Zero Row Event", 0, 4);
    return 0;
}
