#include <iostream>
class Complex {
public:
    explicit Complex(double = 0.0, double = 0.0);
    Complex operator+(const Complex&) const;
    Complex operator-(const Complex&) const;
    Complex operator*(const Complex&) const;
    bool operator==(const Complex&) const;
    bool operator!=(const Complex&) const;

    friend std::ostream& operator<<(std::ostream&, const Complex&);
    friend std::istream& operator>>(std::istream&, Complex&);

private:
    double real;
    double imaginary;
};

Complex::Complex(double realPart, double imaginaryPart)
    : real(realPart), imaginary(imaginaryPart) {}

Complex Complex::operator+(const Complex& operand2) const {
    return Complex(real + operand2.real, imaginary + operand2.imaginary);
}

Complex Complex::operator-(const Complex& operand2) const {
    return Complex(real - operand2.real, imaginary - operand2.imaginary);
}

Complex Complex::operator*(const Complex& operand2) const {
    return Complex(real * operand2.real - imaginary * operand2.imaginary,
                   real * operand2.imaginary + imaginary * operand2.real);
}

bool Complex::operator==(const Complex& operand2) const {
    return (real == operand2.real) && (imaginary == operand2.imaginary);
}

bool Complex::operator!=(const Complex& operand2) const {
    return !(*this == operand2);
}

std::ostream& operator<<(std::ostream& os, const Complex& c) {
    os << '(' << c.real << ", " << c.imaginary << 'i' << ')';
    return os;
}

std::istream& operator>>(std::istream& is, Complex& c) {
    is >> c.real >> c.imaginary;
    return is;
}

int main() {
    Complex x, y, z;
    std::cout << "Enter the real and imaginary parts of complex number y: ";
    std::cin >> y;
    std::cout << "Enter the real and imaginary parts of complex number z: ";
    std::cin >> z;
    std::cout << "\ny: " << y;
    std::cout << "\nz: " << z;
    x = y + z;
    std::cout << "\n\nx = y + z: " << x;

    x = y - z;
    std::cout << "\n\nx = y - z: " << x;

    x = y * z;
    std::cout << "\n\nx = y * z: " << x;

    std::cout << "\n\nComparing y and z:";

    if (y == z) {
        std::cout << "\ny and z are equal.";
    } else {
        std::cout << "\ny and z are not equal.";
    }

    return 0;
}
