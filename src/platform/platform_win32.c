#ifdef PLATFORM_WIN32

#include <Windows.h>
#include <stdlib.h>
#include <stdio.h>

#include "platform/platform.h"
#include "platform/opengl/context.h"
#include "platform/opengl/context_win32.c"

#include "base/base.h"
#include "base/event.h"

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
            HDC device_context = GetDC(window);
            cmt_platform_renderer_create((void *)&device_context);
            ReleaseDC(window, device_context);
        }break;
        case WM_CLOSE:
        {
            CmtEvent event = {0};
            event.type = CMT_QUIT_EVENT;
            event.quit.state = true;
            cmt_event_push(event);
        }break;
        case WM_KEYDOWN:
        {
            CmtEvent event = {0};
            event.type = CMT_KEYDOWN_EVENT;
            event.key.keycode = (u8)w_param;
            cmt_event_push(event);
        }break;
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

void cmt_platform_swap_buffers(CmtPlatformState* platform)
{
    Win32PlatformState *state = (Win32PlatformState *)platform->state;
    SwapBuffers(state->device_context);
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

CmtFile cmt_platform_read_file(CmtAllocator *allocator, char *path)
{
    // TODO: use win32 IO functions 
    CmtFile result = {0};
    FILE *file = fopen(path, "r");
    if(file)
    {
        fseek(file, 0, SEEK_END);
        result.size = ftell(file);
        fseek(file, 0, SEEK_SET);
        result.data = allocator->alloc(allocator, result.size, 0);
        fread(result.data, 1, result.size, file);
    }
    else
    {
        printf("error opening file: '%s'\n", path);
    }
    fclose(file);
    return result;
}

#endif
