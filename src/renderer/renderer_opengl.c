#include "renderer/renderer.h"

#include "platform/platform.h"
#include "platform/opengl/glad/glad.h"

#define CMT_MAX_NUM_SHADERS 256
typedef struct CmtOpenglRendererState
{
    u32 shaders[CMT_MAX_NUM_SHADERS]; 
} CmtOpenglRendererState;

void cmt_renderer_create(CmtAllocator *allocator, CmtRendererState *renderer)
{
    glViewport(0, 0, 800, 600);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void cmt_renderer_destroy(CmtAllocator *allocator, CmtRendererState *renderer)
{
}

void cmt_renderer_begin(CmtRendererState *renderer)
{
    glClear(GL_COLOR_BUFFER_BIT);
}

void cmt_renderer_end(CmtRendererState *renderer)
{
}

void cmt_renderer_load_shader(CmtRendererState *renderer, char *path)
{
}
