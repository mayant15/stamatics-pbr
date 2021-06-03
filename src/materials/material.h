#pragma once

#include "radiometry.h"

#define PBR_DECLARE_MATERIAL(NAME) \
    struct NAME##BRDF : public BaseBRDF { \
        virtual Ray sample(const Ray& in, const HitResult& hit) override; \
        virtual Colorf eval(const Ray& in, const HitResult& hit, const Ray& out) override; \
    };

namespace pbr
{
    struct HitResult;

    ///////////////////////////////////////////////////////////////////////////////
    // BRDFs
    // NOTE: in is w.r.t. rays from the camera
    ///////////////////////////////////////////////////////////////////////////////

    struct BaseBRDF
    {
        virtual Ray sample(const Ray& in, const HitResult& hit) = 0;
        virtual Colorf eval(const Ray& in, const HitResult& hit, const Ray& out) = 0;

    protected:
        UniformRNG rng;
        Basis get_basis(const HitResult& hit) const;
    };

    /*! @brief Lambertian diffuse BRDF (constant) with cos-weighted hemisphere sampling */
    PBR_DECLARE_MATERIAL(Diffuse);
    PBR_DECLARE_MATERIAL(Specular);

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
