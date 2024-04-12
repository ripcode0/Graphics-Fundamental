#include "Window.h"

Window::Window(int cx, int cy, const char* title)
{
    WNDCLASSEXA wc{};
    wc.cbSize = sizeof(wc);
    wc.hInstance = GetModuleHandle(nullptr);
    wc.hbrBackground = (HBRUSH)GetStockObject(DKGRAY_BRUSH);
    wc.hCursor = LoadCursorA(nullptr, IDC_ARROW);
    wc.lpszClassName = "ModernOpenGL";
    wc.style = CS_VREDRAW | CS_HREDRAW | CS_OWNDC;
    wc.lpfnWndProc = Window::WndProc;

    ATOM res = RegisterClassExA(&wc);
    if(!res) log_error("failed to register %s class", wc.lpszClassName);

    int x = (GetSystemMetrics(SM_CXSCREEN) - cx) /2;
    int y = (GetSystemMetrics(SM_CYSCREEN) - cy) /2;

    DWORD style = WS_OVERLAPPEDWINDOW;

    mHwnd = CreateWindowExA(NULL, wc.lpszClassName, title,
     style, x, y, cx, cy, nullptr, 0, wc.hInstance, 0
     );
    if(!mHwnd) log_error("failed to create window %s", title);
}

Window::~Window()
{
    if(mHwnd) DestroyWindow(mHwnd);
}

void Window::show()
{
    ShowWindow(mHwnd, SW_SHOWNORMAL);
}

LRESULT Window::WndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
    switch (msg)
    {
    case WM_CLOSE:
        PostQuitMessage(0);
        break;
    
    default:
        break;
    }
    return DefWindowProcA(hwnd, msg, wp, lp);
}

bool executeWindow(Window *window)
{
    bool isRunning = true;
    MSG msg{};
    if(PeekMessageA(&msg, nullptr, 0, 0, PM_REMOVE)){
        if(msg.message == WM_KEYDOWN && msg.wParam == VK_ESCAPE){
            PostQuitMessage(0);
            isRunning = false;
        }
        if(msg.message == WM_QUIT){
            isRunning = false;
        }
        TranslateMessage(&msg);
        DispatchMessageA(&msg);
    }
    return isRunning;
}

bool BeginFrame(Window *window)
{
    return executeWindow(window);
}

void SwapFrame(Window *window)
{
    return window->swapBuffer();
}
