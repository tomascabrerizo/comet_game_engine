#include <stdio.h>

#include "base/base.h"
#include "base/memory.h"
#include "base/memory.c"
#include "base/event.h"
#include "base/event.c"

#include "platform/platform.h"
#include "platform/platform_win32.c"

#include "renderer/renderer.h"
#include "renderer/renderer_opengl.c"

static b8 global_running;

f32 vertices[6] =
{
    -1.0f, -1.0f,
     1.0f, -1.0f,
     0.0f,  1.0f,
};

char *triangle_vert_shader = 
    "#version 450 core\n"
    "layout (location = 0) in vec2 pos;\n"
    "void main() {\n"
        "gl_Position = vec4(pos, 0, 1);\n"
    "}\n";
char *triangle_frag_shader = 
    "#version 450 core\n"
    "out vec4 color;\n"
    "void main() {\n"
        "color = vec4(0, 0, 1, 1);\n"
    "}\n";

int main(void)
{
    CmtPlatformState platform = {0};
    cmt_platform_create(&platform, "Comet Game Engine", 100, 100, 800, 600);
    
    CmtAllocator linear_allocator = {0};
    cmt_linear_allocator_create(&linear_allocator, MB(64));
    
    u32 *u32_align = linear_allocator.alloc(&linear_allocator, sizeof(u32), 4);
    u64 *u64_align = linear_allocator.alloc(&linear_allocator, sizeof(u64), 8);
    printf("4 bytes align: %llx\n", (u64)u32_align);
    printf("8 bytes align: %llx\n", (u64)u64_align);
    cmt_print_memory_registry();
    
    CmtRendererState renderer = {0};
    cmt_renderer_create(&linear_allocator, &renderer);
    CmtShader *triangle_shader = renderer.load_shader(&renderer, triangle_vert_shader, triangle_frag_shader);
    CmtVertexBuffer *triangle_buffer = renderer.create_vertex_buffer(&renderer, vertices, sizeof(vertices));
    renderer.use_shader(&renderer, triangle_shader);
    renderer.use_vertex_buffer(&renderer, triangle_buffer);
    
    global_running = true;
    while(global_running)
    {
        cmt_platform_pump_events(&platform);
        CmtEvent event;
        while(cmt_event_get(&event))
        {
            switch(event.type)
            {
                case CMT_QUIT_EVENT:
                {
                    printf("key quit event!\n");
                    global_running = false;
                }break;
                case CMT_KEYDOWN_EVENT:
                {
                    printf("'%c' key down event!\n", event.key.keycode);
                }break;
                case CMT_KEYUP_EVENT:
                {
                }break;
                case CMT_TEST_EVENT:
                {
                    printf("test event!\n");
                }break;
            }
        }

        renderer.begin(&renderer);
        renderer.end(&renderer);
        
        cmt_platform_swap_buffers(&platform);
    }
    cmt_platform_destroy(&platform);
    
    return 0;
}
