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

void cmt_linear_free(CmtAllocator *allocator, u64 size, u64 align)
{
    ASSERT(!"Error: linears allocator cannot free memory\n");
}

void cmt_linear_clear(CmtAllocator *allocator)
{
    allocator->used = 0;
}
