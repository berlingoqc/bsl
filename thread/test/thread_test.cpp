
#define CATCH_CONFIG_MAIN


#include <catch2/catch.hpp>

unsigned int Factorial( unsigned int number ) {
    return number <= 1 ? number : Factorial(number-1)*number;
}




TEST_CASE( "Factorials are computed", "[factorial]" ) {
    REQUIRE(Factorial(1) == 1);
}