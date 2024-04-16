
file(GLOB_RECURSE SRCS ./*.h ./*.cpp)


add_executable(${target} ${SRCS})

target_include_directories(${target} PUBLIC ${INC_DIR})
target_link_directories(${target} PUBLIC ${LIB_DIR})
target_link_libraries(${target} PUBLIC wglad.lib Graphics.lib)


set_target_properties(${target} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${BIN_DIR}/${target}
    RUNTIME_OUTPUT_DIRECTORY_DEBUG ${BIN_DIR}/${target}
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ${BIN_DIR}/${target}
)

add_dependencies(${target} lib::Graphics lib::wglad)

file(GLOB shaders 
    ${CMAKE_CURRENT_SOURCE_DIR}/*.vs
    ${CMAKE_CURRENT_SOURCE_DIR}/*.vert
    ${CMAKE_CURRENT_SOURCE_DIR}/*.fs
    ${CMAKE_CURRENT_SOURCE_DIR}/*.frag
    ${CMAKE_CURRENT_SOURCE_DIR}/*.ps
    ${CMAKE_CURRENT_SOURCE_DIR}/*.tcs
    ${CMAKE_CURRENT_SOURCE_DIR}/*.tes
    ${CMAKE_CURRENT_SOURCE_DIR}/*.gs
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cs
)

foreach(shader ${shaders})
    add_custom_command(TARGET ${target} PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy
        ${shader} $<TARGET_FILE_DIR:${target}>)
endforeach()


