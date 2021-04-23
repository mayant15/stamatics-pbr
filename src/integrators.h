#pragma once

#include "math_definitions.h"
#include "config.h"

struct DiscreteSampler
{
    // NOTE: in is w.r.t. rays from the camera
    std::vector<Ray> operator()(const Ray& in, const HitResult& hit) const
    {
        switch (hit.material.type)
        {
            case EMaterialType::DIFFUSE:
            {
                // Add a random offset between [-k/2, k/2] to each component
                double k = PBR_DISCRETE_SAMPLER_DIFFUSE_OFFSET;
                Vec d = reflect(in.direction, hit.normal);
                d.x += ((double) std::rand() / RAND_MAX) * k - (k / 2);
                d.y += ((double) std::rand() / RAND_MAX) * k - (k / 2);
                d.z += ((double) std::rand() / RAND_MAX) * k - (k / 2);

                Ray refl;
                refl.direction = normalize(d);
                refl.origin = hit.point;
                return { refl };
            }
            
            case EMaterialType::SPECULAR:
            {
                Ray refl;
                refl.direction = reflect(in.direction, hit.normal);
                refl.origin = hit.point;
                return { refl };
            }
        
            default:
                // return a ray with zero-length direction if we don't want to trace the ray further
                return { Ray {} };
        }
    }
};

// Simulates a discrete BRDF
struct DiscreteBRDF
{
    // NOTE: in and out is w.r.t. rays from the camera
    Colorf operator()(const Ray& in, const HitResult& hit, const Ray& out) const
    {
        switch (hit.material.type)
        {
            case EMaterialType::DIFFUSE:
            {
                double diff = clamp(cosv(out.direction, hit.normal));
                return hit.material.color * diff;
            }

            case EMaterialType::SPECULAR:
            {
                return PBR_COLOR_WHITE;
            }

            default:
                return hit.material.color;
        }
    }
};

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
                result = result + coeff * tr;
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
