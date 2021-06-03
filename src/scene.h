#pragma once

#include "math_definitions.h"
#include "material.h"

namespace pbr
{
    /** Structure that represents a spherical object. */
    struct SphereGeometry
    {
        Vec center;
        double radius;

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

    struct Actor;

    /** Information required from each intersection. */
    struct HitResult
    {
        double param;
        Vec point;
        Vec normal;
        const Actor* actor;
    };

    /** An object that can be placed in the scene. Contains material and geometry for the object. */
    struct Actor
    {
        std::shared_ptr<Material> material;
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
                hit.actor = this;
                hit.normal = normalize(hit.point - geometry.center);
                return true;
            }
            else
            {
                return false;
            }
        }
    };

    /** Scene alias for convenience. */
    using Scene = std::vector<Actor>;

    //// These are externs and defined in scene.cpp because we're going to pass pointers and such
    //// So I don't want this to be defined in each translation unit separately.

    extern Scene PBR_SCENE_RTWEEKEND;
    // extern Scene PBR_SCENE_CORNELL;
}
