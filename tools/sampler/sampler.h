#pragma once

#include <vector>
#include <cmath>

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
    // TODO: Pick n random points inside the unit circle, any way you want
    
}
