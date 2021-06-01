#include <stb_image_write.h>
#include <iostream>
#include <array>
#include "sampler.h"

constexpr int IMAGE_HEIGHT = 300;
constexpr int IMAGE_WIDTH = 300;
constexpr double RADIUS = IMAGE_HEIGHT / 2.1;
using Image = std::array<uint32_t, IMAGE_HEIGHT * IMAGE_WIDTH>;

static int get_index(int row, int col)
{
    return row * IMAGE_WIDTH + col;
}

static void draw_around_pixel(Image& image, int row, int col)
{
    static constexpr int POINT_HALF_SIDE = 2;
    
    // Make sure the cursor stays in bounds both vertically and horizontally
    int hstart = std::max(0, col - POINT_HALF_SIDE);
    int hend = std::min(IMAGE_WIDTH - 1, col + POINT_HALF_SIDE);
    for (int i = hstart; i <= hend; ++i)
    {
        int vstart = std::max(0, row - POINT_HALF_SIDE);
        int vend = std::min(IMAGE_HEIGHT - 1, row + POINT_HALF_SIDE);
        for (int j = vstart; j <= vend; ++j)
        {
            image[get_index(j, i)] = 0xFFFFFFFF; // make that pixel white
        }
    }
}

int main(void)
{
    constexpr size_t NUM_SAMPLER = 600;
    std::cout << "Sampling " << NUM_SAMPLER << " samples\n";

    Image image;
    for (int i = 0; i < IMAGE_HEIGHT; ++i)
    {
        for (int j = 0; j < IMAGE_WIDTH; ++j)
        {
            image[get_index(i, j)] = 0xFF000000;
        }
    }

    auto points = sample_unit_circle(NUM_SAMPLER);

    for (const auto& point : points)
    {
        int col = RADIUS * point.x + (IMAGE_WIDTH / 2);
        int row = RADIUS * point.y + (IMAGE_HEIGHT / 2);
        draw_around_pixel(image, row, col);
    }

    stbi_write_png("sampler.png", IMAGE_WIDTH, IMAGE_HEIGHT, 4, image.data(), IMAGE_WIDTH * sizeof (uint32_t));

    return 0;
}
