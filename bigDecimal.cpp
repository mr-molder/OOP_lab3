//
// Created by santas_molderras on 09.10.22.
//
#include "bigDecimal.h"
#include <memory>
#include <cstring>

namespace Lab3 {

    BigDecimal::BigDecimal() {
        for (int i = 0; i < SIZE; ++i) {
            digits[i] = '0';
        }
    }

    BigDecimal::BigDecimal(const char *number): BigDecimal{} {
        if(number[0] == '-') {
            sign = '-';
            number++;
        }

        int len = std::strlen(number);

        for (int i = len - 1; i >= 0; --i) {
            digits[len - i - 1] = number[i];
        }

    }

    BigDecimal::BigDecimal(long long number): BigDecimal{} {
        if(number < 0) {
            sign = '-';
        }

        int digit;
        for (int i = 0; number; ++i) {
            digit = number % 10;
            if (digit < 0)
                digit = -digit;
            number = number / 10;
            digits[i] = digit + '0';
        }

    }

    BigDecimal& BigDecimal::operator+= (const BigDecimal& right) {

        BigDecimal newLeft = *this;
        BigDecimal newRight = right;
        if (newLeft.sign == '-') newLeft = newLeft.complement().add(1);
        if (newRight.sign == '-') newRight = newRight.complement().add(1);
        newLeft.add(newRight);
        newLeft.sign = '+';
        if (newLeft.digits[SIZE-1] > '4') {

            newLeft = newLeft.complement().add(1);
            newLeft.sign = '-';
        }

        *this = newLeft;
        return *this;
    }

    BigDecimal BigDecimal::operator- () const {
        BigDecimal negative = *this;
        negative.sign = negative.sign == '+' ? '-':'+';
        return negative;
    }

    char BigDecimal::addDigits(char left, char right, int& carry){
        int sumDigit = left - '0' + right - '0' + carry;
        char sumChar = sumDigit % 10 + '0';
        carry = sumDigit / 10;
        return sumChar;
    }

    BigDecimal BigDecimal::complement() const{
        BigDecimal c;
        for (int i = 0; i < SIZE; ++i) {
            c.digits[i] = '9' - digits[i] + '0';
        }
        return c;
    }

    BigDecimal& BigDecimal::add(const BigDecimal& right) {
        int carry = 0;
        for (int i = 0; i < SIZE; ++i) {
            digits[i] = addDigits(digits[i], right.digits[i], carry);
        }
        return *this;
    }

    BigDecimal operator+ (const BigDecimal& left, const BigDecimal& right) {
        BigDecimal sum = left;
        sum+=right;

        return sum;
    }

    BigDecimal operator- (const BigDecimal& left, const BigDecimal& right) {
        return left + (-right);
    }

    BigDecimal& BigDecimal::divideTen() {
        for (int i = 0; i < SIZE - 1; ++i) {
            digits[i] = digits[i + 1];
        }
        digits[SIZE - 1] = '0';
        return *this;
    }

    BigDecimal& BigDecimal::timesTen() {
        for (int i = SIZE - 1; i > 0; --i) {
            digits[i] = digits[i - 1];
        }
        digits[0] = '0';
        return *this;
    }

    std::ostream& operator<< (std::ostream& stream, const BigDecimal& number) {

        if (number.sign == '-') stream << number.sign;

        int i = BigDecimal::SIZE  - 1;

        while(i > 0 && number.digits[i] == '0')  i--;
        for (; i >= 0; --i) {
            stream << number.digits[i];
        }
        return stream;
    }

    std::istream& operator>> (std::istream& stream, BigDecimal& number) {
        char symbol;
        char sign = '+';
        stream >> std::ws;
        symbol = stream.get();
        if (symbol == '-' || symbol == '+')
           sign = symbol;
        else if (symbol != ' '){
            stream.unget();
        }
        while (stream) {
            symbol = stream.get();
            if (!std::isdigit(symbol)) {
                stream.unget();
                break;
            }
            number.timesTen();
            number += symbol - '0';
        }
        number.sign = sign;
        return stream;
    }

    BigDecimal BigDecimal::complement_digits() const {
        BigDecimal comp = complement();
        comp.sign = '+';
        return comp;
    }
}