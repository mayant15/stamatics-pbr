# Physically-Based Rendering

A short course on pathtracing for Stamatics Projects '21

## Week 2

This week we'll lay down the foundations of the scene by defining a camera, spheres, ray trace function and image output. Quite a lot of code is added so please go through things carefully.

There are a few math operations in the `Vec` class that leverage a few C++ features to make code simpler. Those and others are marked with
```cpp
///////////////////////////////////////////////////////////////////////////////
// vvv CAN IGNORE

code that can be ignored

// ^^^
///////////////////////////////////////////////////////////////////////////////
```
These sections can be ignored and it's okay to not understand them. For all other parts though there are a ton of comments in the code that you should also read to get a better picture.

I'll now describe this week's tasks in detail.

### Task 1: Intersections with the sphere

`math_definitions.h` defines vector types and operations. It also defines a `SphereGeometry` type, and that's what we're interested in for now. Given a ray's origin, ray's direction, sphere's center and sphere's radius, is it possible to find the points where the ray intersects the sphere?

### Task 2: Camera

`camera.h` defines a camera that can be placed in the scene. We want to send out a ray from the camera to different directions depending on which pixel this ray is for. We have the camera's position, we want to define a plane perpendicular to the vector `w = look_at - position`. Vectors `u` and `v` are vectors in the plane. We now want a section of this plane centered at `look_at` with a size that depends on the camera's field of view and the output image's aspect ratio.

You now need to complete two functions:
1. `get_ray()`: Label the corners of this section from (-1, -1) to (1, 1). The loop in `main.cpp` calculates the coordinates (x, y) for each pixel on this section. The `get_ray()` function calculates a ray starting from the camera's position pointing to the direction of (x, y)
1. `calculate_basis()`: Find the vectors u, v and w for this camera configuration. w has already been defined above.

### Result

If all TODOs are successful, you can run the program and get an output image like this. It should be in `build\bin\Debug\out.png`

![out.png](screenshots/out.png)

## Build Instructions

**Requirements:**
- C++ compiler
- CMake (get this via `pip` and not `apt` if you're on Ubuntu)

**Build:**

```
mkdir build
cd build
cmake ..
cmake --build .
```

You should now have an executable in `build/bin` or `build/bin/Debug`
