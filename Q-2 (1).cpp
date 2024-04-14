// Hugeint.h
// HugeInt class definition.
#ifndef HUGEINT_H
#define HUGEINT_H

#include <array>
#include <iostream>
#include <string>

class HugeInt {
    friend std::ostream& operator<<(std::ostream&, const HugeInt&);

public:
    static const int digits = 30;  // maximum digits in a HugeInt

    HugeInt(long = 0);  // conversion/default constructor
    HugeInt(const std::string&);  // conversion constructor

    // arithmetic operators
    HugeInt operator+(const HugeInt&) const;
    HugeInt operator+(int) const;
    HugeInt operator+(const std::string&) const;

    HugeInt operator*(const HugeInt&) const;  // multiplication operator
    HugeInt operator/(const HugeInt&) const;  // division operator

    // relational and equality operators
    bool operator==(const HugeInt&) const;
    bool operator!=(const HugeInt&) const;
    bool operator<(const HugeInt&) const;
    bool operator>(const HugeInt&) const;
    bool operator<=(const HugeInt&) const;
    bool operator>=(const HugeInt&) const;

private:
    std::array<short, digits> integer;
};

#endif // HUGEINT_H

// Hugeint.cpp
// HugeInt member-function and friend-function definitions.
#include <cctype>
#include "Hugeint.h"

// default constructor; conversion constructor that converts
// a long integer into a HugeInt object
HugeInt::HugeInt(long value) {
    for (short& element : integer)
        element = 0;

    for (size_t j = digits - 1; value != 0 && j >= 0; j--) {
        integer[j] = value % 10;
        value /= 10;
    }
}

// conversion constructor that converts a character string
// representing a large integer into a HugeInt object
HugeInt::HugeInt(const std::string& number) {
    for (short& element : integer)
        element = 0;

    size_t length = number.size();
    for (size_t j = digits - length, k = 0; j < digits; ++j, ++k)
        if (isdigit(number[k]))
            integer[j] = number[k] - '0';
}

// addition operator; HugeInt + HugeInt
HugeInt HugeInt::operator+(const HugeInt& op2) const {
    HugeInt temp;
    int carry = 0;

    for (int i = digits - 1; i >= 0; i--) {
        temp.integer[i] = integer[i] + op2.integer[i] + carry;
        if (temp.integer[i] > 9) {
            temp.integer[i] %= 10;
            carry = 1;
        } else {
            carry = 0;
        }
    }

    return temp;
}

// addition operator; HugeInt + int
HugeInt HugeInt::operator+(int op2) const {
    return *this + HugeInt(op2);
}

// addition operator; HugeInt + string
HugeInt HugeInt::operator+(const std::string& op2) const {
    return *this + HugeInt(op2);
}

// multiplication operator; HugeInt * HugeInt
HugeInt HugeInt::operator*(const HugeInt& op2) const {
    HugeInt temp;
    HugeInt result;
    int carry = 0;

    for (int i = digits - 1; i >= 0; i--) {
        for (int j = digits - 1; j >= 0; j--) {
            int product = integer[i] * op2.integer[j] + carry + temp.integer[i + j + 1];
            temp.integer[i + j + 1] = product % 10;
            carry = product / 10;
        }
    }

    return temp;
}

// division operator; HugeInt / HugeInt
HugeInt HugeInt::operator/(const HugeInt& op2) const {
    HugeInt quotient;
    HugeInt remainder = *this;
    HugeInt zero("0");

    if (op2 == zero) {
        std::cerr << "Error: Division by zero\n";
        return quotient;
    }

    while (remainder >= op2) {
        remainder = remainder - op2;
        ++quotient;
    }

    return quotient;
}

// equality operator; HugeInt == HugeInt
bool HugeInt::operator==(const HugeInt& op2) const {
    for (int i = 0; i < digits; ++i) {
        if (integer[i] != op2.integer[i]) {
            return false;
        }
    }
    return true;
}

// inequality operator; HugeInt != HugeInt
bool HugeInt::operator!=(const HugeInt& op2) const {
    return !(*this == op2);
}

// less than operator; HugeInt < HugeInt
bool HugeInt::operator<(const HugeInt& op2) const {
    for (int i = 0; i < digits; ++i) {
        if (integer[i] < op2.integer[i]) {
            return true;
        }
        if (integer[i] > op2.integer[i]) {
            return false;
        }
    }
    return false;
}

// greater than operator; HugeInt > HugeInt
bool HugeInt::operator>(const HugeInt& op2) const {
    return op2 < *this;
}

// less than or equal to operator; HugeInt <= HugeInt
bool HugeInt::operator<=(const HugeInt& op2) const {
    return !(*this > op2);
}

// greater than or equal to operator; HugeInt >= HugeInt
bool HugeInt::operator>=(const HugeInt& op2) const {
    return !(*this < op2);
}

// overloaded output operator
std::ostream& operator<<(std::ostream& output, const HugeInt& num) {
    int i;
    for (i = 0; (i < HugeInt::digits) && (0 == num.integer[i]); ++i)
        ;  // skip leading zeros

    if (i == HugeInt::digits) {
        output << 0;
    } else {
        for (; i < HugeInt::digits; ++i)
            output << num.integer[i];
    }
    return output;
}

// main.cpp
// HugeInt test program.
#include <iostream>
#include "Hugeint.h"

int main() {
    HugeInt n1(7654321);
    HugeInt n2(7891234);
    HugeInt n3("99999999999999999999999999999");
    HugeInt n4("1");
    HugeInt n5;

    std::cout << "n1 is " << n1 << "\nn2 is " << n2
              << "\nn3 is " << n3 << "\nn4 is " << n4
              << "\nn5 is " << n5 << "\n\n";

    n5 = n1 + n2;
    std::cout << n1 << " + " << n2 << " = " << n5 << "\n\n";

    std::cout << n3 << " + " << n4 << "\n= " << (n3 + n4) << "\n\n";

    n5 = n1 + 9;
    std::cout << n1 << " + " << 9 << " = " << n5 << "\n\n";

    n5 = n2 + "10000";
    std::cout << n2 << " + " << "10000" << " = " << n5 << std::endl;

    n5 = n1 * n2;
    std::cout << n1 << " * " << n2 << " = " << n5 << "\n\n";

    n5 = n3 / n4;
    std::cout << n3 << " / " << n4 << " = " << n5 << std::endl;

    return 0;
}
