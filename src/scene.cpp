#include "math_definitions.h"

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
    Actor {
        Material {
            Colorf { 1.0, 0.1, 0.1 }, // Color
            Colorf { 0.0, 0.0, 0.0 },  // Emission
            EMaterialType::DIFFUSE
        },
        SphereGeometry {
            Vec { 1.5, 1.0, 0.0 },   // Position
            1.0                      // Radius
        }
    },

    // Light 1
    Actor {
        Material {
            Colorf { 0.0, 0.0, 0.0 }, // Color
            Colorf { 8.0, 8.0, 8.0 },  // Emission
            EMaterialType::DIFFUSE
        },
        SphereGeometry {
            Vec { 6.0, 4.5, -4.0 },   // Position
            3.0                      // Radius
        }
    },

    // Light 2
    Actor {
        Material {
            Colorf { 0.0, 0.0, 0.0 }, // Color
            Colorf { 8.0, 8.0, 8.0 },  // Emission
            EMaterialType::DIFFUSE
        },
        SphereGeometry {
            Vec { -6.0, 4.5, -4.0 },   // Position
            3.0                      // Radius
        }
    },

    // Mirror
    Actor {
        Material {
            Colorf { 1.0, 1.0, 1.0 }, // Color
            Colorf { 0.0, 0.0, 0.0 },  // Emission
            EMaterialType::SPECULAR
        },
        SphereGeometry {
            Vec { -1.5, 1.0, 0.0 },   // Position
            1.0                      // Radius
        }
    },

    // Floor
    Actor {
        Material {
            Colorf { 0.1, 1.0, 0.1 }, // Color
            Colorf { 0.0, 0.0, 0.0 },  // Emission
            EMaterialType::DIFFUSE
        },
        SphereGeometry {
            Vec { 0.0, -1e5, 0.0 },  // Position
            1e5                      // Radius
        }
    }
};
