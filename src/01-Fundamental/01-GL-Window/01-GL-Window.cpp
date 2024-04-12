#include <iostream>
#include <wglad/wglad.h>
#include <GL/GLWindow.h>


int main(int args, char* argv[])
{

    GLWindow window(1024, 640, "hello world");  
    
    window.show();

    while (ExecWindow(&window))
    {
        glClearColor(0.5, 0.2,0.3, 1);
        glClear(GL_COLOR_BUFFER_BIT);
        
        

        SwapChain(&window);
    }
    
    return 0;
}