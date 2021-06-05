#include "material.h"

#include <scene/scene.h>
#include <config.h>

namespace pbr
{
    Basis BaseBRDF::get_basis(const HitResult& hit) const
    {
        Vec w = hit.normal;
        Vec u = normalize(cross(w, Vec { 0, 1, 0 }));
        Vec v = normalize(cross(u, w));
        return { u, v, w };
    }

    Ray BaseBRDF::sample(const Ray& in, const HitResult& hit)
    {
        auto s = rng.sample_hemisphere();
        auto b = get_basis(hit);
        auto dir = normalize(b.u * s.x + b.v * s.y + b.w * s.z);
        return { hit.point, dir };
    }

    Colorf BaseBRDF::eval(const Ray& in, const HitResult& hit, const Ray& out)
    {
        // Returns hit.material.color by default
        return hit.actor->material->color;
    }

    Ray DiffuseBRDF::sample(const Ray& in, const HitResult& hit)
    {
        // Cos-weighted sampling the hemisphere
        double u1 = rng.sample();
        double u2 = rng.sample();

        double theta = std::acos(1 - 2 * u1) / 2;
        double phi = 2 * PBR_PI * u2;

        double x = std::sin(theta) * std::cos(phi);
        double y = std::sin(theta) * std::sin(phi);
        double z = std::cos(theta);

        auto b = get_basis(hit);
        auto dir = normalize(b.u * x + b.v * y + b.w * z);

        return { hit.point, dir };
    }

    Colorf DiffuseBRDF::eval(const Ray& in, const HitResult& hit, const Ray& out)
    {
        // Cos-weighted, so cos/pi has already been cancelled
        double roughness = hit.actor->material->roughness;
        Colorf albedo = hit.actor->material->color;
        if (roughness == 0)
        {
            // Return Lambertian diffuse
            return albedo;
        }

        // Oren-Nayar model
        //   https://en.wikipedia.org/wiki/Oren%E2%80%93Nayar_reflectance_model

        auto [theta_in, phi_in] = to_polar_hemisphere(in.direction * -1, hit.normal);
        auto [theta_out, phi_out] = to_polar_hemisphere(out.direction, hit.normal);

        double alpha = std::max(theta_in, theta_out);
        double beta = std::min(theta_in, theta_out);

        double sq_rough = roughness * roughness;
        double A = 1 - (0.5 * sq_rough) / (sq_rough + 0.33);
        double B = (0.45 * sq_rough) / (sq_rough + 0.09);

        B = B * std::max(0., std::cos(phi_in - phi_out)) * std::sin(alpha) * std::tan(beta);
        return albedo * (A + B);
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
