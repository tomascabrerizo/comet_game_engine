#ifdef PLATFORM_WIN32

#include <Windows.h>
#include <stdlib.h>
#include "platform/platform.h"

typedef struct Win32PlatformState
{
    HINSTANCE h_instance;
    HWND window;
    HDC device_context;
} Win32PlatformState;

static LRESULT win32_window_proc(HWND window, UINT message, WPARAM w_param, LPARAM l_param)
{
    LRESULT result = 0;
    switch(message)
    {
        case WM_CREATE:
        {
        }break;
        case WM_CLOSE:
        {
        }break;
        case WM_KEYDOWN:
        case WM_KEYUP:
        {
        }
        default:
        {
            result = DefWindowProcA(window, message, w_param, l_param);
        }break;
    }
    return result;
}

void cmt_platform_create(CmtPlatformState *platform, char *app_name, u32 x, u32 y, u32 widht, u32 height)
{
    // TODO: Maybe alloc memory in heap, not use static
    static Win32PlatformState static_win32_state;
    platform->state = (void *)&static_win32_state;
    Win32PlatformState *state = (Win32PlatformState *)platform->state;
    
    // NOTE: Init win32 platform state
    state->h_instance = GetModuleHandle(0);

    WNDCLASSA window_class = {0};
    window_class.style = CS_HREDRAW|CS_VREDRAW|CS_OWNDC;
    window_class.lpfnWndProc = win32_window_proc;
    window_class.hInstance = state->h_instance;
    window_class.lpszClassName = "comet_wndclass";
    
    // TODO: Check for errors
    RegisterClassA(&window_class);
    
    state->window = CreateWindowExA(0, window_class.lpszClassName, app_name,
                                    WS_VISIBLE|WS_OVERLAPPED|WS_CAPTION|WS_SYSMENU,
                                    x, y, widht, height,
                                    0, 0, state->h_instance, 0);
    
    // TODO: Check for error
    state->device_context = GetDC(state->window);
}

void cmt_platform_pump_events(CmtPlatformState* platform)
{
    Win32PlatformState *state = (Win32PlatformState *)platform->state;
    MSG message;
    while(PeekMessageA(&message, state->window, 0, 0, PM_REMOVE))
    {
        TranslateMessage(&message); 
        DispatchMessageA(&message); 
    }
}

void cmt_platform_destroy(CmtPlatformState *platform)
{
    Win32PlatformState *state = (Win32PlatformState *)platform->state;
    ReleaseDC(state->window, state->device_context);
    state->device_context = 0;
    DestroyWindow(state->window);
    state->window = 0;
}

void *cmt_platform_allocate(u64 size)
{
    // TODO: Use VirtualAlloc
    void *result = malloc(size);
    return result;
}

void cmt_platform_release(void *mem, u64 size)
{
    // TODO: Use VirtualFree
    (void)size;
    free(mem);
}

#endif
