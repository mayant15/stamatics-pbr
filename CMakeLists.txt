cmake_minimum_required(VERSION 3.13)
project(pbr)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include_directories(common src)

set(PBR_SOURCES
    common/stb_image_write.cpp

    src/scene.cpp
    src/units.cpp
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
