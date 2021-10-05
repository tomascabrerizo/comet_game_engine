#include <stdio.h>

#include "base/base.h"
#include "base/memory.h"
#include "base/memory.c"
#include "base/event.h"
#include "base/event.c"
#include "base/math.h"
#include "base/math.c"

#include "platform/platform.h"
#include "platform/platform_win32.c"

#include "renderer/renderer.h"
#include "renderer/renderer_opengl.c"

static b8 global_running;

#if 1
f32 vertices[6] =
{
    0.0f,    0.0f,
    400.0f,  300.0f,
    800.0f,  0.0f,
};
#else
f32 vertices[6] =
{
    -1.0f, -1.0f,
     1.0f, -1.0f,
     0.0f,  1.0f,
};
#endif

int main(void)
{
    // NOTE: vector library test
    v3 test = v3(3.4, 9, 40);
    printf("v3 = (%f, %f, %f)\n", test.x, test.y, test.z);
    printf("y = (%f)\n", VEC_INDEX(test, 1));
    printf("x = (%f)\n", VEC_INDEX(test, 0));
    printf("z = (%f)\n", VEC_INDEX(test, 2));

    CmtPlatformState platform = {0};
    cmt_platform_create(&platform, "Comet Game Engine", 100, 100, 800, 600);
    
    CmtAllocator linear_allocator = {0};
    cmt_linear_allocator_create(&linear_allocator, MB(64));
    
    CmtRendererState renderer = {0};
    cmt_renderer_create(&linear_allocator, &renderer);
    
    // TODO: add markers to the linear allocator or something form temp memory like this files
    CmtFile test_vert = cmt_platform_read_file(&linear_allocator, "src/renderer/shader/test.vert");
    CmtFile test_frag = cmt_platform_read_file(&linear_allocator, "src/renderer/shader/test.frag");
    CmtShader *test_shader = renderer.load_shader(&renderer, test_vert.data, test_frag.data);

    CmtVertexBuffer *triangle_buffer = renderer.create_vertex_buffer(&renderer, vertices, sizeof(vertices));
    
    renderer.use_shader(&renderer, test_shader);
    renderer.use_vertex_buffer(&renderer, triangle_buffer);
#if 1
    renderer.set_uniform_m4(test_shader, "projection", m4_orthographic(0, 800, 0, 600, 0, 100));
#else
    renderer.set_uniform_m4(test_shader, "model", m4_translate(v3(0, 0, 4)));
    renderer.set_uniform_m4(test_shader, "projection", m4_perspective(60, 800/600, 0.1f, 100.0f));
#endif

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
                    if(event.key.keycode == 'M')
                    {
                        cmt_print_memory_registry();
                    }
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
    cmt_renderer_destroy(&linear_allocator, &renderer);
    cmt_platform_destroy(&platform);
    
    return 0;
}
