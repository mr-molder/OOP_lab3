#include <gtest/gtest.h>
#include "../bigDecimal.h"


TEST(BigDecimalConstructor, ConstructorWithArguments)
{
Lab3::BigDecimal a(12345678);
    ASSERT_EQ(8, a.length);
    Lab2::BigDecimal a("12345678");
    ASSERT_EQ(8, a.length);

}

TEST(AriphmeticsConstructor, ConstructorWithArguments)
{

lab3::BigDecimal::Ariphmetics b("12345678");
    ASSERT_EQ(8, b.length);
}

TEST(BigDecimalConstructor, InitConstructors)
{
Lab3::BigDecimal a(12345678);
lab3::BigDecimal::Ariphmetics b(a);
ASSERT_EQ(8, b.length);
}


TEST(BigDecimalMethods, Add)
{
Lab3::BigDecimal a(12345678);
Lab3::BigDecimal b(87654321);
Lab3::BigDecimal c(99999999);
a += b;
ASSERT_EQ(c.digits, a.digits);
}

TEST(BigDecimalMethods, Minus)
{
Lab3::BigDecimal a(12345678);
Lab3::BigDecimal b(87654321);
Lab3::BigDecimal c(99999999);
c = c - b;
ASSERT_EQ(c.digits, a.digits);
}

int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
