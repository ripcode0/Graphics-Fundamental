cmake_minimum_required(VERSION 3.15)

file(GLOB_RECURSE SRCS 
            ./*.h
            ./*.cpp
            ./GL/*.h
            ./GL/*.cpp
            )

add_library(Graphics STATIC ${SRCS})
add_library(lib::Graphics ALIAS Graphics)

target_include_directories(Graphics PUBLIC
    ${WGLAD_INC_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_directories(Graphics PUBLIC
    ${LIB_DIR})

target_link_libraries(Graphics PUBLIC wglad.lib)

set_target_properties(Graphics PROPERTIES
    LINKER_LANGUAGE CXX
    ARCHIVE_OUTPUT_DIRECTORY ${LIB_DIR}
    ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${LIB_DIR}
    ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${LIB_DIR}
)