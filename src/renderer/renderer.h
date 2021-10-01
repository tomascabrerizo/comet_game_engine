#ifndef RENDERER_H
#define RENDERER_H

#include "base/base.h"
#include "base/memory.h"

typedef struct CmtRendererState
{
    void *state; 
} CmtRendererState;

void cmt_renderer_create(CmtAllocator *allocator, CmtRendererState *renderer);
void cmt_renderer_destroy(CmtAllocator *allocator, CmtRendererState *renderer);

void cmt_renderer_load_shader(CmtRendererState *renderer, char *path);

void cmt_renderer_begin(CmtRendererState *renderer);
void cmt_renderer_end(CmtRendererState *renderer);

#endif // RENDERER_H
