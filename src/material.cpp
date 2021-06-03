#include "material.h"
#include "scene.h"
#include "config.h"

namespace pbr
{
    
    Ray BaseBRDF::sample(const Ray& in, const HitResult& hit)
    {
        Vec s = rng.sample_hemisphere();

        Vec w = hit.normal;
        Vec u = normalize(cross(w, Vec { 0, 1, 0 }));
        Vec v = normalize(cross(u, w));
        
        Vec dir = normalize(u * s.x + v * s.y + w * s.z);

        return { hit.point, dir };
    }

    Colorf BaseBRDF::eval(const Ray& in, const HitResult& hit, const Ray& out)
    {
        // Returns hit.material.color by default
        return hit.actor->material->color;
    }

    Colorf DiffuseBRDF::eval(const Ray& in, const HitResult& hit, const Ray& out)
    {
        double diff = clamp(cosv(out.direction, hit.normal));
        return hit.actor->material->color * diff;
    }

    Ray SpecularBRDF::sample(const Ray& in, const HitResult& hit)
    {
        Ray refl;
        refl.direction = reflect(in.direction, hit.normal);
        refl.origin = hit.point;
        return refl;
    }

    Colorf SpecularBRDF::eval(const Ray& in, const HitResult& hit, const Ray& out)
    {
        return PBR_COLOR_WHITE;
    }
}
