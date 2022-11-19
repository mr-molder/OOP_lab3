//
// Created by  on 31.10.2022.
//

#include "bigDecimal.h"

namespace Lab3 {

    BigDecimal::Arithmetics::Arithmetics() {
        length = 1;
        digits = new char[length];
    }

    BigDecimal::Arithmetics::Arithmetics(const BigDecimal& number) { // проверить правильность инициализации @@@
        length = number.length + 1;
        digits = new char[length];
        //Arithmetics uno = one();
        int i = 0;
        for (; i < number.length; ++i) {
            digits[i] = number.digits[i];
        }
        digits[i] = '0';

        if (number.sign == '-') {
            for (int i = 0; i <= length; ++i) {
                digits[i] = '9' - digits[i] + '0';
            }
            addOne();
        }
    }

    BigDecimal::Arithmetics::~Arithmetics() {
        delete [] digits;
        digits = nullptr;
    }

    void BigDecimal::Arithmetics::extend(int add_size) {
        char *old_digits = digits;
        digits = new char[length + add_size];
        int i = 0;
        for (; i < length; ++i) {
            digits[i] = old_digits[i];
        }
        for (; i < length + add_size; ++i) {
            if (digits[i - 1] >= '5')
                digits[i] = '9';
            else
                digits[i] = '0';
        }
        length += add_size;
        delete [] old_digits;
    }

    BigDecimal BigDecimal::Arithmetics::toNum() {
        char other_sign = '+';
        //Arithmetics uno = one();
        if (digits[length - 1] > '4') {
            other_sign = '-';
            for (int i = 0; i < length; ++i) {
                digits[i] = '9' - digits[i] + '0';
            }
            addOne();
        }
        for (int j = 0, k = length- 1; j < k; ++j, --k) {
            std::swap(digits[j], digits[k]);
        }

        extend(1);
        char *str = digits;
        while (*(++str) == '0'); //skip leading zeroes
        digits[length - 1] = '\0';
        BigDecimal result(str);
        result.sign = other_sign;
        return result;
    }

    BigDecimal::Arithmetics& BigDecimal::Arithmetics::add(Arithmetics& right) {
        int carry = 0;
        int new_len = std::max(this->length, right.length);
        this->extend(new_len - length);
        right.extend(new_len - right.length);
        int i = 0;
        for (; i < length; ++i) {
            digits[i] = addDigits(digits[i], right.digits[i], carry);
        }
//        digits[i] = carry + '0';
        return *this;
    }

    char BigDecimal::Arithmetics::addDigits(char left, char right, int& carry){
        int sumDigit = left - '0' + right - '0' + carry;
        char sumChar = sumDigit % 10 + '0';
        carry = sumDigit / 10;
        return sumChar;
    }

    BigDecimal::Arithmetics BigDecimal::Arithmetics::one() {
        Arithmetics uno;
        uno.digits[0] = '1';
        return uno;
    }

    void BigDecimal::Arithmetics::addOne() {
        int carry = 1;
        int i = 0;
        for (; i < length; ++i) {
            digits[i] = addDigits(digits[i], '0', carry);
        }
//        digits[i] = carry + '0';
    }
}
