#include <iostream>
#include <wglad/wglad.h>

#include "GL/GLWindow.h"

int main(int args, char* argv[])
{

    GLWindow window(1024, 780, "GLWindow");

    window.show();

    while (BeginFrame(&window))
    {
        glClearColor(0.2, 0.5, 0.7, 1.f);
        glClear(GL_COLOR_BUFFER_BIT);

        SwapFrame(&window);
    }
    
    

    return 0;
}