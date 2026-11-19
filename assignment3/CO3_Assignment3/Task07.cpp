#include <cmath>
#include <iostream>
#include <stdexcept>

class Complex {
    double real, imag;

public:
    Complex() : real(0.0), imag(0.0) {}
    Complex(double r) : real(r), imag(0.0) {}
    Complex(double r, double i) : real(r), imag(i) {}

    Complex operator+(const Complex& z) const {
        return Complex(real + z.real, imag + z.imag);
    }
    Complex operator-(const Complex& z) const {
        return Complex(real - z.real, imag - z.imag);
    }
    Complex operator*(const Complex& z) const {
        return Complex(real * z.real - imag * z.imag,
                       real * z.imag + imag * z.real);
    }
    Complex operator/(const Complex& z) const {
        double denominator = z.real * z.real + z.imag * z.imag;
        if (denominator == 0.0) throw std::domain_error("Division by zero impedance");
        return Complex((real * z.real + imag * z.imag) / denominator,
                       (imag * z.real - real * z.imag) / denominator);
    }
    bool operator==(const Complex& z) const {
        const double eps = 1e-9;
        return std::fabs(real - z.real) < eps && std::fabs(imag - z.imag) < eps;
    }
    double magnitude() const { return std::sqrt(real * real + imag * imag); }

    friend std::ostream& operator<<(std::ostream& out, const Complex& z) {
        out << z.real;
        if (z.imag >= 0) out << " + j" << z.imag;
        else out << " - j" << -z.imag;
        return out;
    }
};

int main() {
    // Example series and parallel impedances
    Complex resistor(10.0, 0.0);
    Complex inductor(0.0, 5.0);
    Complex capacitor(0.0, -2.0);

    Complex series = resistor + inductor + capacitor;
    std::cout << "Series impedance: " << series << '\n';
    std::cout << "Series magnitude: " << series.magnitude() << '\n';

    Complex z1(10.0, 0.0), z2(0.0, 5.0);
    try {
        Complex parallel = (z1 * z2) / (z1 + z2);
        std::cout << "Parallel impedance: " << parallel << '\n';
        std::cout << "Parallel magnitude: " << parallel.magnitude() << '\n';
        Complex zero;
        std::cout << (z1 / zero) << '\n';
    } catch (const std::domain_error& e) {
        std::cout << e.what() << '\n';
    }
    return 0;
}
