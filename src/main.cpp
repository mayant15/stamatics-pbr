#include "math_definitions.h"
#include "camera.h"
#include "stb_image_write.h"
#include "config.h"
#include "integrators.h"

#include <iostream>
#include <vector>

/*!
 * @brief Convert floating point color to integer color type.
 *
 * Colorf has components between 0 and 1. Convert these components to integers between 0 and 255.
 * Note that Colori is usually just used to write the final PNG image. Use Colorf for all other
 * lighting calculations.
 * 
 * @param color Color to convert to integer representation
 * @return Colori 
 */
Colori to_colori(const Colorf& color)
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

int main()
{
    // Wrap the entire thing in a try-catch to catch errors
    try
    {
        // Setup the camera
        Camera camera;
        camera.position = PBR_CAMERA_POSITION;
        camera.look_at = PBR_CAMERA_LOOKAT;
        camera.fov = PBR_CAMERA_FOV_DEG;
        camera.calculate_basis((double) PBR_OUTPUT_IMAGE_COLUMNS / PBR_OUTPUT_IMAGE_ROWS);

        // Setup the integrator. Notice the <DiscreteBRDF>. This is a template parameter.
        // The aim is to implement all our BRDFs like this so that we can simply switch them
        // out here and compare results.
        Integrator<PBR_ACTIVE_SAMPLER_CLASS, PBR_ACTIVE_BRDF_CLASS> integrator;
        integrator.set_scene(&PBR_ACTIVE_SCENE);

        // The image will have ROWS * COLS number of pixels, and each pixel will have
        // one Colori for it
        std::vector<Colori> image (PBR_OUTPUT_IMAGE_ROWS * PBR_OUTPUT_IMAGE_COLUMNS);

        // Iterate over all rows
        // The #pragma is for using something called OpenMP, which will automatically run this
        // loop in parallel on multiple threads. We can do this because rows are independent.
        // Running them in parallel will give us a significant performance boost.
#if PBR_USE_THREADS
        #pragma omp parallel for
#endif
        for (int row = 0; row < PBR_OUTPUT_IMAGE_ROWS; ++row)
        {
            std::cout << "Processing row " << row << std::endl;

            // Iterate over all cols
            for (int col = 0; col < PBR_OUTPUT_IMAGE_COLUMNS; ++col)
            {
                // Normalize (row, col) to (x, y) where x and y are between -1 and 1.
                // Note that row = 0 col = 0 represents (-1, -1)
                double x = (((double) col) / PBR_OUTPUT_IMAGE_COLUMNS) * 2 - 1;
                double y = (((double) row) / PBR_OUTPUT_IMAGE_ROWS) * 2 - 1;
                
                // Get the ray corresponding to (x, y)
                Ray ray = camera.get_ray(x, y);

                // Trace the ray, find the color, write to the image vector
                Colorf color = integrator.trace_ray(ray, 0);
                image[row * PBR_OUTPUT_IMAGE_COLUMNS + col] = to_colori(color);
            }
        }

        // Use the stb library to write our calculated data to disk as a PNG file
        // Flip the image first because top-left was (-1, -1) for us.
        // The stb_image_write.h file has some documentation at the top for the library,
        // but we'll only ever need the following two lines.
        stbi_flip_vertically_on_write(true);
        stbi_write_png(PBR_OUTPUT_IMAGE_NAME, PBR_OUTPUT_IMAGE_COLUMNS, PBR_OUTPUT_IMAGE_ROWS, 4, image.data(), PBR_OUTPUT_IMAGE_COLUMNS * sizeof (Colori));

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
