#pragma once

#include <cmath>
#include <cstdint>
#include <cassert>
#include <vector>
#include <random>

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

///////////////////////////////////////////////////////////////////////////////
// vvv CAN IGNORE

struct Point2D
{
    double x, y;
    Point2D(double x_ = 0, double y_ = 0) : x(x_), y(y_) {}
};

struct Vec
{
    double x, y, z;


    Vec(double x_, double y_, double z_) : x(x_), y(y_), z(z_) {}
    Vec(double scalar = 0.0) : Vec(scalar, scalar, scalar) {}

    inline double sqlen() const
    {
        return x * x + y * y + z * z;
    }

    inline double len() const
    {
        return std::sqrt(sqlen());
    }

    inline Vec operator*(double s) const
    {
        return { x * s, y * s, z * s };
    }

    inline Vec operator*(const Vec& v) const
    {
        return { x * v.x, y * v.y, z * v.z };
    }

    inline Vec operator/(double s) const
    {
        return *this * (1. / s);
    }

    inline Vec operator+(const Vec& b) const
    {
        return {x + b.x, y + b.y, z + b.z};
    }

    inline Vec operator-(const Vec& b) const
    {
        return *this + b * (-1.);
    }

};

/** Normalize the vector, return a unit vector in the same direction as the parameter. */
inline Vec normalize(const Vec& v)
{
    return v / v.len();
}

/** Calculate the dot product between vectors a and b. */
inline double dot(const Vec& a, const Vec& b)
{
    return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
}

/** Calculate the cos of the angle between vectors a and b. */
inline double cosv(const Vec& a, const Vec& b)
{
    return dot(normalize(a), normalize(b));
}

/** Calculate the cross product between a and b. */
inline Vec cross(const Vec& a, const Vec& b)
{
    return { 
        (a.y * b.z) - (a.z * b.y),
        (a.z * b.x) - (a.x * b.z),
        (a.x * b.y) - (a.y * b.x)
    };
}

// ^^^
///////////////////////////////////////////////////////////////////////////////

/** Reflect the incident vector v about a normal n. */
inline Vec reflect(const Vec& v, const Vec& n)
{
    return v - n * 2 * cosv(v, n) * v.len();
}

/** Structure that represents a ray in 3D. */
struct Ray
{
    Vec origin;
    Vec direction;
};

/** Clamp a value x between min and max. */
inline double clamp(double x, double min = 0, double max = 1)
{
    return (x < min) ? min : (x > max) ? max : x;
}
