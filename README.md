# Physically-Based Rendering

A short course on pathtracing for Stamatics Projects '21.

## Structure

The `week-*` branches have tasks and corresponding code created as part of the eight week course. The `main` branch contains a continuation of that project, extended with various other features and improvements.

## Showcase 

The following are final results by students in the project.

By [@akshatsh49](https://github.com/akshatsh49)
![akshatsh49](screenshots/showcase/akshat.png)

By [@deepalokkaushik](https://github.com/deepalokkaushik)
![deepalokkaushik](screenshots/showcase/deepalokkaushik.png)

By [@Prajwal-Arya](https://github.com/Prajwal-Arya)
![Prajwal-Arya](screenshots/showcase/prajwal-arya.png)

By [@sps1112](https://github.com/sps1112)
![sps1112](screenshots/showcase/sps.png)

By [@sumeet13gupta](https://github.com/sumeet13gupta)
![sumeet13gupta](screenshots/showcase/sumeet.png)

## Build Instructions

**Requirements:**
- C++ compiler. The main branch requires C++17 but the weekly tasks are compatible with C++11
- CMake (get this via `pip` and not `apt` if you're on Ubuntu)

**Build:**

```
mkdir build
cd build
cmake ..
cmake --build .
```

You should now have an executable in `build/bin` or `build/bin/Debug`
