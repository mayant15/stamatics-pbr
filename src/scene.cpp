#include "scene.h"
#include "brdfs.h"

///////////////////////////////////////////////////////////////////////////////
// Scene description.
///////////////////////////////////////////////////////////////////////////////

// NOTE: We assume the following conventions
//   X-axis: Right
//   Y-axis: Up
//   Z-axis: Back
// Note that X cross Y = Z, making this a right-handed system

Scene PBR_SCENE_RTWEEKEND = {
    // Red ball
    Actor{
        std::make_shared<Material>(
            Colorf{1.0, 0.1, 0.1}, // Color
            Colorf{0.0, 0.0, 0.0}, // Emission
            new path::DiffuseBRDF),
        SphereGeometry{
            Vec{3.0, 1.0, 0.0}, // Position
            1.0                 // Radius
        }},
    // blue ball
    Actor{
        std::make_shared<Material>(
            Colorf{0.1, 0.1, 1.0}, // Color
            Colorf{0.0, 0.0, 0.0}, // Emission
            new path::DiffuseBRDF),
        SphereGeometry{
            Vec{-3.0, 1.0, 0.0}, // Position
            1.0                  // Radius
        }},

    // Light 1
    Actor{
        std::make_shared<Material>(
            Colorf{1.0, 1.0, 1.0}, // Color
            Colorf{6.0, 6.0, 6.0}, // Emission
            new path::DiffuseBRDF),
        SphereGeometry{
            Vec{6.0, 4.5, -4.0}, // Position
            3.0                  // Radius
        }},

    // Light 2
    Actor{
        std::make_shared<Material>(
            Colorf{1.0, 1.0, 1.0}, // Color
            Colorf{6.0, 6.0, 6.0}, // Emission
            new path::DiffuseBRDF),
        SphereGeometry{
            Vec{-6.0, 4.5, -4.0}, // Position
            3.0                   // Radius
        }},

    // Mirror
    Actor{
        std::make_shared<Material>(
            Colorf{1.0, 1.0, 1.0}, // Color
            Colorf{0.0, 0.0, 0.0}, // Emission
            new path::SpecularBRDF),
        SphereGeometry{
            Vec{0.0, 1.0, 0.0}, // Position
            1.0                 // Radius
        }},

    // Floor
    Actor{
        std::make_shared<Material>(
            Colorf{0.1, 1.0, 0.1}, // Color
            Colorf{0.0, 0.0, 0.0}, // Emission
            new path::DiffuseBRDF),
        SphereGeometry{
            Vec{0.0, -1e5, 0.0}, // Position
            1e5                  // Radius
        }}};
