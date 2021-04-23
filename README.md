# Physically-Based Rendering

A short course on pathtracing for Stamatics Projects '21

## Week 3

There are no code tasks this week, mainly because the changes in code are quite significant and understanding them is a task in itself. Here's a summary.

### Configuration options

We're going to configure our renderer using a few macros, defined in `config.h`. We should keep a track of various "knobs" that our renderer will provide to the artist, and therefore this file is meant to simulate a sort of a "settings panel".

The scene that we're using is described in `scene.cpp`. More spheres can be added here and their material properties can be tweaked. We'll eventually have a number of different scenes that we'll keep here and switch between them using the `PBR_ACTIVE_SCENE` config macro.

### Materials

A "material" is a general way to define surface properties for objects, like color. Right now, we have two kinds of materials - diffuse and specular.

1. Diffuse reflections are the haphazard reflections on a rough surface. You can see these on matte surfaces, they don't shine.
1. Specular reflections are perfect reflections from a mirror-like surface. You can see these on mirrors and shiny metals.

In reality, a surface is neither perfectly diffuse nor perfectly specular, which is why most renderers let artists define these properties on a scale of 0 to 1. The BRDF then uses these parameters to determine which rays to favor. To keep things simple for now, we will consider a surface to be either diffuse or specular, but not both. This is implemented with the `EMaterialType` enum.

### Sampler

To evaluate the integration term of the rendering equation, we need to discretize it and consider a finite number of rays approaching the current point. The `DiscreteSampler` class chooses these rays. For now, we choose just one ray. For specular materials, we choose the reflection about the surface normal. For diffuse materials, we add a random offset to the direction of this reflection. The magnitude of this offset can be configured with `PBR_DISCRETE_SAMPLER_DIFFUSE_OFFSET`.

### BRDF

After the sampler gives us a set of rays to evaluate, we need to find the BRDF term of the integrand. In the current state of our renderer, we implement a simple `DiscreteBRDF`. For specular surfaces, this gives a coefficient of 1, that is, the reflection goes unchanged. For diffuse surfaces, we multiply the surface color and a cos term to model the surface as per [Lambert's cosine law](https://en.wikipedia.org/wiki/Lambert%27s_cosine_law).

**NOTE:** It is very important to note here that the combination of material, sampler and the BRDF is what's involved in solving the rendering equation. The BRDF is what makes your surface look realistic, and therefore must be chosen carefully. We'll look at much better BRDFs and samplers in the future.

### Integrator

The integrator is an interface that we'll use from `main.cpp`. This integrator performs the necessary recursive raytracing, and calls the sampler and BRDF when there's a hit. The current implementation of the integrator calculates a simple Reimann sum.

We use a C++ feature called _templates_ in the integrator so that we can swap out the BRDF and sampler with other implementations and compare, with minimal changes to the code. This is why we tried to decouple the three steps of sampling, BRDF and integration.

### Result

You can run the program and get an output image like this. It should be in `build\bin\Debug\out.png`

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
