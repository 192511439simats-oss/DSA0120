#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

class Time {
    int seconds;

public:
    explicit Time(int total = 0) : seconds(total < 0 ? 0 : total) {}

    Time& operator++() { ++seconds; return *this; }       // prefix
    Time operator++(int) { Time old(*this); ++seconds; return old; } // postfix

    bool operator==(const Time& other) const { return seconds == other.seconds; }
    bool operator<(const Time& other) const { return seconds < other.seconds; }

    void display() const {
        int h = seconds / 3600;
        int m = (seconds % 3600) / 60;
        int s = seconds % 60;
        std::cout << h << ':' << (m < 10 ? "0" : "") << m
                  << ':' << (s < 10 ? "0" : "") << s;
    }
};

class Playlist {
    std::vector<std::string> tracks;

public:
    explicit Playlist(std::vector<std::string> t) : tracks(std::move(t)) {}

    std::string& operator[](int index) {
        if (index < 0 || index >= static_cast<int>(tracks.size()))
            throw std::out_of_range("Playlist index out of range");
        return tracks[static_cast<std::size_t>(index)];
    }

    const std::string& operator[](int index) const {
        if (index < 0 || index >= static_cast<int>(tracks.size()))
            throw std::out_of_range("Playlist index out of range");
        return tracks[static_cast<std::size_t>(index)];
    }
};

int main() {
    Time t(5);
    Time a = t++;
    Time b = ++t;
    std::cout << "a = "; a.display();
    std::cout << "\nb = "; b.display();
    std::cout << "\nt = "; t.display();

    Playlist playlist({"Song One", "Song Two", "Song Three"});
    std::cout << "\nTrack 1: " << playlist[0] << '\n';
    try {
        std::cout << playlist[3] << '\n';
    } catch (const std::out_of_range& e) {
        std::cout << e.what() << '\n';
    }
    return 0;
}
