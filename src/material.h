#pragma once

#include "radiometry.h"
#include <memory>

namespace pbr
{
    struct HitResult;

    ///////////////////////////////////////////////////////////////////////////////
    // BRDFs
    // NOTE: in is w.r.t. rays from the camera
    ///////////////////////////////////////////////////////////////////////////////

    struct BaseBRDF
    {
        virtual Ray sample(const Ray& in, const HitResult& hit);
        virtual Colorf eval(const Ray& in, const HitResult& hit, const Ray& out);

    protected:
        UniformRNG rng;
    };

    /*!
     * @brief Lambertian diffuse BRDF (constant)
     * Sample: Uniform hemisphere
     */
    struct DiffuseBRDF : public BaseBRDF
    {
        virtual Colorf eval(const Ray& in, const HitResult& hit, const Ray& out) override;
    };

    struct SpecularBRDF : public BaseBRDF
    {
        virtual Ray sample(const Ray& in, const HitResult& hit) override;
        virtual Colorf eval(const Ray& in, const HitResult& hit, const Ray& out) override;
    };

    /** Structure that represents the surface material. */
    struct Material
    {
        /** Color of the surface */
        Colorf color;

        /** Color of the light that this surface emits */
        Colorf emission;

        /** Behaviour of the surface */
        BaseBRDF* brdf;

        Material(Colorf color_, Colorf emission_, BaseBRDF* brdf_)
            : color(color_), emission(emission_), brdf(brdf_) {}

        ~Material() { delete brdf; }
    };
}
