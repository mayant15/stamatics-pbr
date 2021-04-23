#pragma once

#include "math_definitions.h"

/** Structure that represents a camera in the scene. */
struct Camera
{
    /** Camera half field-of-view in degrees. */
    double fov;

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
        return {
            position,
            w + u * x + v * y
        };
    }

    /*!
     * @brief Calculate a basis for the look at plane
     * 
     * @param aspect_ratio Aspect ratio for the camera's output image
     */
    void calculate_basis(double aspect_ratio)
    {
        w = (look_at - position);

        double width = w.len() * std::tan(PBR_DEG_TO_RAD(fov));
        double height = width / aspect_ratio;
        u = normalize(cross(w, { 0, 1, 0 })) * width;
        v = normalize(cross(u, w)) * height;
    }

private:
    Vec u, v, w;
};
