#include "units.h"

namespace pbr
{
    TEST_CASE("units::Number::compare")
    {
        Length r1 (1.0);
        Length r2 (1.0);
        Length r3 (0.5);

        CHECK(r1 == 1.0);
        CHECK(r2 == 1.0);
        CHECK(r1 == r2);
        CHECK(r2 != r3);
        CHECK_FALSE(r1 < r3);
        CHECK_FALSE(r3 > r1);
        CHECK(r2 < 2.0);
        CHECK(r2 >= r3);
    }

    TEST_CASE("units::Number::multiply")
    {
        Length radius (1.0);
        auto a = radius * radius;
        
        CHECK(std::is_same<decltype(a)::dimensions, dims::Area>::value);
        CHECK(a == 1.0);
    }

    TEST_CASE("units::Number::divide")
    {
        Length radius (2.0);
        auto a = radius / radius;

        Time t (1.0);
        auto s = radius / t;
        
        CHECK(std::is_same<decltype(a)::dimensions, dims::Scalar>::value);
        CHECK(std::is_same<decltype(s)::dimensions, dims::Speed>::value);
        CHECK(a == 1.0);
        CHECK(s == 2.0);
    }

    TEST_CASE("units::Number::add")
    {
        Length radius (1.0);
        auto a = radius + radius;
        
        CHECK(std::is_same<decltype(a)::dimensions, dims::Length>::value);
        CHECK(a == 2.0);
    }

    TEST_CASE("units::Number::subtract")
    {
        Length radius (1.0);
        auto a = radius - radius;
        
        CHECK(std::is_same<decltype(a)::dimensions, dims::Length>::value);
        CHECK(a == 0.0);
    }
}
