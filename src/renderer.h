#pragma once

#include <stb_image_write.h>
#include "materials/radiometry.h"
#include "scene/camera.h"
#include "config.h"
#include "debug.h"

namespace pbr
{
    class Image
    {
    public:
        Image(unsigned int rows, unsigned int cols)
            : _rows(rows), _cols(cols), _data()
        {
            _data.resize(rows * cols);
        }

        // Write to file as RGBA
        void write(const std::string& name)
        {
            stbi_flip_vertically_on_write(true);
            stbi_write_png(name.c_str(), _cols, _rows, 4, _data.data(), _cols * sizeof (Colori));
        }

        int rows() { return _rows; }
        int cols() { return _cols; }

        Colori& operator[](size_t index) { return _data.at(index); }
        const Colori& operator[](size_t index) const { return _data.at(index); }

    private:
        std::vector<Colori> _data;
        const unsigned int _rows;
        const unsigned int _cols;
    };

    template <class Integrator>
    class Renderer
    {
    public:
        void render(const Scene* scene, const Camera& camera, Image& outImage)
        {
            integrator.set_scene(scene);

            UniformRNG rng;

            int progress = 0;

            // Iterate over all rows
#if PBR_USE_THREADS
#pragma omp parallel for private(rng) shared(progress)
#endif
            for (int row = 0; row < outImage.rows(); ++row)
            {

                // Iterate over all cols
                for (int col = 0; col < outImage.cols(); ++col)
                {
                    Colorf color;
                    for (int i = 0; i < PBR_SAMPLES_PER_PIXEL; ++i)
                    {
                        auto sample = rng.sample_disk();

#if PBR_STRATIFIED_SAMPLE
                        // Split the pixel into four quadrants for stratified sampling
                        // Modulo operations to choose these quadrants
                        double center_x = (1. / 2.) * ((i % 2) * 2 - 1);
                        double center_y = (1. / 2.) * (((i % 4) < 2) ? 1 : -1);
                        double deviation_x = sample.x / 2.;
                        double deviation_y = sample.y / 2.;
#else
                        double center_x = 0;
                        double center_y = 0;
                        double deviation_x = sample.x;
                        double deviation_y = sample.y;

#endif

                        // Normalize (row + deviation, col + deviation) to (x, y) where x and y are between -1 and 1.
                        double x = ((col + center_x + deviation_x) / PBR_OUTPUT_IMAGE_COLUMNS) * 2 - 1;
                        double y = ((row + center_y + deviation_y) / PBR_OUTPUT_IMAGE_ROWS) * 2 - 1;
                        Ray ray = camera.get_ray(x, y);
                        color = color + integrator.trace_ray(ray, 0) / (PBR_SAMPLES_PER_PIXEL);
                    }

                    outImage[row * PBR_OUTPUT_IMAGE_COLUMNS + col] = to_colori(color);
                }

                // Not adding a critical section here, accurate progress reporting is not super important
                progress++;
                LOG_DEBUG("Rendering %f%%", progress * 100 / (double) outImage.rows());
            }
        }

    private:
        Integrator integrator {};
    };
}
