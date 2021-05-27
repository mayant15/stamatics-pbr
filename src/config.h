#pragma once

///////////////////////////////////////////////////////////////////////////////
// Renderer

#define PBR_MAX_RECURSION_DEPTH 2

#define PBR_DISCRETE_SAMPLER_DIFFUSE_OFFSET 50

#define PBR_GRID_SAMPLER_SIZE 1

#define PBR_NUM_SAMPLES 8

#define PBR_ACTIVE_SAMPLER_CLASS UniformSampler
#define PBR_ACTIVE_BRDF_CLASS    DiffuseBRDF

///////////////////////////////////////////////////////////////////////////////
// Scene and camera

#define PBR_ACTIVE_SCENE PBR_SCENE_RTWEEKEND

#define PBR_CAMERA_LOOKAT   Vec { 0, 1, 0 }
#define PBR_CAMERA_POSITION Vec { 0, 2, 5 }
#define PBR_CAMERA_FOV_DEG  45

///////////////////////////////////////////////////////////////////////////////
// Preset colors

#define PBR_COLOR_SKYBLUE Colorf { 0.572, 0.886, 0.992 }
#define PBR_COLOR_BLACK   Colorf { 0.0, 0.0, 0.0 }
#define PBR_COLOR_WHITE   Colorf { 1.0, 1.0, 1.0 }
#define PBR_COLOR_GREY    Colorf { 0.2, 0.2, 0.2 }
#define PBR_COLOR_RED     Colorf { 1.0, 0.0, 0.0 }
#define PBR_COLOR_GREEN   Colorf { 0.0, 1.0, 0.0 }
#define PBR_COLOR_BLUE    Colorf { 0.0, 0.0, 1.0 }

#define PBR_BACKGROUND_COLOR PBR_COLOR_BLACK

///////////////////////////////////////////////////////////////////////////////
// Output

#define PBR_OUTPUT_IMAGE_COLUMNS 1280
#define PBR_OUTPUT_IMAGE_ROWS    720
#define PBR_OUTPUT_IMAGE_NAME "out.png"
#define PBR_USE_THREADS 1
