# root directory
cmake_minimum_required(VERSION 3.15)

# globar setting
set(CMAKE_SKIP_INSTALL_RULES TRUE)
set_property(GLOBAL PROPERTY USE_FOLDERS ON) #for visual studio filter folder
set(CMAKE_SUPPRESS_REGENERATION TRUE)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(Graphics-Fundamental
    VERSION 0.1.0
    LANGUAGES CXX
    )

# define globar directories
set(INC_DIR ${CMAKE_SOURCE_DIR}/external ${CMAKE_SOURCE_DIR}/internal/Graphics)
set(LIB_DIR ${CMAKE_SOURCE_DIR}/lib)
set(BIN_DIR ${CMAKE_SOURCE_DIR}/bin)
set(LIBS)

# configure external library
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/module)

include(test)

message(STATUS "include dir : ${INC_DIR}")
message(STATUS "lib dir : ${LIB_DIR}")
message(STATUS "binary dir : ${BIN_DIR}")

# add sub project
add_executable(${PROJECT_NAME} src/main.cpp)

# set_property(${PROJECT_NAME} PROPERTY
#         CXX_STANDARD 20
#         CXX_STANDARD_REQUIRED ON
#         )



