#ifndef PLATFORM_H
#define PLATFORM_H

#include "base/base.h"
#include "base/memory.h"

typedef struct CmtPlatformState
{
    void *state;
} CmtPlatformState;

COMET void cmt_platform_create(CmtPlatformState *platform, char *app_name, u32 x, u32 y, u32 widht, u32 height);
COMET void cmt_platform_destroy(CmtPlatformState *platform);
COMET void cmt_platform_pump_events(CmtPlatformState* platform);
COMET void cmt_platform_swap_buffers(CmtPlatformState* platform);

void *cmt_platform_allocate(u64 size);
void cmt_platform_release(void *mem, u64 size);

typedef struct CmtFile
{
    void *data;
    u64 size;
} CmtFile;

CmtFile cmt_platform_read_file(CmtAllocator *allocator, char *path);

#endif // PLATFORM_H
