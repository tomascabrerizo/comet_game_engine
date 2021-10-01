#include <stdio.h>

#include "base/base.h"
#include "platform/platform.h"
#ifdef PLATFORM_WIN32
#include "platform/platform_win32.c"
#endif
#include "base/memory.h"
#include "base/memory.c"
#include "base/event.h"
#include "base/event.c"

#include "renderer/renderer.h"
#include "renderer/renderer_opengl.c"

static b8 global_running;

f32 vertices[6] =
{
    -0.5f, -0.5f,
     0.5f, -0.5f,
     0.0f,  0.5f,
};
u32 vao;
u32 triangle_buffer;
u32 shader_program;

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

void setup_opengl_shaders(void)
{
    u32 v_shader = glCreateShader(GL_VERTEX_SHADER);
    u32 f_shader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(v_shader, 1, (const char **)&triangle_vert_shader, 0);  
    glShaderSource(f_shader, 1, (const char **)&triangle_frag_shader, 0);  

    glCompileShader(v_shader);
    i32 v_compile;
    glGetShaderiv(v_shader, GL_COMPILE_STATUS, &v_compile);
    if (v_compile != GL_TRUE)
    {
        GLsizei log_size = 0;
        char message[1024];
        glGetShaderInfoLog(v_shader, 1024, &log_size, message);
        printf("Failt to compile vertex shader:'%s'", message);
    }

    glCompileShader(f_shader);
    i32 f_compile;
    glGetShaderiv(f_shader, GL_COMPILE_STATUS, &f_compile);
    if (f_compile != GL_TRUE)
    {
        GLsizei log_size = 0;
        char message[1024];
        glGetShaderInfoLog(f_shader, 1024, &log_size, message);
        printf("Failt to compile fragment shader:'%s'", message);
    }

    shader_program = glCreateProgram();
    glAttachShader(shader_program, v_shader);
    glAttachShader(shader_program, f_shader);
    glLinkProgram(shader_program);
    
    i32 shader_program_link;
    glGetProgramiv(shader_program, GL_LINK_STATUS, &shader_program_link);
    if (shader_program_link != GL_TRUE)
    {
        GLsizei log_size = 0;
        char message[1024];
        glGetShaderInfoLog(shader_program, 1024, &log_size, message);
        printf("Failt to link shader shader_program:'%s'", message);
    }
    
    glDeleteShader(v_shader);
    glDeleteShader(f_shader);  
}

void setup_opengl_triangle(void)
{
    glCreateVertexArrays(1, &vao); 
    glBindVertexArray(vao);
    glCreateBuffers(1, &triangle_buffer); 
    glBindBuffer(GL_ARRAY_BUFFER, triangle_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2*sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);
}

void draw_opengl_triangle(void)
{
    glUseProgram(shader_program);
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, triangle_buffer);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

int main(void)
{
    CmtPlatformState platform = {0};
    cmt_platform_create(&platform, "Comet Game Engine", 100, 100, 800, 600);
    
    CmtAllocator linear_allocator = {0};
    cmt_linear_allocator_create(&linear_allocator, MB(64));
    
    CmtRendererState renderer = {0};
    cmt_renderer_create(&linear_allocator, &renderer);
    
    u32 *u32_align = linear_allocator.alloc(&linear_allocator, sizeof(u32), 4);
    u64 *u64_align = linear_allocator.alloc(&linear_allocator, sizeof(u64), 8);
    printf("4 bytes align: %llx\n", (u64)u32_align);
    printf("8 bytes align: %llx\n", (u64)u64_align);
    
    CmtFile file = cmt_platform_read_file(&linear_allocator, "src/main.c");
    (void)file;

    cmt_print_memory_registry();

    setup_opengl_shaders();
    setup_opengl_triangle();
    
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
        
        cmt_renderer_begin(&renderer); 
        draw_opengl_triangle();
        cmt_renderer_end(&renderer); 
        
        cmt_platform_swap_buffers(&platform);
    }
    cmt_platform_destroy(&platform);
    
    return 0;
}
