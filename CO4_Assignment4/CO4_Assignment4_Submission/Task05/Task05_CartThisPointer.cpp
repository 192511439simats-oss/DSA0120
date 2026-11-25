#include <iomanip>
#include <iostream>
#include <string>

class Cart {
    std::string items[10];
    double prices[10]{};
    int n = 0;
    double discount = 0;
public:
    Cart& add(const std::string& item, double price) {
        if (n < 10 && price >= 0) {
            items[n] = item;
            prices[n] = price;
            ++n;
        }
        return *this;
    }
    Cart& setDiscount(double discount) {
        this->discount = discount;
        return *this;
    }
    double total() const {
        double sum = 0;
        for (int i = 0; i < n; ++i) sum += prices[i];
        return sum * (100 - discount) / 100;
    }
    const std::string& getItem(int index) const { return items[index]; }
};

int main() {
    Cart c;                                  // direct object
    c.add("Rice", 60).add("Dal", 120).setDiscount(10);
    Cart* pointer = &c;                      // pointer with ->
    pointer->add("Oil", 180);
    Cart& reference = c;                     // reference
    std::cout << std::fixed << std::setprecision(2)
              << "Total through pointer: " << pointer->total() << '\n';
    std::cout << "Total through reference: " << reference.total() << '\n';

    Cart* dynamicCart = new Cart;            // dynamic allocation
    dynamicCart->add("Milk", 50);
    std::cout << "Dynamic cart total: " << dynamicCart->total() << '\n';
    delete dynamicCart;

    Cart* customers[3] = {new Cart, new Cart, new Cart};
    customers[0]->add("A", 100);
    customers[1]->add("B", 250);
    customers[2]->add("C", 180);
    int best = 0;
    for (int i = 1; i < 3; ++i)
        if (customers[i]->total() > customers[best]->total()) best = i;
    std::cout << "Highest cart total: " << customers[best]->total() << '\n';
    for (Cart* customer : customers) delete customer;
}