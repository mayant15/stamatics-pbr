#pragma once

#include <cmath>
#include <cstdint>

struct Vec
{
    double x, y, z;

///////////////////////////////////////////////////////////////////////////////
// STAR

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

///////////////////////////////////////////////////////////////////////////////
};

inline Vec normalize(const Vec& v)
{
    return v / v.len();
}

struct Ray
{
    Vec origin;
    Vec direction;
};

using Colorf = Vec;
using Colori = uint32_t;

Colori to_colori(const Colorf& color)
{
    return (255 << 24)
    | ((int) std::floor(color.z * 255) << 16)
    | ((int) std::floor(color.y * 255) << 8)
    | (int) std::floor(color.x * 255);
}

struct Material
{
    // color as a (r, g, b) vector. alpha is assumed to be 1
    Colorf color;
};

struct SphereGeometry
{
    Vec center;
    float radius;

    bool intersect(const Ray& ray, Vec& point) const
    {
        // TODO: Calculate the point of intersection between a sphere and a ray
    }
};

struct HitResult
{
    Vec point;
    Vec normal;
    Colorf color;
};

struct Actor
{
    Material material;
    SphereGeometry geometry;

    bool intersect(const Ray& ray, HitResult& hit) const
    {
        Vec point;
        if (geometry.intersect(ray, point))
        {
            hit.point = point;
            hit.color = material.color;
            hit.normal = normalize(hit.point - geometry.center);
            return true;
        }
        else
        {
            return false;
        }
    }
};
