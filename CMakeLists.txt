cmake_minimum_required(VERSION 3.17)
project(pbr)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(common src)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

set(PBR_SOURCES
    common/stb_image_write.cpp

    src/core/units.cpp
    src/scene/scene.cpp
    src/materials/material.cpp
)

add_executable(pbr ${PBR_SOURCES} src/main.cpp)
add_executable(pbr-test ${PBR_SOURCES} common/doctest.cpp)
target_compile_definitions(pbr-test PRIVATE PBR_BUILDING_TESTS)

# OpenMP
find_package(OpenMP)
if(OpenMP_CXX_FOUND)
    target_link_libraries(pbr PUBLIC OpenMP::OpenMP_CXX)
    target_link_libraries(pbr-test PUBLIC OpenMP::OpenMP_CXX)
endif()

# Other tools
add_executable(sample2d tools/sampler/main.cpp common/stb_image_write.cpp)

# Copy compile_commands.json to repo root
configure_file(${CMAKE_BINARY_DIR}/compile_commands.json ${CMAKE_SOURCE_DIR}/compile_commands.json COPYONLY)

