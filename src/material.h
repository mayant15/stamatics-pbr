#pragma once

#include "math_definitions.h"
#include <memory>

///////////////////////////////////////////////////////////////////////////////
// Colors, materials and objects placed in the scene
///////////////////////////////////////////////////////////////////////////////

/** Color as a (r, g, b) vector, where each component is between 0 and 1. Alpha is assumed to be 1. */
using Colorf = Vec;

/** A 4-byte representation of color. R, G, B and A each are 1-byte integers (between 0 and 255). */
using Colori = uint32_t;

/** Define the kind of reflection that the surface has. */
enum class EMaterialType
{
    DIFFUSE,
    SPECULAR
};

namespace path
{
    struct BaseBRDF;
}

/** Structure that represents the surface material. */
struct Material
{
    /** Color of the surface */
    Colorf color;

    /** Color of the light that this surface emits */
    Colorf emission;

    /** Behaviour of the surface */
    path::BaseBRDF* brdf;

    Material(Colorf color_, Colorf emission_, path::BaseBRDF* brdf_)
        : color(color_), emission(emission_), brdf(brdf_) {}

    ~Material()
    {
        delete brdf;
    }
};
