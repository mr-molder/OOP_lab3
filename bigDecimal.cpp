//
// Created by santas_molderras on 09.10.22.
//
#include "bigDecimal.h"
#include <memory>
#include <cstring>

namespace Lab3 {

    BigDecimal::BigDecimal() {
        length = MIN_SIZE;
        digits = new char[length];
        for (int i = 0; i < length; ++i) {
            digits[i] = '0';
        }
    }

    BigDecimal& BigDecimal::operator= (const Lab3::BigDecimal &right) {
        if (&right == this) return *this;
        if (this->length > right.length) {
            this->shrink(length - right.length);
        }
        if (this->length < right.length) {
            this->extend(right.length - length);
        }

        for (int i = 0; i < length; i++) {
            digits[i] = right.digits[i];
        }
        sign = right.sign;
        return *this;
    }

    BigDecimal::BigDecimal(const BigDecimal &right) : BigDecimal{} {
        *this = right;
    }

    BigDecimal::~BigDecimal() {
        delete [] digits;
        digits = nullptr;
    }

    BigDecimal::BigDecimal(const char *number): BigDecimal{} {
        if(number[0] == '-') {
            sign = '-';
            number++;
        }

        int len = std::strlen(number);

        extend(len);

        for (int i = len - 1; i >= 0; --i) {
            digits[len - i - 1] = number[i];
        }
        delete_zeroes();

    }

    BigDecimal::BigDecimal(long long number): BigDecimal{} {
        if(number < 0) {
            sign = '-';
        }

        extend(19);

        int digit;
        for (int i = 0; number; ++i) {
            digit = number % 10;
            if (digit < 0)
                digit = -digit;
            number = number / 10;
            digits[i] = digit + '0';
        }

        delete_zeroes();

    }

    BigDecimal& BigDecimal::operator+= (const BigDecimal& other) {
        Arithmetics left = *this;
        Arithmetics right = other;
        left.add(right);

        *this = left.toNum();
        delete_zeroes();
        return *this;
    }

    BigDecimal BigDecimal::operator- () const {
        BigDecimal negative = *this;
        negative.sign = negative.sign == '+' ? '-':'+';
        return negative;
    }

//    char BigDecimal::addDigits(char left, char right, int& carry){
//        int sumDigit = left - '0' + right - '0' + carry;
//        char sumChar = sumDigit % 10 + '0';
//        carry = sumDigit / 10;
//        return sumChar;
//    }

    BigDecimal BigDecimal::complement() const{
        BigDecimal c(*this);
        for (int i = 0; i < length; ++i) {
            c.digits[i] = '9' - digits[i] + '0';
        }
        return c;
    }

//    BigDecimal& BigDecimal::add(const BigDecimal& right) {
//        int carry = 0;
//        for (int i = 0; i < length; ++i) {
//            digits[i] = addDigits(digits[i], right.digits[i], carry);
//        }
//        return *this;
//    }

    BigDecimal operator+ (const BigDecimal& left, const BigDecimal& right) {
        BigDecimal sum = left;
        sum+=right;

        return sum;
    }

    BigDecimal operator- (const BigDecimal& left, const BigDecimal& right) {
        return left + (-right);
    }

    BigDecimal& BigDecimal::divideTen() {
        for (int i = 0; i < length - 1; ++i) {
            digits[i] = digits[i + 1];
        }
        digits[length - 1] = '0';
        return *this;
    }

    BigDecimal& BigDecimal::timesTen() {
        for (int i = length - 1; i > 0; --i) {
            digits[i] = digits[i - 1];
        }
        digits[0] = '0';
        return *this;
    }

    std::ostream& operator<< (std::ostream& stream, const BigDecimal& number) {

        if (number.sign == '-') stream << number.sign;

        int i = number.length  - 1;

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

    void BigDecimal::extend(int add_size) {
        char *old_digits = digits;
        digits = new char[length + add_size];
        int i = 0;
        for (; i < length; ++i) {
            digits[i] = old_digits[i];
        }
        for (; i < length + add_size; ++i) {
            digits[i] = '0';
        }
        length += add_size;
        delete [] old_digits;
    }

    void BigDecimal::shrink(int cut_size) {
        if (cut_size == 0) return;
        char *old_digits = digits;
        digits = new char[length - cut_size];
        int i = 0;
        for (; i < length - cut_size; ++i) {
            digits[i] = old_digits[i];
        }
        length -= cut_size;
        delete [] old_digits;
    }

    void BigDecimal::delete_zeroes() {
        int counter = length;
        int cut_size = 0;
        for (; counter > 1 && digits[counter] == '0'; --counter, ++cut_size);
        shrink(cut_size);
    }
}