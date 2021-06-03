#pragma once

#include "scene.h"
#include "config.h"

namespace pbr
{
    struct PathIntegrator
    {
        void set_scene(const Scene* scene)
        {
            p_scene = scene;
        }

        // TODO: Convert the following recursive function into an iterative function
        Radiance trace_ray(const Ray& ray, int depth)
        {
            if (depth >= PBR_MAX_RECURSION_DEPTH) return PBR_COLOR_WHITE;

            HitResult hit;
            if (intersect_scene(ray, hit))
            {
                auto brdf = hit.actor->material->brdf;
                Ray sampled_ray = brdf->sample(ray, hit);
                Colorf coeff = brdf->eval(ray, hit, sampled_ray);
                return hit.actor->material->emission + coeff * trace_ray(sampled_ray, depth + 1);
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
}
