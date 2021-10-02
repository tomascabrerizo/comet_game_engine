#ifndef RENDERER_H
#define RENDERER_H

#include "base/base.h"
#include "base/memory.h"

struct CmtRendererState;
// NOTE: functions pointer to renderer virtual table
typedef void (*FpCmtRenderBegin)(struct CmtRendererState *renderer);
typedef void (*FpCmtRenderEnd)(struct CmtRendererState *renderer);
typedef struct CmtShader *(*FpCmtLoadShader)(struct CmtRendererState *renderer, char *vert, char *frag);
typedef void (*FpCmtUseShader)(struct CmtRendererState *renderer, struct CmtShader *shader);
typedef struct CmtVertexBuffer *(*FpCmtCreateVertexBuffer)(struct CmtRendererState *renderer, void *data, u64 data_size);
typedef void (*FpCmtUseVertexBuffer)(struct CmtRendererState *renderer, struct CmtVertexBuffer *vertex_buffer);

typedef struct CmtRendererState
{
    // NOTE: renderer virtual table
    FpCmtRenderBegin begin;
    FpCmtRenderEnd end;
    FpCmtLoadShader load_shader;
    FpCmtUseShader use_shader;
    FpCmtCreateVertexBuffer create_vertex_buffer;
    FpCmtUseVertexBuffer use_vertex_buffer;
    // NOTE: renderer state
    void *state; 
} CmtRendererState;

void cmt_renderer_create(CmtAllocator *allocator, CmtRendererState *renderer);
void cmt_renderer_destroy(CmtAllocator *allocator, CmtRendererState *renderer);

void cmt_renderer_begin(CmtRendererState *renderer);
void cmt_renderer_end(CmtRendererState *renderer);

// NOTE: CmtShader is a hardware specific and can have differents implementations
struct CmtShader;
struct CmtVertexBuffer;

struct CmtShader *cmt_renderer_load_shader(CmtRendererState *renderer, char *vert, char *frag);
void cmt_renderer_use_shader(CmtRendererState *renderer, struct CmtShader *shader);

struct CmtVertexBuffer *cmt_renderer_create_vertex_buffer(CmtRendererState *renderer, void *data, u64 data_size);
void cmt_renderer_use_vertex_buffer(CmtRendererState *renderer, struct CmtVertexBuffer *vertex_buffer);

#endif // RENDERER_H
