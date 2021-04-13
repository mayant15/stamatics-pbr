#pragma once

#include "math_definitions.h"

/** Structure that represents a camera in the scene. */
struct Camera
{
    /** Camera half field-of-view in degrees. */
    double fov = 45;

    /** Camera position. */
    Vec position;

    /** Point that the camera is focusing on. */
    Vec look_at;

    /*!
     * @brief Get a ray from the camera to point (x, y) on the far plane
     * 
     * @param x X-coordinate, between -1 and 1
     * @param y Y-coordinate, between -1 and 1
     * @return Ray
     */
    Ray get_ray(double x, double y) const
    {
        // TODO: Use the vectors u, v, w to find a ray from the camera to (x, y)
    }

    void calculate_basis(double aspect_ratio)
    {
        // TODO: Calculate u, v, w using look_at and aspect_ratio
    }

private:
    Vec u, v, w;
};
