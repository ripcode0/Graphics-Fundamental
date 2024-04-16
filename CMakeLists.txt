# root directory
cmake_minimum_required(VERSION 3.15)

# globar setting
set(CMAKE_SKIP_INSTALL_RULES TRUE)
set_property(GLOBAL PROPERTY USE_FOLDERS ON) #for visual studio filter folder
set(CMAKE_SUPPRESS_REGENERATION TRUE)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(Graphics-Fundamental
    VERSION 0.1.0
    #LANGUAGES C CXX
    )

# define globar directories
set(INC_DIR ${CMAKE_SOURCE_DIR}/External ${CMAKE_SOURCE_DIR}/Internal/Graphics)
set(LIB_DIR ${CMAKE_SOURCE_DIR}/lib)
set(BIN_DIR ${CMAKE_SOURCE_DIR}/bin)


# configure external library
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/module)

#install exernal lib : wglad stb ..etc
include(external-config)

add_subdirectory(Internal/Graphics)
add_dependencies(Graphics lib::wglad)

message(STATUS "include dir : ${INC_DIR}")
message(STATUS "lib dir : ${LIB_DIR}")
message(STATUS "binary dir : ${BIN_DIR}")

set(LIBS wglad.lib)
set(INC_DIR ${INC_DIR} ${WGLAD_INC_DIR})

# add sub project

set(Fundamental
    01-GL-Window
    02-GL-Buffer
)

foreach(target ${Fundamental})
    message(STATUS "configure : ${target}")
    add_subdirectory(Samples/01-Fundamental/${target})
endforeach()








