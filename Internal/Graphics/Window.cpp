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
     style, x, y, cx, cy, nullptr, 0, wc.hInstance, this
     );
    if(!mHwnd) log_error("failed to create window %s", title);
}

Window::~Window()
{
    if(mHwnd) DestroyWindow(mHwnd);
}

void Window::onResize(int cx, int cy)
{
    if(pfnOnResize){
        pfnOnResize(cx, cy);
    }
}

void Window::show()
{
    ShowWindow(mHwnd, SW_SHOWNORMAL);
}

LRESULT Window::LocalWndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
    switch (msg)
    {
    case WM_ACTIVATE:{
        if(LOWORD(wp) == WA_INACTIVE){
            printf("[window] inactive\n");
            mState.bPaused = true;
        }else{
            mState.bPaused = false;
        }
        return 0;
    }
    case WM_SIZE:{
        int cx = (int)LOWORD(lp);
        int cy = (int)HIWORD(lp);
        //printf("[window] size %d : %d\n", cx, cy);
        if(wp == SIZE_MINIMIZED){
            mState.bPaused = true;
            mState.bMinimized = true;
            mState.bMaximized = false;
        }
        else if(wp == SIZE_MAXIMIZED){
            mState.bPaused = false;
            mState.bMinimized = false;
            mState.bMaximized = true;
            onResize(cx,cy);
        }
        else if(wp == SIZE_RESTORED){
            //printf("[window] RESTORED %d : %d\n", cx, cy);
            if(mState.bMinimized){
                mState.bPaused = false;
                mState.bMinimized = false;
                onResize(cx, cy);
            }
            else if(mState.bMaximized){
                mState.bPaused = false;
                mState.bMaximized = false;
                onResize(cx, cy);
            }
            else if(mState.bResizing){
                //printf("[window] ignore resize\n");
                //return 0;
            }
            else{
                onResize(cx, cy);
            }
        }
        return 0;
    }break;
    case WM_GETMINMAXINFO:{
        ((MINMAXINFO*)lp)->ptMinTrackSize = {300, 300};
        return 0;
    }
    case WM_ENTERSIZEMOVE:{
        mState.bResizing = true;
        mState.bPaused = true;
        return 0;
    }
    case WM_EXITSIZEMOVE:{
        mState.bPaused = false;
        mState.bResizing = false;
        RECT rc{};
        GetClientRect(hwnd, &rc);
        onResize(rc.right - rc.left, rc.bottom - rc.top);
        return 0;
    }
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    
    default:
        break;
    }
    return DefWindowProc(hwnd, msg, wp, lp);
}

LRESULT Window::WndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
    Window* window = (Window*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
    switch (msg)
    {
    case WM_CREATE:{
        window = (Window*)((LPCREATESTRUCT)lp)->lpCreateParams;
        window->mHwnd = hwnd;
        SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)window);
        return 0;
    }break;
    default:
        break;
    }
    if(window){
        return window->LocalWndProc(hwnd, msg, wp, lp);
    }
    return DefWindowProcA(hwnd, msg, wp, lp);
}

bool executeWindow(Window *window)
{
    bool isRunning = true;
    MSG msg{};
    // if(PeekMessageA(&msg, nullptr, 0, 0, PM_REMOVE)){
    //     if(msg.message == WM_KEYDOWN && msg.wParam == VK_ESCAPE){
    //         PostQuitMessage(0);
    //         isRunning = false;
    //     }
    //     if(msg.message == WM_QUIT){
    //         isRunning = false;
    //     }
    //     TranslateMessage(&msg);
    //     DispatchMessageA(&msg);
    // }

    while(PeekMessageA(&msg, nullptr, 0, 0, PM_REMOVE)){
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
    // auto timer = &window->mTimer;
    // timer->tick();
    // static int frameCount = 0;
    // static float timeElapsed = 0.0f;
    // frameCount++;
    // if((timer->totalTime() - timeElapsed) >= 1.0f){
    //     float fps = (float)frameCount;
    //     float mspf = 1000.f / fps;
    //     printf("fps : %f : %f : %f\n", fps, mspf, timer->deltaTime());
    //     frameCount =0;
    //     timeElapsed += 1.f;
    // }

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
