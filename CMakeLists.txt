cmake_minimum_required(VERSION 3.19.0)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VERSION 0.0.${PATCH_VERSION})
set(TARGET "homework3")

project(${TARGET} VERSION ${PROJECT_VERSION})

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/hard_memory_allocator)

add_executable(${TARGET}_cli main.cpp)

target_link_libraries(${TARGET}_cli hard_memory_allocator_lib)
set_target_properties(${TARGET}_cli PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
        )
