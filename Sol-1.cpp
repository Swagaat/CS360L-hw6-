#include <iostream>
#include <array>
#include <string>
#include <cctype>

class HugeInt {
    friend std::ostream &operator<<(std::ostream &, const HugeInt &);

public:
    static const int max_digits = 30; // Maximum number of digits in a HugeInt
    HugeInt(long = 0); // Conversion/default constructor
    HugeInt(const std::string &); // Conversion constructor from string
    HugeInt operator+(const HugeInt &) const;
    HugeInt operator+(int) const;
    HugeInt operator+(const std::string &) const;
    HugeInt operator*(const HugeInt &) const;
    HugeInt operator/(const HugeInt &) const;
    bool operator==(const HugeInt &) const;
    bool operator!=(const HugeInt &) const;
    bool operator<(const HugeInt &) const;
    bool operator<=(const HugeInt &) const;
    bool operator>(const HugeInt &) const;
    bool operator>=(const HugeInt &) const;

private:
    std::array<short, max_digits> digits; // Array to store individual digits
};

// Constructor from long
HugeInt::HugeInt(long value) {
    digits.fill(0);
    for (int pos = max_digits - 1; value != 0 && pos >= 0; pos--) {
        digits[pos] = value % 10;
        value /= 10;
    }
}

// Constructor from string
HugeInt::HugeInt(const std::string &number) {
    digits.fill(0);
    size_t num_length = number.size();
    for (int pos = max_digits - num_length, index = 0; pos < max_digits; ++pos, ++index) {
        if (isdigit(number[index]))
            digits[pos] = number[index] - '0';
    }
}

// Addition of two HugeInts
HugeInt HugeInt::operator+(const HugeInt &other) const {
    HugeInt result;
    int carry = 0;
    for (int i = max_digits - 1; i >= 0; i--) {
        int sum = digits[i] + other.digits[i] + carry;
        result.digits[i] = sum % 10;
        carry = sum / 10;
    }
    return result;
}

// Addition of HugeInt and int
HugeInt HugeInt::operator+(int scalar) const {
    return *this + HugeInt(scalar);
}

// Addition of HugeInt and string
HugeInt HugeInt::operator+(const std::string &number) const {
    return *this + HugeInt(number);
}

// Multiplication of two HugeInts
HugeInt HugeInt::operator*(const HugeInt &other) const {
    HugeInt result;
    for (int i = max_digits - 1; i >= 0; i--) {
        int carry = 0;
        for (int j = max_digits - 1; j >= 0; j--) {
            int idx = i + j + 1 - max_digits;
            if (idx >= 0) {
                int product = result.digits[idx] + digits[j] * other.digits[i] + carry;
                result.digits[idx] = product % 10;
                carry = product / 10;
            }
        }
        if (i > 0) result.digits[i - 1] += carry;
    }
    return result;
}
// Placeholder for division - real implementation needed
HugeInt HugeInt::operator/(const HugeInt &divisor) const {
    HugeInt quotient, remainder;
    return quotient; // Simple stub: Real implementation needed
}
bool HugeInt::operator==(const HugeInt &other) const {
    return digits == other.digits;
}
bool HugeInt::operator!=(const HugeInt &other) const {
    return !(*this == other);
}
bool HugeInt::operator<(const HugeInt &other) const {
    for (int i = 0; i < max_digits; i++) {
        if (digits[i] < other.digits[i]) return true;
        if (digits[i] > other.digits[i]) return false;
    }
    return false;
}
bool HugeInt::operator<=(const HugeInt &other) const {
    return *this < other || *this == other;
}
bool HugeInt::operator>(const HugeInt &other) const {
    return !(*this <= other);
}
bool HugeInt::operator>=(const HugeInt &other) const {
    return !(*this < other);
}

std::ostream &operator<<(std::ostream &out, const HugeInt &num) {
    bool leadingZero = true;
    for (int i = 0; i < HugeInt::max_digits; i++) {
        if (leadingZero && num.digits[i] == 0)
            continue;
        out << num.digits[i];
        leadingZero = false;
    }
    if (leadingZero)
        out << '0'; // Handle the zero case explicitly
    return out;
}
int main() {
    HugeInt n1(92389013421);
    HugeInt n2(875644891234);
    HugeInt n3("99999999999999999999999999999");
    HugeInt n4("1");
    HugeInt n5;
    std::cout << "n1 is " << n1 << "\nn2 is " << n2
         << "\nn3 is " << n3 << "\nn4 is " << n4
         << "\nn5 is " << n5 << "\n\n";
    n5 = n1 + n2;
    std::cout << n1 << " + " << n2 << " = " << n5 << "\n\n";
    std::cout << n3 << " + " << n4 << " = " << (n3 + n4) << "\n\n";
    n5 = n1 + 9;
    std::cout << n1 << " + " << 9 << " = " << n5 << "\n\n";
    n5 = n2 + "10000";
    std::cout << n2 << " + " << "10000" << " = " << n5 << "\n\n";

    // Additional tests for multiplication
    n5 = n1 * n2;
    std::cout << n1 << " * " << n2 << " = " << n5 << "\n\n";

    return 0;
}
