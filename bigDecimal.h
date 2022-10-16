//
// Created by santas_molderras on 09.10.22.
//

#ifndef LAB3_BIGDECIMAL_H
#define LAB3_BIGDECIMAL_H

#include <istream>

namespace Lab3 {

    class BigDecimal{
    private:
        static const int SIZE = 50;
        char digits[SIZE];
        char sign = '+';
        BigDecimal complement() const;
        static char addDigits(char left, char right, int& carry);
        BigDecimal& add(const BigDecimal& right); //add numbers in 10's complement
    public:
        BigDecimal();
        BigDecimal(long long);
        BigDecimal(const char*);

        BigDecimal& operator+= (const BigDecimal& right);
        BigDecimal operator- () const;
        friend BigDecimal operator+ (const BigDecimal& left, const BigDecimal& right);
        friend BigDecimal operator- (const BigDecimal& left, const BigDecimal& right);


        BigDecimal& divideTen();
        BigDecimal& timesTen();

        friend std::ostream& operator<< (std::ostream& stream, const BigDecimal& number);
        friend std::istream& operator>> (std::istream& stream, BigDecimal& number);

        BigDecimal complement_digits() const;
    };

}

#endif //LAB3_BIGDECIMAL_H
