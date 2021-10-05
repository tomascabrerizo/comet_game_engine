#ifndef RENDERER_H
#define RENDERER_H

#include "base/base.h"
#include "base/memory.h"
#include "base/math.h"

struct CmtRendererState;
// NOTE: functions pointer to renderer virtual table
typedef void (*FpCmtRenderBegin)(struct CmtRendererState *renderer);
typedef void (*FpCmtRenderEnd)(struct CmtRendererState *renderer);
typedef struct CmtShader *(*FpCmtLoadShader)(struct CmtRendererState *renderer, char *vert, char *frag);
typedef void (*FpCmtUseShader)(struct CmtRendererState *renderer, struct CmtShader *shader);
typedef struct CmtVertexBuffer *(*FpCmtCreateVertexBuffer)(struct CmtRendererState *renderer, void *data, u64 data_size);
typedef void (*FpCmtUseVertexBuffer)(struct CmtRendererState *renderer, struct CmtVertexBuffer *vertex_buffer);

typedef void (*FpCmtSetUniformF32)(struct CmtShader *shader, char *name, f32 value);
typedef void (*FpCmtSetUniformI32)(struct CmtShader *shader, char *name, i32 value);
typedef void (*FpCmtSetUniformV2)(struct CmtShader *shader, char *name, v2 vec);
typedef void (*FpCmtSetUniformV3)(struct CmtShader *shader, char *name, v3 vec);
typedef void (*FpCmtSetUniformV4)(struct CmtShader *shader, char *name, v4 vec);
typedef void (*FpCmtSetUniformM4)(struct CmtShader *shader, char *name, m4 mat);

typedef struct CmtRendererState
{
    // NOTE: renderer virtual table
    FpCmtRenderBegin begin;
    FpCmtRenderEnd end;
    FpCmtLoadShader load_shader;
    FpCmtUseShader use_shader;
    FpCmtCreateVertexBuffer create_vertex_buffer;
    FpCmtUseVertexBuffer use_vertex_buffer;
    FpCmtSetUniformF32 set_uniform_f32;
    FpCmtSetUniformI32 set_uniform_i32;
    FpCmtSetUniformV2 set_uniform_v2; 
    FpCmtSetUniformV3 set_uniform_v3;
    FpCmtSetUniformV4 set_uniform_v4;
    FpCmtSetUniformM4 set_uniform_m4;
    // NOTE: renderer state
    void *state; 
} CmtRendererState;

COMET void cmt_renderer_create(CmtAllocator *allocator, CmtRendererState *renderer);
COMET void cmt_renderer_destroy(CmtAllocator *allocator, CmtRendererState *renderer);

void cmt_renderer_begin(CmtRendererState *renderer);
void cmt_renderer_end(CmtRendererState *renderer);

// NOTE: CmtShader is a hardware specific and can have differents implementations
struct CmtShader;
struct CmtVertexBuffer;

struct CmtShader *cmt_renderer_load_shader(CmtRendererState *renderer, char *vert, char *frag);
void cmt_renderer_use_shader(CmtRendererState *renderer, struct CmtShader *shader);

struct CmtVertexBuffer *cmt_renderer_create_vertex_buffer(CmtRendererState *renderer, void *data, u64 data_size);
void cmt_renderer_use_vertex_buffer(CmtRendererState *renderer, struct CmtVertexBuffer *vertex_buffer);

// NOTE: shaders uniforms
void cmt_renderer_set_uniform_f32(struct CmtShader *shader, char *name, f32 value);
void cmt_renderer_set_uniform_i32(struct CmtShader *shader, char *name, i32 value);
void cmt_renderer_set_uniform_v2(struct CmtShader *shader, char *name, v2 vec);
void cmt_renderer_set_uniform_v3(struct CmtShader *shader, char *name, v3 vec);
void cmt_renderer_set_uniform_v4(struct CmtShader *shader, char *name, v4 vec);
void cmt_renderer_set_uniform_m4(struct CmtShader *shader, char *name, m4 mat);

#endif // RENDERER_H
