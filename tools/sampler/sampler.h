#pragma once

#include <vector>
#include <cmath>
#include <random>

#define PBR_PI 3.1415926535897932384626433832795

// A simple struct to represent a point in 2D
struct Point
{
    double x, y;
    Point(double x_ = 0, double y_ = 0) : x(x_), y(y_) {}
};

/*!
 * This function returns a collection of randomly sampled points that lie 
 * inside a unit circle.
 * 
 * @param n Number of points to sample
 * @return std::vector<Point> A list of sampled points
 */
std::vector<Point> sample_unit_circle(size_t n)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dist(0.0, 1.0);

    std::vector<Point> result;
    for (int i = 0; i < n; ++i) 
    {
        double u1 = dist(gen);
        double u2 = dist(gen);

        result.emplace_back(
            std::sqrt(u1) * std::cos(2 * PBR_PI * u2),
            std::sqrt(u1) * std::sin(2 * PBR_PI * u2)
        );
    }

    return result;
}
