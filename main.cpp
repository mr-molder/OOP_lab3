#include <iostream>
#include "bigDecimal.h"

int main() {
    Lab3::BigDecimal first('123456');
    Lab3::BigDecimal second('654321');
//    second = -second;

//    std::cout << Lab3::BigDecimal() << '\n';
//    std::cout << Lab3::BigDecimal(123) << '\n';
//    std::cout << Lab3::BigDecimal("123") << '\n';
//    std::cout << Lab3::BigDecimal(-123) << '\n';
//    std::cout << Lab3::BigDecimal("-123") << '\n';

//    std::cout << "Print first and second digit:" << '\n';
//    std::cin >> first >> second;
    std::cout << "first + second: " << first + second << '\n';
    std::cout << "first - second: " << first - second << '\n';
    std::cout << "first * 10: " << first.timesTen() << '\n';
    std::cout << "second / 10: " << second.divideTen() << '\n';
    std::cout << "second in complement: " << second.complement_digits() << '\n';

    return 0;
}
