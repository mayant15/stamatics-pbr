# Physically-Based Rendering

A short course on pathtracing for Stamatics Projects '21.

## Structure

The `week-*` branches have tasks and corresponding code created as part of the eight week course. The `main` branch contains a continuation of that project, extended with various other features and improvements.

## Examples

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
