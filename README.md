# Physically-Based Rendering

A short course on pathtracing for Stamatics Projects '21.

## Week 6

### Task: The `UniformSampler`

This week we'll extend last week's 2D uniform sampler to 3D. Implement the `UniformSampler` to return directions uniformly sampled over a unit sphere.


### Result

This output image was generated with the `UniformSampler` and `DiffuseBRDF`, with 2 bounces and 32 samples.

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
