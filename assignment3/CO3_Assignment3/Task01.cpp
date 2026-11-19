#include <iostream>
#include <string>
#include <utility>

class Book {
    std::string title;
    int copies;

    static int validCopies(int value) {
        return value < 0 ? 0 : value;
    }

public:
    Book() : Book("", 0) {}                         // delegated default constructor
    explicit Book(const std::string& t) : Book(t, 0) {}
    Book(const std::string& t, int c) : title(t), copies(validCopies(c)) {}

    void display() const {
        std::cout << "Title: " << (title.empty() ? "(empty)" : title)
                  << ", Copies: " << copies << '\n';
    }
};

int main() {
    Book empty;
    Book donated("The Alchemist");
    Book full("C++ Programming", 5);
    Book invalid("Invalid Book", -3);

    empty.display();
    donated.display();
    full.display();
    invalid.display();
    return 0;
}
