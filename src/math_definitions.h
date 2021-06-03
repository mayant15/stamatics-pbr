#pragma once

#include "base.h"
#include "units.h"

///////////////////////////////////////////////////////////////////////////////
// Constants and conversions
///////////////////////////////////////////////////////////////////////////////

#define PBR_PI 3.1415926535897932384626433832795
#define PBR_INF 1e20
#define PBR_EPSILON 1e-4

#define PBR_DEG_TO_RAD(DEG) (DEG * PBR_PI / 180)

///////////////////////////////////////////////////////////////////////////////
// Math types
///////////////////////////////////////////////////////////////////////////////

namespace pbr
{
    template <class Type>
    struct BaseVec
    {
        Type x, y, z;

        BaseVec(Type x_, Type y_, Type z_) : x(x_), y(y_), z(z_) {}
        BaseVec(Type scalar = 0.0) : BaseVec(scalar, scalar, scalar) {}

        inline Type sqlen() const
        {
            return x * x + y * y + z * z;
        }

        inline Type len() const
        {
            return std::sqrt(sqlen());
        }

        inline BaseVec operator*(Type s) const
        {
            return { x * s, y * s, z * s };
        }

        inline BaseVec operator*(const BaseVec& v) const
        {
            return { x * v.x, y * v.y, z * v.z };
        }

        inline BaseVec operator/(Type s) const
        {
            return *this * (1. / s);
        }

        inline BaseVec operator+(const BaseVec& b) const
        {
            return {x + b.x, y + b.y, z + b.z};
        }

        inline BaseVec operator-(const BaseVec& b) const
        {
            return *this + b * (-1.);
        }
    };

    struct Point2D
    {
        double x, y;
        Point2D(double x_ = 0, double y_ = 0) : x(x_), y(y_) {}
    };

    using Vec = BaseVec<double>;

    using Point = Vec;
    using Direction = Vec;

    /** Structure that represents a ray in 3D. */
    struct Ray
    {
        Point origin;
        Direction direction;
    };

    struct Basis
    {
        Vec u, v, w;
    };

    /** Normalize the vector, return a unit vector in the same direction as the parameter. */
    // template <class Dims>
    inline auto normalize(const Vec& v)
    {
        return v / v.len();
    }

    /** Calculate the dot product between vectors a and b. */
    // template <class Dims>
    inline auto dot(const Vec& a, const Vec& b)
    {
        return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
    }

    /** Calculate the cos of the angle between vectors a and b. */
    // template <class Dims>
    inline double cosv(const Vec& a, const Vec& b)
    {
        return dot(normalize(a), normalize(b));
    }

    /** Calculate the cross product between a and b. */
    // template <class Dims>
    inline Vec cross(const Vec& a, const Vec& b)
    {
        return { 
            (a.y * b.z) - (a.z * b.y),
            (a.z * b.x) - (a.x * b.z),
            (a.x * b.y) - (a.y * b.x)
        };
    }

    /** Reflect the incident vector v about a normal n. */
    // template <class Dims>
    inline auto reflect(const Vec& v, const Vec& n)
    {
        return v - n * 2 * cosv(v, n) * v.len();
    }

    /** Clamp a value x between min and max. */
    // template <class Dims>
    inline double clamp(double x, double min = 0, double max = 1)
    {
        return (x < min) ? min : (x > max) ? max : x;
    }

    ///////////////////////////////////////////////////////////////////////////////
    // Random
    ///////////////////////////////////////////////////////////////////////////////

    struct UniformRNG
    {
        inline double sample()
        {
            return dist(gen);
        }

        inline Point2D sample_disk()
        {
            double u1 = sample();
            double u2 = sample();

            return {
                std::sqrt(u1) * std::cos(2 * PBR_PI * u2),
                std::sqrt(u1) * std::sin(2 * PBR_PI * u2)
            };
        }

        inline Vec sample_hemisphere()
        {
            double u1 = sample();
            double u2 = sample();

            double A = std::sqrt(1 - u1 * u1);
            double phi = 2 * PBR_PI * u2;

            return {
                A * std::cos(phi),
                A * std::sin(phi),
                u1
            };
        }

        UniformRNG()
            : dist(0.0, 1.0)
        {
            gen = std::mt19937(rd());
        }

    private:
        std::random_device rd;
        std::mt19937 gen;
        std::uniform_real_distribution<> dist;
    };

    ///////////////////////////////////////////////////////////////////////////////
    // TESTS
    ///////////////////////////////////////////////////////////////////////////////

    TEST_CASE("Testing inf")
    {
        CHECK(PBR_INF == 1e20);
    }
}
