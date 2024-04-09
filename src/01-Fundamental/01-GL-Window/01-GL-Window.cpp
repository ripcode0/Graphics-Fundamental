#include <iostream>
#include <wglad/wglad.h>

LRESULT WINAPI WndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp){
    return DefWindowProcA(hwnd, msg, wp, lp);
}

int main(int args, char* argv[])
{

    WNDCLASSEXA wc{};
    wc.cbSize = sizeof(wc);
    wc.hInstance = GetModuleHandle(nullptr);
    wc.hbrBackground = (HBRUSH)GetStockObject(DKGRAY_BRUSH);
    wc.hCursor = LoadCursorA(nullptr, IDC_ARROW);
    wc.lpszClassName = "ModernOpenGL";
    wc.style = CS_VREDRAW | CS_HREDRAW | CS_OWNDC;
    wc.lpfnWndProc = WndProc;

    ATOM res = RegisterClassExA(&wc);

    int x = (GetSystemMetrics(SM_CXSCREEN) - 1000) /2;
    int y = (GetSystemMetrics(SM_CYSCREEN) - 700) /2;

    DWORD style = WS_OVERLAPPEDWINDOW;
    HWND hwnd = CreateWindowExA(NULL, wc.lpszClassName, "hello",
     style, x, y, 1000, 700, nullptr, 0, wc.hInstance, 0
     );

    //if(!hwnd) log_error("failed to create window");

    ShowWindow(hwnd, TRUE);

    HDC dc{};
    HGLRC rc{};
    

    WGL::createGLContextFromHwnd(hwnd, &rc, &dc);

    MSG msg{};
    while (msg.message != WM_QUIT)
    {
        if(PeekMessageA(&msg, nullptr, 0, 0, PM_REMOVE)){
            if(msg.message == WM_KEYDOWN && msg.wParam == VK_ESCAPE)
                PostQuitMessage(0);
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        /* code */
    }
    

    return (int)msg.lParam;

    return 0;
}