cmake_minimum_required(VERSION 3.28)

#USAGE INSTALL_WGLAD_DIR (input)

#set glad
if(NOT DEFINED INSTALL_WGLAD_DIR)
    set(INSTALL_WGLAD_DIR ${CMAKE_SOURCE_DIR}/External/wglad)
endif()
#check out glad dir
set(GLAD_DOWNLOAD_REQUIRED FALSE)
if(NOT EXISTS ${INSTALL_WGLAD_DIR})
    message(STATUS "download glad")
    execute_process(
        COMMAND git clone https://github.com/ripcode0/wglad.git ${INSTALL_WGLAD_DIR})
        file(REMOVE_RECURSE ${INSTALL_WGLAD_DIR}/.git)
        file(REMOVE_RECURSE ${INSTALL_WGLAD_DIR}/module)
        file(REMOVE_RECURSE ${INSTALL_WGLAD_DIR}/.gitignore)
else()
    #check out each file
    if(NOT EXISTS ${INSTALL_WGLAD_DIR}/CMakeLists.txt)
        set(GLAD_DOWNLOAD_REQUIRED TRUE)
    endif()
    if(NOT EXISTS ${INSTALL_WGLAD_DIR}/include/wglad/glad.h)
        set(GLAD_DOWNLOAD_REQUIRED TRUE)
    endif()
    if(NOT EXISTS ${INSTALL_WGLAD_DIR}/include/wglad/glad.c)
        set(GLAD_DOWNLOAD_REQUIRED TRUE)
    endif()
    if(GLAD_DOWNLOAD_REQUIRED)
        message(STATUS "download glad")
        file(REMOVE_RECURSE ${INSTALL_WGLAD_DIR})
        execute_process(
            COMMAND git clone https://github.com/ripcode0/wglad.git ${INSTALL_WGLAD_DIR})
        file(REMOVE_RECURSE ${INSTALL_WGLAD_DIR}/.git)
        file(REMOVE_RECURSE ${INSTALL_WGLAD_DIR}/module)
        file(REMOVE_RECURSE ${INSTALL_WGLAD_DIR}/.gitignore)
    endif()
endif()

add_subdirectory(External/wglad)