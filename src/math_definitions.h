#pragma once

#include <cmath>
#include <cstdint>
#include <cassert>

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

inline Vec reflect(const Vec& v, const Vec& n)
{
    return v - n * 2 * cosv(v, n) * v.len();
}

// ^^^
///////////////////////////////////////////////////////////////////////////////

/** Structure that represents a ray in 3D. */
struct Ray
{
    Vec origin;
    Vec direction;
};

///////////////////////////////////////////////////////////////////////////////
// Colors, materials and objects placed in the scene
///////////////////////////////////////////////////////////////////////////////

/** Color as a (r, g, b) vector, where each component is between 0 and 1. Alpha is assumed to be 1. */
using Colorf = Vec;

/** A 4-byte representation of color. R, G, B and A each are 1-byte integers (between 0 and 255). */
using Colori = uint32_t;

///////////////////////////////////////////////////////////////////////////////
// vvv CAN IGNORE

/*!
 * @brief Convert floating point color to integer color type.
 *
 * Colorf has components between 0 and 1. Convert these components to integers between 0 and 255.
 * Note that Colori is usually just used to write the final PNG image. Use Colorf for all other
 * lighting calculations.
 * 
 * @param color Color to convert to integer representation
 * @return Colori 
 */
Colori to_colori(const Colorf& color)
{
    // Colorf should always be between 0 and 1
    assert(color.x <= 1 && color.x >= 0);
    assert(color.y <= 1 && color.y >= 0);
    assert(color.z <= 1 && color.z >= 0);

    // FIXME: Gamma correction

    // Convert a valid Colorf to Colori
    return (255 << 24)
    | ((int) std::floor(color.z * 255) << 16)
    | ((int) std::floor(color.y * 255) << 8)
    | (int) std::floor(color.x * 255);
}

// ^^^
///////////////////////////////////////////////////////////////////////////////

/** Structure that represents the surface material. Just a color for now. */
struct Material
{
    Colorf color;
    Colorf emission;
};

/** Structure that represents a spherical object. */
struct SphereGeometry
{
    Vec center;
    float radius;

    bool intersect(const Ray& ray, Vec& point) const
    {
        // For intersection, solve
        // |(o + t*dir) - position| = radius
        // (op + t * dir).(op + t * dir) = radius^2
        // (dir.dir)t^2 + 2(op.dir)t + op.op - radius^2 = 0
        // i.e solve At^2 + Bt + C = 0

        Vec op = ray.origin - center;
        double A = ray.direction.sqlen();
        double B = 2 * dot(op, ray.direction);
        double C = op.sqlen() - radius * radius;

        double D = B * B - 4 * A * C;
        if (D < 0) return false; // no solution
        else D = std::sqrt(D);

        double t1 = (-1 * B + D) / (2 * A);
        double t2 = (-1 * B - D) / (2 * A);

        // returns distance, 0 if nohit
        if (t1 > PBR_EPSILON && t1 < t2)
        {
            point = ray.origin + ray.direction * t1;
            return true;
        }
        else if (t2 > PBR_EPSILON)
        {
            point = ray.origin + ray.direction * t2;
            return true;
        }
        else
        {
            return false;
        }
    }
};

/** Information required from each intersection. */
struct HitResult
{
    double param;
    Vec point;
    Vec normal;
    Material material;
};

/** An object that can be placed in the scene. Contains material and geometry for the object. */
struct Actor
{
    Material material;
    SphereGeometry geometry;

    /*!
     * @brief Calculate ray intersection with the geometry for this actor
     * 
     * @param ray Ray that will intersect this object
     * @param hit Output hit data
     * @return bool Indicates if the ray intersects with this actor
     */
    bool intersect(const Ray& ray, HitResult& hit) const
    {
        Vec point;
        if (geometry.intersect(ray, point))
        {
            hit.param = (point - ray.origin).len() / ray.direction.len();
            hit.point = point;
            hit.material = material;
            hit.normal = normalize(hit.point - geometry.center);
            return true;
        }
        else
        {
            return false;
        }
    }
};
