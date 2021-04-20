cmake_minimum_required(VERSION 3.13)
project(pbr)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_executable(pbr src/main.cpp src/stb_image_write.cpp src/scene.cpp)

# OpenMP
find_package(OpenMP)
if(OpenMP_CXX_FOUND)
    target_link_libraries(pbr PUBLIC OpenMP::OpenMP_CXX)
endif()
