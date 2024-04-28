message(STATUS "find external library")

if(NOT EXISTS ${CMAKE_SOURCE_DIR}/module/wglad-download.cmake)
message(STATUS "download wglad confiure file")
file(DOWNLOAD "https://raw.githubusercontent.com/ripcode0/wglad/main/module/wglad-download.cmake" ${CMAKE_SOURCE_DIR}/module/wglad-download.cmake)
endif()

include(wglad-download)

include(stb-config)