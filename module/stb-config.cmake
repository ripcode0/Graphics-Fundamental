set(STB_INSTALL_DIR ${CMAKE_SOURCE_DIR}/External/stb)

set(stbfiles stb_image.h stb_image_write.h)

foreach(stbfile ${stbfiles})
    if(NOT EXISTS ${STB_INSTALL_DIR}/${stbfile})
        file(DOWNLOAD "https://raw.githubusercontent.com/nothings/stb/master/${stbfile}" 
         ${STB_INSTALL_DIR}/${stbfile})
    endif()
endforeach()
