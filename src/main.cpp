#include "math_definitions.h"
#include "camera.h"
#include "stb_image_write.h"

#include <iostream>
#include <vector>

const std::vector<Actor> SCENE = {
    // Red ball
    Actor 
    {
        {
            Colorf { 1.0, 0.0, 0.0 }
        },
        {
            Vec { 0.0, 1.0, 0.0 }, 1.0
        }
    },

    // Floor
    Actor 
    {
        {
            Colorf { 0.0, 1.0, 0.0 }
        },
        {
            Vec { 0.0, -1e5, 0.0 }, 1e5
        }
    }
};

#define COLS 1280
#define ROWS 720

Colorf trace_ray(const Ray& ray)
{
    // for (const auto& actor : SCENE)
    // {
    //     HitResult hit;
    //     if (actor.intersect(ray, hit))
    //     {
    //         return hit.color;
    //     }
    // }
    
    return Colorf (0, 0, 1);
}

int main()
{
    try
    {
        Camera camera;
        camera.position = Vec { 0, 0, 1 };
        camera.look_at = Vec { 0, 0, 0 };

        std::vector<Colori> image (ROWS * COLS);

        for (int row = 0; row < ROWS; ++row)
        {
            std::cout << "Processing row " << row << std::endl;
            for (int col = 0; col < COLS; ++col)
            {
                double x = (((double) col) / COLS) * 2 - 1;
                double y = (((double) row) / ROWS) * 2 - 1;
                
                Ray ray = camera.get_ray(x, y);

                Colorf color = trace_ray(ray);
                image[row * COLS + col] = to_colori(color);
            }
        }

        stbi_flip_vertically_on_write(true);
        stbi_write_png("out.png", COLS, ROWS, 4, image.data(), COLS * sizeof (Colori));

        std::cout << "All ok!" << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cout << "ERROR: " << e.what() << std::endl;
    }

    return 0;
}
