//
// Created by santas_molderras on 09.10.22.
//

#ifndef LAB3_BIGDECIMAL_H
#define LAB3_BIGDECIMAL_H

#include <istream>

namespace Lab3 {

    class BigDecimal{
    private:
        static const int MIN_SIZE = 1;
        int length;
        //char digits[MIN_SIZE];
        char *digits = nullptr;
        char sign = '+';
        BigDecimal complement() const;
        //static char addDigits(char left, char right, int& carry);
        //BigDecimal& add(const BigDecimal& right); //add numbers in 10's complement
        void extend(int add_size=1);
        void shrink(int cut_size=1);
        void delete_zeroes();
        class Arithmetics{
        private:
            char *digits;
            int length;
        public:
            Arithmetics();
            Arithmetics(const BigDecimal&);
            Arithmetics& add(Arithmetics& right);
            void extend(int add_size=1);
            ~Arithmetics();
            BigDecimal toNum();
            static char addDigits(char left, char right, int& carry);
            Arithmetics one();
            void addOne();
        };
    public:
        BigDecimal();
        BigDecimal(long long);
        BigDecimal(const char*);

        BigDecimal(const BigDecimal &);
        BigDecimal& operator= (const BigDecimal &);

        BigDecimal& operator+= (const BigDecimal& right);
        BigDecimal operator- () const;
        friend BigDecimal operator+ (const BigDecimal& left, const BigDecimal& right);
        friend BigDecimal operator- (const BigDecimal& left, const BigDecimal& right);


        BigDecimal& divideTen();
        BigDecimal& timesTen();

        friend std::ostream& operator<< (std::ostream& stream, const BigDecimal& number);
        friend std::istream& operator>> (std::istream& stream, BigDecimal& number);

        BigDecimal complement_digits() const;

        ~BigDecimal();
    };

}

#endif //LAB3_BIGDECIMAL_H