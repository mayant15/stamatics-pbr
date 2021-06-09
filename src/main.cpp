#include "math_definitions.h"
#include "camera.h"
#include "stb_image_write.h"
#include "config.h"
#include "integrators.h"
#include "brdfs.h"
#include "scene.h"

#include <iostream>
#include <vector>

std::vector<Point2D> sample_unit_circle()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dist(0.0, 1.0);

    std::vector<Point2D> result = {Point2D{0.0, 0.0}}; // Always sample the origin
    for (int i = 0; i < PBR_SAMPLES_PER_PIXEL - 1; ++i)
    {
        double u1 = dist(gen);
        double u2 = dist(gen);

        result.emplace_back(
            std::sqrt(u1) * std::cos(2 * PBR_PI * u2),
            std::sqrt(u1) * std::sin(2 * PBR_PI * u2));
    }

    return result;
}

Colori to_colori(const Colorf &color)
{
    // Gamma correction
    double gamma = 1 / 2.2;
    double gx = std::pow(clamp(color.x), gamma);
    double gy = std::pow(clamp(color.y), gamma);
    double gz = std::pow(clamp(color.z), gamma);

    // Convert a valid Colorf to Colori
    return (255 << 24) | ((int)std::floor(gz * 255) << 16) | ((int)std::floor(gy * 255) << 8) | (int)std::floor(gx * 255);
}

int main()
{
    try
    {
        // Setup the camera
        Camera camera;
        camera.position = PBR_CAMERA_POSITION;
        camera.look_at = PBR_CAMERA_LOOKAT;
        camera.fov = PBR_CAMERA_FOV_DEG;
        camera.calculate_basis((double)PBR_OUTPUT_IMAGE_COLUMNS / PBR_OUTPUT_IMAGE_ROWS);

        PathIntegrator integrator;
        integrator.set_scene(&PBR_ACTIVE_SCENE);

        std::vector<Colori> image(PBR_OUTPUT_IMAGE_ROWS * PBR_OUTPUT_IMAGE_COLUMNS);

        // Iterate over all rows
#if PBR_USE_THREADS
#pragma omp parallel for
#endif
        for (int row = 0; row < PBR_OUTPUT_IMAGE_ROWS; ++row)
        {
            std::cout << "Processing row " << row << std::endl;

            // Iterate over all cols
            for (int col = 0; col < PBR_OUTPUT_IMAGE_COLUMNS; ++col)
            {

                // TODO: Implement stratified sampling here
                // Done
                auto spp = sample_unit_circle();

                Colorf color;
                int i = 0;
                for (const auto &s : spp)
                {
                    double c_x, c_y, d_x, d_y;
                    c_x = 0.5 * (i % 2) * 2 - 1;
                    c_y = 0.5 * (((i % 4) < 2) ? 1 : -1);
                    d_x = s.x / 2.0;
                    d_y = s.y / 2.0;
                    double x = ((col + c_x + d_x) / PBR_OUTPUT_IMAGE_COLUMNS) * 2 - 1;
                    double y = ((row + c_y + d_y) / PBR_OUTPUT_IMAGE_ROWS) * 2 - 1;
                    // Normalize (row + deviation, col + deviation) to (x, y) where x and y are between -1 and 1.
                    /* double x = ((col + s.x) / PBR_OUTPUT_IMAGE_COLUMNS) * 2 - 1;
                    double y = ((row + s.y) / PBR_OUTPUT_IMAGE_ROWS) * 2 - 1;*/
                    Ray ray = camera.get_ray(x, y);
                    color = color + integrator.trace_ray(ray, 0) / (PBR_SAMPLES_PER_PIXEL);
                    i++;
                }

                image[row * PBR_OUTPUT_IMAGE_COLUMNS + col] = to_colori(color);
            }
        }

        // Write to file
        stbi_flip_vertically_on_write(true);
        stbi_write_png(PBR_OUTPUT_IMAGE_NAME, PBR_OUTPUT_IMAGE_COLUMNS, PBR_OUTPUT_IMAGE_ROWS, 4, image.data(), PBR_OUTPUT_IMAGE_COLUMNS * sizeof(Colori));

        // Completed successfully! :)
        std::cout << "All ok!" << std::endl;
    }
    catch (const std::exception &e)
    {
        // Print out an error message if caught
        std::cout << "ERROR: " << e.what() << std::endl;
    }

    return 0;
}
