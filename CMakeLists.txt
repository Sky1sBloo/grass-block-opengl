cmake_minimum_required(VERSION 3.0)
project (grass-block)

find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)
add_subdirectory(lib/glad)
add_subdirectory(lib/stb_image)

file (GLOB_RECURSE SRC_FILES main.cpp src/*.cpp)
add_executable (grass-block ${SRC_FILES})

target_link_libraries(grass-block glfw glad stb_image glm)
target_include_directories(grass-block PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
