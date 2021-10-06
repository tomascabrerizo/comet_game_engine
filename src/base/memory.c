#include "base/memory.h"
#include "platform/platform.h"

static u64 cmt_memory_registry[MEM_COUNT];

static char *cmt_tag_to_string(CmtMemoryTag tag)
{
    switch(tag)
    {
        case MEM_UNKNOW: return "UNKNOW";
        case MEM_LINEAR: return "LINEAR";
        case MEM_STACK: return "STACK";
        case MEM_POOL: return "POOL";
        case MEM_COUNT: 
        { 
            ASSERT(!"invalid code path MEM_COUNT cannot be string");
        };
    }
    return 0;
}

void cmt_print_memory_registry()
{
    for(CmtMemoryTag tag = 0; tag < MEM_COUNT; ++tag)
    {
        // TODO: use a custom loggin system insted of printf 
        printf("[MEMORY %s]: %lld bytes used\n", cmt_tag_to_string(tag), cmt_memory_registry[tag]);
    }
}

void *cmt_alloc(u64 size, CmtMemoryTag tag)
{
    cmt_memory_registry[tag] += size;
    void *result = cmt_platform_allocate(size);
    return result;
}

void cmt_free(void *mem, u64 size, CmtMemoryTag tag)
{
    cmt_memory_registry[tag] -= size;
    cmt_platform_release(mem, size); 
    mem = 0;
}

// NOTE: linear allocator

void cmt_linear_allocator_create(CmtAllocator *allocator, u64 size)
{
    // TODO: dont assert, report and error insted
    ASSERT(allocator);
    ASSERT(!allocator->mem);
    allocator->mem = cmt_alloc(size, MEM_LINEAR);
    allocator->used = 0;
    allocator->size = size;
    allocator->alloc = cmt_linear_alloc;
    allocator->clear = cmt_linear_clear;
    allocator->free = cmt_linear_free;
}

void cmt_linear_allocator_destroy(CmtAllocator *allocator)
{
    // TODO: dont assert, report and error insted
    ASSERT(allocator);
    cmt_free(allocator->mem, allocator->size, MEM_LINEAR);
    allocator->size = 0;
}

void *cmt_linear_alloc(CmtAllocator *allocator, u64 size, u64 align)
{
    // NOTE: must be a power of two
    ASSERT((align & (align - 1)) == 0);
    ASSERT(allocator->used + (size + align) < allocator->size);
    void *result = allocator->mem + allocator->used;
    allocator->used += (size + align);
    if(align > 0)
    {
        u32 pass_align = (u64)result & (align - 1);
        result = (u8 *)result + (align - pass_align);
    }
    return result;
}

void cmt_linear_free(CmtAllocator *allocator, void *mem, u64 size, u64 align)
{
    ASSERT(!"Error: linear allocators cannot free memory");
}

void cmt_linear_clear(CmtAllocator *allocator)
{
    allocator->used = 0;
}

// NOTE: pool allocator

void cmt_pool_allocator_create(CmtAllocator *allocator, u64 block_size, u64 count)
{
    ASSERT(block_size >= sizeof(CmtMemBlock));
    allocator->size = block_size * count;
    allocator->used = 0;
    allocator->mem = cmt_alloc(allocator->used, MEM_POOL);
    // NOTE: initialize the list of free pools
    allocator->block_size = block_size;
    allocator->pool = (CmtMemBlock *)allocator->mem;
    CmtMemBlock *block = allocator->pool;
    for(i32 i = 0; i < count; ++i)
    {
        block->mem = (u8 *)allocator->mem + (i * block_size);
        // NOTE: last block dont have next
        if(i < count-1)
        {
            block->next = (CmtMemBlock *)((u8 *)block->mem + block_size);
        }
        block = block->next;
    }

    // NOTE: set the allocator virtual table
    allocator->alloc = cmt_pool_alloc;
    allocator->clear = cmt_pool_clear;
    allocator->free = cmt_pool_free;
}

void cmt_pool_allocator_destroy(CmtAllocator *allocator)
{
    cmt_free(allocator->mem, allocator->size, MEM_POOL);
    allocator->size = 0;
    allocator->used = 0;
    allocator->pool = 0;
    allocator->block_size = 0;
}

void *cmt_pool_alloc(CmtAllocator *allocator, u64 size, u64 align)
{
    // NOTE: remove the first element of the pool list
    ASSERT(allocator->pool);
    CmtMemBlock *block = allocator->pool;
    allocator->pool = allocator->pool->next;
    return block->mem;
}

void cmt_pool_free(CmtAllocator *allocator, void *mem, u64 size, u64 align)
{
    // NOTE: add a new no to the top of the pool with the new free block 
    CmtMemBlock *block = mem;
    block->mem = mem;
    block->next = allocator->pool;
    allocator->pool = block;
}

void cmt_pool_clear(CmtAllocator *allocator)
{
    ASSERT(!"error: pool allocator clear not implemented");
}
