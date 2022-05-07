set(LIB_NAME hard_memory_allocator_lib)
set(SOURCES src/hard_memory_allocator.cpp)

add_library(${LIB_NAME} ${SOURCES})

target_include_directories(${LIB_NAME} PUBLIC
        include
        PRIVATE "${CMAKE_BINARY_DIR}"
        )