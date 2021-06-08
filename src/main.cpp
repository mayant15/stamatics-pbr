#include "pbr.h"
#include "debug.h"

void entry()
{
    using namespace pbr;
    
    // Setup the camera
    Camera camera;
    camera.position = PBR_CAMERA_POSITION;
    camera.look_at = PBR_CAMERA_LOOKAT;
    camera.fov = PBR_CAMERA_FOV_DEG;
    camera.calculate_basis((double) PBR_OUTPUT_IMAGE_COLUMNS / PBR_OUTPUT_IMAGE_ROWS);

    // Output image buffer
    Image image { PBR_OUTPUT_IMAGE_ROWS, PBR_OUTPUT_IMAGE_COLUMNS };

    // Render scene to image
    Renderer<PathIntegrator> renderer;
    renderer.render(&PBR_ACTIVE_SCENE, camera, image);

    // Write image to file
    image.write(PBR_OUTPUT_IMAGE_NAME);

    // Completed successfully! :)
    LOG_INFO("All ok!");
}

int main()
{
    try
    {
        entry();
    }
    catch (const std::exception& e)
    {
        std::cout << "ERROR: " << e.what() << std::endl;
    }

    return 0;
}
