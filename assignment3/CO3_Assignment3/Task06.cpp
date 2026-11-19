#include <cstring>
#include <iostream>

class Text {
    char* data;

public:
    explicit Text(const char* value = "") {
        std::size_t length = std::strlen(value);
        data = new char[length + 1];
        std::strcpy(data, value);
    }

    Text(const Text& other) {
        std::size_t length = std::strlen(other.data);
        data = new char[length + 1];
        std::strcpy(data, other.data);
    }

    Text& operator=(const Text& other) {
        if (this != &other) {
            std::size_t length = std::strlen(other.data);
            char* fresh = new char[length + 1];
            std::strcpy(fresh, other.data);
            delete[] data;
            data = fresh;
        }
        return *this;
    }

    ~Text() { delete[] data; }

    Text operator+(const Text& other) const {
        std::size_t a = std::strlen(data), b = std::strlen(other.data);
        char* joined = new char[a + b + 1];
        std::strcpy(joined, data);
        std::strcat(joined, other.data);
        Text result(joined);
        delete[] joined;
        return result;
    }

    bool operator==(const Text& other) const {
        return std::strcmp(data, other.data) == 0;
    }

    bool operator!=(const Text& other) const { return !(*this == other); }

    friend std::ostream& operator<<(std::ostream& out, const Text& value) {
        return out << value.data;
    }
};

int main() {
    Text first("Hello ");
    Text second("World");
    Text third = first + second;
    std::cout << third << '\n';
    std::cout << std::boolalpha << (third != first) << '\n';

    Text empty;
    Text copy = empty;
    copy = copy; // self-assignment test
    std::cout << "Empty text: [" << copy << "]\n";
    return 0;
}
