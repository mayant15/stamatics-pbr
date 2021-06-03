#pragma once

#include "math_definitions.h"
#include "brdfs.h"
#include "scene.h"
#include "config.h"

struct PathIntegrator
{
    void set_scene(const Scene* scene)
    {
        p_scene = scene;
    }

    Colorf trace_ray(const Ray& ray, int depth)
    {
        if (depth >= PBR_MAX_RECURSION_DEPTH) return PBR_COLOR_WHITE;

        HitResult hit;
        if (intersect_scene(ray, hit))
        {
            auto& brdf = hit.material->brdf;
            Ray sampled_ray = brdf->sample(ray, hit);
            Colorf coeff = brdf->eval(ray, hit, sampled_ray);
            return hit.material->emission + coeff * trace_ray(sampled_ray, depth + 1);
        }
        else return PBR_BACKGROUND_COLOR;
    }

private:
    const Scene* p_scene;

    bool intersect_scene(const Ray& ray, HitResult& out_hit) const
    {
        bool does_hit = false;
        HitResult closest_hit;
        for (const auto& actor : *p_scene)
        {
            HitResult hit;
            if (actor.intersect(ray, hit))
            {
                if (does_hit)
                {
                    if (hit.param < closest_hit.param)
                    {
                        closest_hit = hit;
                    }
                }
                else
                {
                    closest_hit = hit;
                    does_hit = true;
                }
            }
        }

        out_hit = closest_hit;
        return does_hit;
    }
};

#if 0

template <class Sampler, class BRDF>
struct Integrator
{
    void set_scene(const Scene* scene)
    {
        p_scene = scene;
    }

    /*!
    * @brief Recursively trace the ray.
    * 
    * @param ray Ray that's being traced
    * @return Colorf Output color
    */
    Colorf trace_ray(const Ray& ray, int depth)
    {
        if (depth >= PBR_MAX_RECURSION_DEPTH)
        {
            return PBR_BACKGROUND_COLOR;
        }

        HitResult hit;
        if (intersect_scene(ray, hit))
        {
            auto samples = sampler(ray, hit);

            Colorf result = Colorf { 0.0 };
            for (const auto& sample_ray : samples)
            {
                Colorf tr = Colorf { 1.0 };
                if (sample_ray.direction.len() > PBR_EPSILON)
                {
                    tr = trace_ray(sample_ray, depth + 1);
                }

                Colorf coeff = brdf(ray, hit, sample_ray);
                result = result + coeff * tr * sampler.weight;
            }

            // NOTE: result = emission + \sum_0^n weight * BRDF(in, out) * I(hit, trace)
            //   Change the weight for other methods of integration appropriately
            return result + hit.material.emission;
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
    Sampler sampler;

    bool intersect_scene(const Ray& ray, HitResult& out_hit) const
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

#endif
