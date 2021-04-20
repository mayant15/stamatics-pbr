#pragma once

#include "math_definitions.h"
#include "config.h"

#include <tuple>

struct IntegratorTerm
{
    bool do_trace;
    Colorf coeff;
    Ray ray;

    IntegratorTerm (bool dt, Colorf c, Ray r) : do_trace(dt), coeff(c), ray(r) {}
};

// Simulates a discrete BRDF
struct DiscreteBRDF
{
    std::vector<IntegratorTerm> operator()(const Ray& incidence, const HitResult& hit) const
    {
        std::vector<IntegratorTerm> result;
        switch (hit.material.type)
        {
            case EMaterialType::DIFFUSE:
            {
                double k = 500;
                Vec d = reflect(incidence.direction, hit.normal);
                d.x += ((double) std::rand() / RAND_MAX) * k - (k / 2);
                d.y += ((double) std::rand() / RAND_MAX) * k - (k / 2);
                d.z += ((double) std::rand() / RAND_MAX) * k - (k / 2);

                Ray refl;
                refl.direction = normalize(d);
                refl.origin = hit.point;

                double diff = clamp(cosv(refl.direction, hit.normal));

                result.emplace_back(true, hit.material.color * diff, refl);
                break;
            }

            case EMaterialType::SPECULAR:
            {
                Ray refl;
                refl.direction = reflect(incidence.direction, hit.normal);
                refl.origin = hit.point;
                result.emplace_back(true, Vec { 1.0 }, refl);
                break;
            }

            default:
                result.emplace_back(false, hit.material.color, Ray {});
                break;
        }

        return result;
    }
};

// struct TrapezoidalBRDF
// {
//     std::vector<IntegratorTerm> operator()(const Ray& incidence, const HitResult& hit) const
//     {
//         // TODO: Generate equidistant grid points for trapezoidal rule
//     }
// };

template <class BRDF>
struct Integrator
{
    void set_scene(const Scene* scene)
    {
        p_scene = scene;
    }

    /*!
    * @brief Recursively trace the ray.
    * 
    * This function will be developed further, it is not even recursive for now.
    * 
    * @param ray Ray that's being traced
    * @return Colorf Output color
    */
    Colorf trace_ray(const Ray& ray, int depth) const
    {
        if (depth >= PBR_MAX_RECURSION_DEPTH)
        {
            return PBR_COLOR_SKYBLUE;
        }

        HitResult hit;
        if (intersect_scene(ray, hit))
        {
            auto terms = brdf(ray, hit);

            Colorf result;
            for (const auto& term : terms)
            {
                if (term.do_trace)
                {
                    result = result + term.coeff * trace_ray(term.ray, depth + 1);
                }
            }

            return result;
        }
        else
        {
            // If there's no intersection, return a light blue color
            return PBR_BACKGROUND_COLOR;
        }
    }

private:
    const Scene* p_scene;
    BRDF brdf;

    bool intersect_scene(const Ray& ray, HitResult& out_hit)
    {
        // Check if this ray intersects with anything in the scene
        bool does_hit = false;
        HitResult closest_hit;
        for (const auto& actor : *p_scene)
        {
            HitResult hit;
            if (actor.intersect(ray, hit))
            {
                if (does_hit)
                {
                    // Already hit something. Check if this one is closer.
                    if (hit.param < closest_hit.param)
                    {
                        closest_hit = hit;
                    }
                }
                else
                {
                    // First hit. Set closest_hit.
                    closest_hit = hit;
                    does_hit = true;
                }
            }
        }

        out_hit = closest_hit;
        return does_hit;
    }
};
