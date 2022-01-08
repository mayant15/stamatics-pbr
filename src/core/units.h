#pragma once

#include "base.h"

namespace pbr::dims
{
    template <
        int Length,
        int Time,
        int Mass,
        int Current,
        int Temperature,
        int Angle, // instead of Amount
        int LuminousIntensity
    >
    struct Dimensions
    {
        static constexpr int length = Length;
        static constexpr int time = Time;
        static constexpr int mass = Mass;
        static constexpr int current = Current;
        static constexpr int temperature = Temperature;
        static constexpr int angle = Angle;
        static constexpr int luminous_intensity = LuminousIntensity;

        template <class Other>
        using multiply = Dimensions<
            length + Other::length,
            time + Other::time,
            mass + Other::mass,
            current + Other::current,
            temperature + Other::temperature,
            angle + Other::angle,
            luminous_intensity + Other::luminous_intensity
        >;

        template <class Other>
        using divide = Dimensions<
            length - Other::length,
            time - Other::time,
            mass - Other::mass,
            current - Other::current,
            temperature - Other::temperature,
            angle - Other::angle,
            luminous_intensity - Other::luminous_intensity
        >;
    };

    // Base dimensions
    using Scalar = Dimensions<0, 0, 0, 0, 0, 0, 0>;
    using Length = Dimensions<1, 0, 0, 0, 0, 0, 0>;
    using Time = Dimensions<0, 1, 0, 0, 0, 0, 0>;
    using Mass = Dimensions<0, 0, 1, 0, 0, 0, 0>;
    using Current = Dimensions<0, 0, 0, 1, 0, 0, 0>;
    using Temperature = Dimensions<0, 0, 0, 0, 1, 0, 0>;
    using Angle = Dimensions<0, 0, 0, 0, 0, 1, 0>;
    using LuminousIntensity = Dimensions<0, 0, 0, 0, 0, 0, 1>;

    // Derived dimensions
    using Area = Dimensions<2, 0, 0, 0, 0, 0, 0>;
    using Volume = Dimensions<3, 0, 0, 0, 0, 0, 0>;
    using Speed = Dimensions<1, -1, 0, 0, 0, 0, 0>;

    template <typename T, typename U>
    constexpr bool assert_eq()
    {
        return std::is_same<typename T::dimensions, typename U::dimensions>::value;
    }

    template <class T, class U>
    constexpr bool decay_eq()
    {
        return std::is_same<
            typename std::decay<T>::type::dimensions,
            typename std::decay<U>::type::dimensions
        >::value;
    };
}

namespace pbr
{
    template <class T>
    struct Number
    {
        double m_data;
        
        using dimensions = T;

        template <class OtherDims>
        decltype(auto) operator*(Number<OtherDims> other)
        {
            return Number<typename dimensions::template multiply<OtherDims>> { m_data * other.m_data };
        }

        template <class OtherDims>
        decltype(auto) operator+(Number<OtherDims> other)
        {
            static_assert(std::is_same<dimensions, OtherDims>::value);
            return Number<dimensions> { m_data + other.m_data };
        }

        template <class OtherDims>
        decltype(auto) operator-(Number<OtherDims> other)
        {
            static_assert(std::is_same<dimensions, OtherDims>::value);
            return Number<dimensions> { m_data - other.m_data };
        }

        template <class OtherDims>
        decltype(auto) operator/(Number<OtherDims> other)
        {
            return Number<typename dimensions::template divide<OtherDims>> { m_data / other.m_data };
        }

        template <class OtherDims>
        decltype(auto) operator=(const Number<OtherDims>& other)
        {
            static_assert(std::is_same<dimensions, OtherDims>::value);
            m_data = other.m_data;
            return *this;
        }

        // This one is constexpr becuase naked primitives should only be present as literals,
        // which are available at compile time.
        constexpr bool operator==(double other)
        {
            return m_data == other;
        }

        template <class OtherDims>
        bool operator==(const Number<OtherDims>& other)
        {
            static_assert(std::is_same<dimensions, OtherDims>::value);
            return m_data == other.m_data;
        }

        constexpr bool operator!=(double other)
        {
            return !(*this == other);
        }

        template <class OtherDims>
        bool operator!=(const Number<OtherDims>& other)
        {
            return !(*this == other);
        }

        constexpr friend bool operator<(const Number& lhs, double rhs)
        {
            return lhs.m_data < rhs;
        }

        constexpr friend bool operator<(double lhs, const Number& rhs)
        {
            return lhs < rhs.m_data;
        }

        friend bool operator<(const Number& lhs, const Number& rhs)
        {
            static_assert(dims::decay_eq<decltype(lhs), decltype(rhs)>());
            return lhs.m_data < rhs.m_data;
        }

        constexpr friend bool operator>(const Number& lhs, double rhs)
        {
            return rhs < lhs;
        }

        friend bool operator>(const Number& lhs, const Number& rhs)
        {
            return rhs < lhs;
        }

        constexpr friend bool operator<=(const Number& lhs, double rhs)
        {
            return !(lhs > rhs);
        }

        friend bool operator<=(const Number& lhs, const Number& rhs)
        {
            return !(lhs > rhs);
        }

        constexpr friend bool operator>=(const Number& lhs, double rhs)
        {
            return !(lhs < rhs);
        }

        friend bool operator>=(const Number& lhs, const Number& rhs)
        {
            return !(lhs < rhs);
        }

        Number(double data = 0) : m_data(data) {}
    };

    // Quantities using those dimensions
    using Scalar = Number<dims::Scalar>;
    using Length = Number<dims::Length>;
    using Time = Number<dims::Time>;
    using Speed = Number<dims::Speed>;
    using Acceleration = Number<dims::Speed::divide<dims::Time>>;
    using Force = Number<dims::Mass::multiply<Acceleration::dimensions>>;
    using Energy = Number<Force::dimensions::multiply<dims::Length>>;
    using Power = Number<Energy::dimensions::divide<dims::Time>>;
    using Intensity = Number<Power::dimensions::divide<dims::Area>>;
}
