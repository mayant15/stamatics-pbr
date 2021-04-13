#pragma once

#include "math_definitions.h"

struct Camera
{
    float fov = 45;
    Vec position;
    Vec look_at;

    Ray get_ray(double x, double y) const
    {
        return {};
    }
};
