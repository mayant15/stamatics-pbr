#pragma once

#include <core/math_definitions.h>

namespace pbr
{
    using ColorType = Number<Intensity::dimensions::divide<dims::Angle>>;

    /** Color as a (r, g, b) vector, where each component is between 0 and 1. Alpha is assumed to be 1. */
    using Colorf = Vec;

    /** A 4-byte representation of color. R, G, B and A each are 1-byte integers (between 0 and 255). */
    using Colori = uint32_t;

    inline Colori to_colori(const Colorf& color)
    {
        // Gamma correction
        double gamma = 1 / 2.2;
        double gx = std::pow(clamp(color.x), gamma);
        double gy = std::pow(clamp(color.y), gamma);
        double gz = std::pow(clamp(color.z), gamma);

        // Convert a valid Colorf to Colori
        return (255 << 24)
        | ((int) std::floor(gz * 255) << 16)
        | ((int) std::floor(gy * 255) << 8)
        | (int) std::floor(gx * 255);
    }


    using Radiance = Colorf;
}
