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
    MEM_POOL,

    // NOTE: must be the last member of the enum
    MEM_COUNT,
} CmtMemoryTag;
void cmt_print_memory_registry();

COMET void *cmt_alloc(u64 size, CmtMemoryTag tag);
COMET void cmt_free(void *mem, u64 size, CmtMemoryTag tag);

struct CmtAllocator;
typedef void *(*FpCmtAlloc)(struct CmtAllocator *allocator, u64 size, u64 align);
typedef void (*FpCmtFree)(struct CmtAllocator *allocator, void *mem, u64 size, u64 align);
typedef void (*FpCmtClear)(struct CmtAllocator *allocator);

typedef struct CmtAllocator
{
    void *mem;
    u64 size;
    u64 used;
    
    // NOTE: list used in pool allocator to get free mem blocks
    struct CmtMemBlock *pool;
    u64 block_size;

    FpCmtAlloc alloc;
    FpCmtClear clear;
    FpCmtFree free;
} CmtAllocator;

// NOTE: linear allocator
COMET void cmt_linear_allocator_create(CmtAllocator *allocator, u64 size);
COMET void cmt_linear_allocator_destroy(CmtAllocator *allocator);

void *cmt_linear_alloc(CmtAllocator *allocator, u64 size, u64 align);
void cmt_linear_free(CmtAllocator *allocator, void *mem, u64 size, u64 align);
void cmt_linear_clear(CmtAllocator *allocator);

// NOTE: pool allocator
typedef struct CmtMemBlock
{
    void *mem;
    struct CmtMemBlock *next;
} CmtMemBlock;

COMET void cmt_pool_allocator_create(CmtAllocator *allocator, u64 block_size, u64 count);
COMET void cmt_pool_allocator_destroy(CmtAllocator *allocator);

void *cmt_pool_alloc(CmtAllocator *allocator, u64 size, u64 align);
void cmt_pool_free(CmtAllocator *allocator, void *mem, u64 size, u64 align);
void cmt_pool_clear(CmtAllocator *allocator);

#endif // MEMORY_H
