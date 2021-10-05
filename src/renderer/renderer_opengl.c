#include "renderer/renderer.h"
#include "platform/opengl/glad/glad.h"

typedef struct CmtShader
{
    u32 program;
} CmtShader;
typedef struct CmtVertexBuffer
{
    u32 buffer;
} CmtVertexBuffer;

#define CMT_MAX_NUM_SHADERS 256
#define CMT_MAX_NUM_BUFFERS 256
typedef struct CmtOpenglRendererState
{
    u32 vao;
    CmtShader shaders[CMT_MAX_NUM_SHADERS]; 
    u32 shaders_count;
    CmtVertexBuffer vertex_buffer[CMT_MAX_NUM_BUFFERS]; 
    u32 vertex_buffer_count;

} CmtOpenglRendererState;

void cmt_renderer_create(CmtAllocator *allocator, CmtRendererState *renderer)
{
    // NOTE: set up renderer virtual table
    renderer->begin = cmt_renderer_begin;
    renderer->end = cmt_renderer_end;
    renderer->load_shader = cmt_renderer_load_shader;
    renderer->use_shader = cmt_renderer_use_shader;
    renderer->create_vertex_buffer = cmt_renderer_create_vertex_buffer;
    renderer->use_vertex_buffer = cmt_renderer_use_vertex_buffer;
    
    renderer->set_uniform_f32 = cmt_renderer_set_uniform_f32;
    renderer->set_uniform_i32 = cmt_renderer_set_uniform_i32;
    renderer->set_uniform_v2 = cmt_renderer_set_uniform_v2; 
    renderer->set_uniform_v3 = cmt_renderer_set_uniform_v3;
    renderer->set_uniform_v4 = cmt_renderer_set_uniform_v4;
    renderer->set_uniform_m4 = cmt_renderer_set_uniform_m4;


    // TODO: the renderer must be able to access the platform
    glViewport(0, 0, 800, 600);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    
    ASSERT(!renderer->state);
    renderer->state = allocator->alloc(allocator, sizeof(CmtOpenglRendererState), 0);
    CmtOpenglRendererState *state = (CmtOpenglRendererState *)renderer->state;
    glCreateVertexArrays(1, &state->vao); 
    glBindVertexArray(state->vao);
}

void cmt_renderer_destroy(CmtAllocator *allocator, CmtRendererState *renderer)
{
    // TODO: loop all renderer arrays and destroy all programs and buffers
}

void cmt_renderer_begin(CmtRendererState *renderer)
{
    glClear(GL_COLOR_BUFFER_BIT);
}

void cmt_renderer_end(CmtRendererState *renderer)
{
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

CmtShader *cmt_renderer_load_shader(CmtRendererState *renderer, char *vert, char *frag)
{
    CmtOpenglRendererState *state = (CmtOpenglRendererState *)renderer->state;

    u32 v_shader = glCreateShader(GL_VERTEX_SHADER);
    u32 f_shader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(v_shader, 1, (const char **)&vert, 0);  
    glShaderSource(f_shader, 1, (const char **)&frag, 0);  

    glCompileShader(v_shader);
    i32 v_compile;
    glGetShaderiv(v_shader, GL_COMPILE_STATUS, &v_compile);
    if (v_compile != GL_TRUE)
    {
        GLsizei log_size = 0;
        char message[1024];
        glGetShaderInfoLog(v_shader, 1024, &log_size, message);
        printf("Fail to compile vertex shader:'%s'", message);
    }

    glCompileShader(f_shader);
    i32 f_compile;
    glGetShaderiv(f_shader, GL_COMPILE_STATUS, &f_compile);
    if (f_compile != GL_TRUE)
    {
        GLsizei log_size = 0;
        char message[1024];
        glGetShaderInfoLog(f_shader, 1024, &log_size, message);
        printf("Fail to compile fragment shader:'%s'", message);
    }
    
    ASSERT(state->shaders_count < CMT_MAX_NUM_SHADERS);
    CmtShader *shader = state->shaders + state->shaders_count++;
    shader->program = glCreateProgram();
    glAttachShader(shader->program, v_shader);
    glAttachShader(shader->program, f_shader);
    glLinkProgram(shader->program);
    
    i32 shader_program_link;
    glGetProgramiv(shader->program, GL_LINK_STATUS, &shader_program_link);
    if (shader_program_link != GL_TRUE)
    {
        GLsizei log_size = 0;
        char message[1024];
        glGetShaderInfoLog(shader->program, 1024, &log_size, message);
        printf("Fail to link shader shader_program:'%s'", message);
    }
    
    glDeleteShader(v_shader);
    glDeleteShader(f_shader);  

    return shader;
}

void cmt_renderer_use_shader(CmtRendererState *renderer, CmtShader *shader)
{
    glUseProgram(shader->program);
}

CmtVertexBuffer *cmt_renderer_create_vertex_buffer(CmtRendererState *renderer, void *data, u64 data_size)
{
    // TODO: add a buffer descriptor to pass into glVertexAttribPointer
    CmtOpenglRendererState *state = (CmtOpenglRendererState *)renderer->state;
    CmtVertexBuffer *result = state->vertex_buffer + state->vertex_buffer_count++;
    glCreateBuffers(1, &result->buffer); 
    glBindBuffer(GL_ARRAY_BUFFER, result->buffer);
    glBufferData(GL_ARRAY_BUFFER, data_size, data, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2*sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);
    return result;
}

void cmt_renderer_use_vertex_buffer(CmtRendererState *renderer, struct CmtVertexBuffer *vertex_buffer)
{
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer->buffer);
}

void cmt_renderer_set_uniform_f32(CmtShader *shader, char *name, f32 value)
{
    u32 location = glGetUniformLocation(shader->program, name);
    glUniform1f(location, value);
}
void cmt_renderer_set_uniform_i32(CmtShader *shader, char *name, i32 value)
{
    u32 location = glGetUniformLocation(shader->program, name);
    glUniform1i(location, value);
}
void cmt_renderer_set_uniform_v2(CmtShader *shader, char *name, v2 vec)
{
    u32 location = glGetUniformLocation(shader->program, name);
    glUniform2f(location, vec.x, vec.y);
}
void cmt_renderer_set_uniform_v3(CmtShader *shader, char *name, v3 vec)
{
    u32 location = glGetUniformLocation(shader->program, name);
    glUniform3f(location, vec.x, vec.y, vec.z);
}
void cmt_renderer_set_uniform_v4(CmtShader *shader, char *name, v4 vec)
{
    u32 location = glGetUniformLocation(shader->program, name);
    glUniform4f(location, vec.x, vec.y, vec.z, vec.w);
}
void cmt_renderer_set_uniform_m4(CmtShader *shader, char *name, m4 mat)
{
    u32 location = glGetUniformLocation(shader->program, name);
    glUniformMatrix4fv(location, 1, GL_FALSE, (f32 *)mat.m);
}
