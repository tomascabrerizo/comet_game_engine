#ifndef MEMORY_H
#define MEMORY_H

#include "base/base.h"

// NOTE: memory defines
#define KB(value) (  (value) * 1024ll)
#define MB(value) (KB(value) * 1024ll)
#define GB(value) (MG(value) * 1024ll)

typedef enum CmtMemoryTag
{
    MEM_UNKNOW,
    MEM_LINEAR,
    MEM_STACK,

    // NOTE: must be the last member of the enum
    MEM_COUNT,
} CmtMemoryTag;
void cmt_print_memory_registry();

COMET void *cmt_alloc(u64 size, CmtMemoryTag tag);
COMET void cmt_free(void *mem, u64 size, CmtMemoryTag tag);

typedef struct CmtLinearAllocator
{
    void *mem;
    u64 size;
    u64 used;
} CmtLinearAllocator;

COMET void cmt_linear_allocator_create(CmtLinearAllocator *allocator, u64 size);
COMET void cmt_linear_allocator_destroy(CmtLinearAllocator *allocator);

COMET void *cmt_linear_alloc(CmtLinearAllocator *allocator, u64 size, u64 align);
COMET void cmt_linear_clear(CmtLinearAllocator *allocator);

#endif // MEMORY_H
