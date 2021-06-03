# Physically-Based Rendering

A short course on pathtracing for Stamatics Projects '21.

## Week 7

The path-based formulation has been implemented, with paths being built incrementally. Sampling is now over a hemisphere since we're not really doing transparency right now, every material now has its own BRDF.

### Task: Stratified sampling for the camera

The current implementation samples camera rays uniformly from a circlular region inside the active pixel. Implement [stratified sampling](https://www.pbr-book.org/3ed-2018/Sampling_and_Reconstruction/Stratified_Sampling) which subdivides this pixel and selects samples uniformly within those subdivisions.

### Result

These images were generated with 4 bounces and samples-per-pixel 16, 128, 512 and 1024 respectively. These results were with no stratified sampling.

![16](screenshots/out_16_spp.png)
![128](screenshots/out_128_spp.png)
![512](screenshots/out_512_spp.png)
![1024](screenshots/out_1024_spp.png)

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
