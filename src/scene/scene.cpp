#include "scene.h"

///////////////////////////////////////////////////////////////////////////////
// Scene description.
///////////////////////////////////////////////////////////////////////////////

// NOTE: We assume the following conventions
//   X-axis: Right
//   Y-axis: Up
//   Z-axis: Back
// Note that X cross Y = Z, making this a right-handed system

namespace pbr
{
    Scene PBR_SCENE_RTWEEKEND = {
        // Red ball
        Actor {
            std::make_shared<Material>(
                Colorf { 1.0, 0.1, 0.1 }, // Color
                Colorf { 0.0, 0.0, 0.0 },  // Emission
                new DiffuseBRDF
            ),
            SphereGeometry {
                Vec { 1.5, 1.0, 0.0 },   // Position
                1.0                      // Radius
            }
        },

        // Light 1
        Actor {
            std::make_shared<Material>(
                Colorf { 1.0, 1.0, 1.0 }, // Color
                Colorf { 6.0, 6.0, 6.0 },  // Emission
                new DiffuseBRDF
            ),
            SphereGeometry {
                Vec { 6.0, 4.5, -4.0 },   // Position
                3.0                      // Radius
            }
        },

        // Light 2
        Actor {
            std::make_shared<Material>(
                Colorf { 1.0, 1.0, 1.0 }, // Color
                Colorf { 6.0, 6.0, 6.0 },  // Emission
                new DiffuseBRDF
            ),
            SphereGeometry {
                Vec { -6.0, 4.5, -4.0 },   // Position
                3.0                      // Radius
            }
        },

        // Mirror
        Actor {
            std::make_shared<Material>(
                Colorf { 1.0, 1.0, 1.0 }, // Color
                Colorf { 0.0, 0.0, 0.0 },  // Emission
                new SpecularBRDF
            ),
            SphereGeometry {
                Vec { -1.5, 1.0, 0.0 },   // Position
                1.0                      // Radius
            }
        },

        // Floor
        Actor {
            std::make_shared<Material>(
                Colorf { 0.1, 1.0, 0.1 }, // Color
                Colorf { 0.0, 0.0, 0.0 },  // Emission
                new DiffuseBRDF
            ),
            SphereGeometry {
                Vec { 0.0, -1e5, 0.0 },  // Position
                1e5                      // Radius
            }
        }
    };

    Scene PBR_SCENE_CORNELL = {
        // Light 1
        Actor {
            std::make_shared<Material>(
                Colorf { 1.0, 1.0, 1.0 }, // Color
                Colorf { 3.0, 3.0, 3.0 },  // Emission
                new DiffuseBRDF
            ),
            SphereGeometry {
                Vec { 0.0, 5.0, -0.5 },   // Position
                1.0                      // Radius
            }
        },

        // Red ball
        Actor {
            std::make_shared<Material>(
                Colorf { 1.0, 0.0, 0.0 }, // Color
                Colorf { 0.0, 0.0, 0.0 },  // Emission
                new DiffuseBRDF,
                0.3
            ),
            SphereGeometry {
                Vec { 1.5, 1.0, 0.0 },   // Position
                1.0                      // Radius
            }
        },

        // // Purple ball
        // Actor {
        //     std::make_shared<Material>(
        //         Colorf { 1.0, 0.0, 1.0 }, // Color
        //         Colorf { 0.0, 0.0, 0.0 },  // Emission
        //         new DiffuseBRDF
        //     ),
        //     SphereGeometry {
        //         Vec { 0.0, 1.0, 0.0 },   // Position
        //         1.0                      // Radius
        //     }
        // },

        // Mirror
        Actor {
            std::make_shared<Material>(
                Colorf { 1.0, 1.0, 1.0 }, // Color
                Colorf { 0.0, 0.0, 0.0 },  // Emission
                new SpecularBRDF
            ),
            SphereGeometry {
                Vec { -1.5, 1.0, 0.0 },   // Position
                1.0                      // Radius
            }
        },

        // Floor
        Actor {
            std::make_shared<Material>(
                Colorf { 1.0, 1.0, 1.0 }, // Color
                Colorf { 0.0, 0.0, 0.0 },  // Emission
                new DiffuseBRDF
            ),
            SphereGeometry {
                Vec { 0.0, -1e5, 0.0 },  // Position
                1e5                      // Radius
            }
        },

        // Back
        Actor {
            std::make_shared<Material>(
                Colorf { 1.0, 1.0, 1.0 }, // Color
                Colorf { 0.0, 0.0, 0.0 },  // Emission
                new DiffuseBRDF
            ),
            SphereGeometry {
                Vec { 0.0, 0.0, -1e5 - 1.5 },  // Position
                1e5                      // Radius
            }
        },

        // Left wall
        Actor {
            std::make_shared<Material>(
                Colorf { 1.0, 0.0, 0.0 }, // Color
                Colorf { 0.0, 0.0, 0.0 },  // Emission
                new DiffuseBRDF
            ),
            SphereGeometry {
                Vec { -1e5 - 5, 0.0, 0.0 },  // Position
                1e5                      // Radius
            }
        },

        // Right wall
        Actor {
            std::make_shared<Material>(
                Colorf { 0.0, 1.0, 0.0 }, // Color
                Colorf { 0.0, 0.0, 0.0 },  // Emission
                new DiffuseBRDF
            ),
            SphereGeometry {
                Vec { 1e5 + 5, 0.0, 0.0 },  // Position
                1e5                      // Radius
            }
        },

        // Roof
        Actor {
            std::make_shared<Material>(
                Colorf { 1.0, 1.0, 1.0 }, // Color
                Colorf { 0.0, 0.0, 0.0 },  // Emission
                new DiffuseBRDF
            ),
            SphereGeometry {
                Vec { 0.0, 1e5 + 5, 0.0 },  // Position
                1e5                      // Radius
            }
        }
    };
}
