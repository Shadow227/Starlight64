#include <windows.h>

static bool isRunning = true;
LRESULT CALLBACK plateform_window_callback(HWND window, UINT msg, WPARAM wparm, LPARAM lparam)
{
    switch(msg)
    {
        case WM_CLOSE:
            isRunning = false;
            break;

    }

    return DefWindowProc(window,msg,wparm,lparam);

}

bool getRunning()
{
    return isRunning;
}

void plateform_update_window(HWND window)
{
    MSG msg;
    while(PeekMessageA(&msg, window, 0, 0, PM_REMOVE))
    {
        TranslateMessage(&msg);
        DispatchMessageA(&msg);
    }

}

bool createWindow(HWND* window)
{
    HINSTANCE windowInstance = GetModuleHandleA(0);

    WNDCLASS windowClass = {};

    windowClass.lpfnWndProc = plateform_window_callback;
    windowClass.hInstance = windowInstance;
    windowClass.lpszClassName = "starlight64_windowClass";
    windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);

    if(!RegisterClassA(&windowClass))
    {
        MessageBoxA(*window, "Failed to register window class", "Critical Error", MB_ICONEXCLAMATION | MB_OK);
        return false;
    }

    *window = CreateWindowExA(WS_EX_APPWINDOW,"starlight64_windowClass","Collectathon 64 | Starlight", 
       WS_THICKFRAME | WS_CAPTION | WS_SYSMENU | WS_MAXIMIZEBOX | WS_MINIMIZEBOX | WS_OVERLAPPED, 0, 0, 1280, 720, 0, 0, windowInstance, 0 );


    //
    if(window == 0)
    {
        MessageBoxA(*window, "Failed to create window", "Critical Error", MB_ICONEXCLAMATION | MB_OK);
        return false;
    }

    ShowWindow(*window, SW_SHOW);

    return true;
}