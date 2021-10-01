#ifdef PLATFORM_WIN32

#include "platform/opengl/context.h"
#include "platform/opengl/glad/glad.h"
#include "platform/opengl/glad/glad.c"
#include "platform/opengl/wgl.h" 

#include <Windows.h>
#include <stdio.h>

void cmt_platform_renderer_create(void *data)
{
    HDC device_context = *((HDC *)data);

    PIXELFORMATDESCRIPTOR pixel_format = {};
    pixel_format.nSize = sizeof(pixel_format);
    pixel_format.nVersion = 1;
    pixel_format.dwFlags = PFD_DRAW_TO_WINDOW|PFD_SUPPORT_OPENGL|PFD_DOUBLEBUFFER;
    pixel_format.iPixelType = PFD_TYPE_RGBA;
    pixel_format.cColorBits = 32;
    pixel_format.cDepthBits = 24;
    pixel_format.cStencilBits = 8;
    pixel_format.iLayerType = PFD_MAIN_PLANE;

    int window_pixel_format = ChoosePixelFormat(device_context, &pixel_format);
    SetPixelFormat(device_context, window_pixel_format, &pixel_format);

    HGLRC temp_gl_context = wglCreateContext(device_context);
    wglMakeCurrent(device_context, temp_gl_context);
    
    i32 attributes[] = 
    {
        WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
        WGL_CONTEXT_MINOR_VERSION_ARB, 5,
        WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB, 
        0, // NOTE: End
    };
    
    PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB =
        (PFNWGLCREATECONTEXTATTRIBSARBPROC)wglGetProcAddress("wglCreateContextAttribsARB");
    if(wglCreateContextAttribsARB)
    {
        HGLRC gl_context = wglCreateContextAttribsARB(device_context, 0, attributes);
        wglMakeCurrent(0, 0);
        wglDeleteContext(temp_gl_context); // NOTE: delete temporal context
        wglMakeCurrent(device_context, gl_context);
        PFNWGLSWAPINTERVALEXTPROC wglSwapIntervalEXT = 
                    (PFNWGLSWAPINTERVALEXTPROC)wglGetProcAddress("wglSwapIntervalEXT");
        if(wglSwapIntervalEXT)
        {
            wglSwapIntervalEXT(1);
        }
        if(!gladLoadGL())
        {
            printf("Error: cannot load glad functions\n");
        }
    }
    else
    {
        printf("Error: cannot create opengl context\n");
    }

}

#endif // PLATFORM_WIN32
