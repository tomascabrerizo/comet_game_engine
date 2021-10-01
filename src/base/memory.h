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

struct CmtAllocator;
typedef void *(*FpCmtAlloc)(struct CmtAllocator *allocator, u64 size, u64 align);
typedef void (*FpCmtFree)(struct CmtAllocator *allocator, u64 size, u64 align);
typedef void (*FpCmtClear)(struct CmtAllocator *allocator);

typedef struct CmtAllocator
{
    void *mem;
    u64 size;
    u64 used;

    FpCmtAlloc alloc;
    FpCmtClear clear;
    FpCmtFree free;

} CmtAllocator;

COMET void cmt_linear_allocator_create(CmtAllocator *allocator, u64 size);
COMET void cmt_linear_allocator_destroy(CmtAllocator *allocator);

void *cmt_linear_alloc(CmtAllocator *allocator, u64 size, u64 align);
void cmt_linear_free(CmtAllocator *allocator, u64 size, u64 align);
void cmt_linear_clear(CmtAllocator *allocator);

#endif // MEMORY_H
