
file(GLOB_RECURSE SRCS ./*.h ./*.cpp)


add_executable(${target} ${SRCS})

target_include_directories(${target} PUBLIC ${WGLAD_INC_DIR})
target_link_directories(${target} PUBLIC ${WGLAD_LIB_DIR})
target_link_libraries(${target} PUBLIC wglad.lib Graphics.lib)


set_target_properties(${target} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${BIN_DIR}/${target}
    RUNTIME_OUTPUT_DIRECTORY_DEBUG ${BIN_DIR}/${target}
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ${BIN_DIR}/${target}
)

#add_dependencies(${target} lib::Graphics lib::wglad)

message(STATUS "project name : ${target}")