#include <windows.h>
/*
    This class was made while following a tutorial, Due to me wanting to switch to
    GLFW for easier times with this, This class will likely be removed and is only being pushed
    for documentation purposes for me to look back on later. As far as I can tell, this is a good
    way to create a Win32/64 window, but I want to try and make this...better in the future.

*/
static bool isRunning = true;
//Window Callback
LRESULT CALLBACK plateform_window_callback(HWND window, UINT msg, WPARAM wparm, LPARAM lparam)
{
    //Check if we recieve the close message (from user hitting X button), if we do set running to false
    //After check, just use default window protocal.
    switch(msg)
    {
        case WM_CLOSE:
            isRunning = false;
            break;
    }
    return DefWindowProc(window,msg,wparm,lparam);
}
//Simple getting because I made the renderer handle most of the windows stuff.
bool getRunning()
{
    return isRunning;
}
//A simple function to translate and dispatch messages. Allows for buttons to be hit.
void plateform_update_window(HWND window)
{
    MSG msg;
    while(PeekMessageA(&msg, window, 0, 0, PM_REMOVE))
    {
        TranslateMessage(&msg);
        DispatchMessageA(&msg);
    }
}
//NOTE: For some reason, in the version of VSCode I am using, this function has 3 errors, They are not real
//But I find it very odd and wanted to document it.
bool createWindow(HWND* window)
{
    //Create window instance and class
    HINSTANCE windowInstance = GetModuleHandleA(0);
    WNDCLASS windowClass = {};
    windowClass.lpfnWndProc = plateform_window_callback;
    windowClass.hInstance = windowInstance;
    windowClass.lpszClassName = "starlight64_windowClass";
    windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    //Register windows class, if we fail throw an error.
    if(!RegisterClassA(&windowClass))
    {
        MessageBoxA(*window, "Failed to register window class", "Critical Error", MB_ICONEXCLAMATION | MB_OK);
        return false;
    }
    //Attempt to create the window. 
    *window = CreateWindowExA(WS_EX_APPWINDOW,"starlight64_windowClass","Collectathon 64 | Starlight", 
       WS_THICKFRAME | WS_CAPTION | WS_SYSMENU | WS_MAXIMIZEBOX | WS_MINIMIZEBOX | WS_OVERLAPPED, 
       0, 0, 1280, 720, 0, 0, windowInstance, 0 );
    //Error checking to see if window was created
    if(window == 0)
    {
        MessageBoxA(*window, "Failed to create window", "Critical Error", MB_ICONEXCLAMATION | MB_OK);
        return false;
    }
    //Show window and return true! We are done!
    ShowWindow(*window, SW_SHOW);
    return true;
}