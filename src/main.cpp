#include "math_definitions.h"
#include "camera.h"
#include "stb_image_write.h"
#include "config.h"
#include <iostream>
#include <vector>

///////////////////////////////////////////////////////////////////////////////
// Scene description. Order is important here, because intersection test will
// happen in that order.
///////////////////////////////////////////////////////////////////////////////

// NOTE: We assume the following conventions
//   X-axis: Right
//   Y-axis: Up
//   Z-axis: Back
// Note that X cross Y = Z, making this a right-handed system

const std::vector<Actor> SCENE = {
    // Red ball
    Actor {
        Material {
            Colorf { 1.0, 0.1, 0.1 }, // Color
            Colorf { 1.0, 0.0, 0.0 }  // Emission
        },
        SphereGeometry {
            Vec { 0.0, 1.0, 0.0 },   // Position
            1.0                      // Radius
        }
    },

    // Floor
    Actor {
        Material {
            Colorf { 0.1, 1.0, 0.1 }, // Color
            Colorf { 1.0, 0.0, 0.0 }  // Emission
        },
        SphereGeometry {
            Vec { 0.0, -1e5, 0.0 },  // Position
            1e5                      // Radius
        }
    }
};

/*!
 * @brief Recursively trace the ray.
 * 
 * This function will be developed further, it is not even recursive for now.
 * 
 * @param ray Ray that's being traced
 * @return Colorf Output color
 */
Colorf trace_ray(const Ray& ray, int depth)
{
    if (depth >= PBR_MAX_RECURSION_DEPTH)
    {
        return PBR_COLOR_BLACK;
    }

    // Check if this ray intersects with anything in the scene
    bool does_hit = false;
    HitResult closest_hit;
    for (const auto& actor : SCENE)
    {
        HitResult hit;
        if (actor.intersect(ray, hit))
        {
            if (does_hit)
            {
                // Already hit something. Check if this one is closer.
                if (hit.param < closest_hit.param)
                {
                    closest_hit = hit;
                }
            }
            else
            {
                // First hit. Set closest_hit.
                closest_hit = hit;
                does_hit = true;
            }
        }
    }

    // Actual lighting calculations
    if (does_hit)
    {
        Ray refl;
        refl.direction = reflect(ray.direction, closest_hit.normal);
        refl.origin = closest_hit.point;

        // double diff = std::max(0., cosv(refl.direction, hit.normal));
        // return hit.material.emission + hit.material.color;
        return trace_ray(refl, depth + 1);
    }
    else
    {
        // If there's no intersection, return a light blue color
        return PBR_BACKGROUND_COLOR;
    }
}

///////////////////////////////////////////////////////////////////////////////
// Configuration and implementation
///////////////////////////////////////////////////////////////////////////////

int main()
{
    // Wrap the entire thing in a try-catch to catch errors
    try
    {
        // Setup the camera
        Camera camera;
        camera.position = Vec { 0, 2, 5 };
        camera.look_at = Vec { 0, 1, 0 }; // look at the red ball
        camera.calculate_basis((double) PBR_OUTPUT_IMAGE_COLUMNS / PBR_OUTPUT_IMAGE_ROWS); // Calculate u, v, w for the camera

        // The image will have ROWS * COLS number of pixels, and each pixel will have
        // one Colori for it
        std::vector<Colori> image (PBR_OUTPUT_IMAGE_ROWS * PBR_OUTPUT_IMAGE_COLUMNS);

        // Iterate over all rows
        #pragma omp parallel for
        for (int row = 0; row < PBR_OUTPUT_IMAGE_ROWS; ++row)
        {
            std::cout << "Processing row " << row << std::endl;

            // Iterates over all cols
            for (int col = 0; col < PBR_OUTPUT_IMAGE_COLUMNS; ++col)
            {
                // Normalize (row, col) to (x, y) where x and y are between -1 and 1.
                // Note that row = 0 col = 0 represents (-1, -1)
                double x = (((double) col) / PBR_OUTPUT_IMAGE_COLUMNS) * 2 - 1;
                double y = (((double) row) / PBR_OUTPUT_IMAGE_ROWS) * 2 - 1;
                
                // Get the ray corresponding to (x, y)
                Ray ray = camera.get_ray(x, y);

                // Trace the ray, find the color, write to the image vector
                Colorf color = trace_ray(ray, 0);
                image[row * PBR_OUTPUT_IMAGE_COLUMNS + col] = to_colori(color);
            }
        }

        // Use the stb library to write our calculated data to disk as a PNG file
        // Flip the image first because top-left was (-1, -1) for us.
        // The stb_image_write.h file has some documentation at the top for the library,
        // but we'll only ever need the following two lines.
        stbi_flip_vertically_on_write(true);
        stbi_write_png("out.png", PBR_OUTPUT_IMAGE_COLUMNS, PBR_OUTPUT_IMAGE_ROWS, 4, image.data(), PBR_OUTPUT_IMAGE_COLUMNS * sizeof (Colori));

        // Completed successfully! :)
        std::cout << "All ok!" << std::endl;
    }
    catch (const std::exception& e)
    {
        // Print out an error message if caught
        std::cout << "ERROR: " << e.what() << std::endl;
    }

    return 0;
}
