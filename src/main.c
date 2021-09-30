#include <stdio.h>

#include "base/base.h"
#include "platform/platform.h"
#ifdef PLATFORM_WIN32
#include "platform/platform_win32.c"
#endif
#include "base/memory.h"
#include "base/memory.c"
#include "base/event.h"
#include "base/event.c"

static b8 global_running;

int main(void)
{
    CmtPlatformState platform = {0};
    cmt_platform_create(&platform, "Comet Game Engine", 100, 100, 800, 600);
    
    CmtLinearAllocator allocator = {0};
    cmt_linear_allocator_create(&allocator, MB(64));
    
    u32 *u32_array = cmt_linear_alloc(&allocator, sizeof(u32)*10, 4);
    u64 *u64_array = cmt_linear_alloc(&allocator, sizeof(u64)*10, 8);
    
    for(i32 i = 0; i < 10; ++i)
    {
        u32_array[i] = i;
    }
    for(i32 i = 0; i < 10; ++i)
    {
        u64_array[i] = 10 - i;
    }
    printf("------u32-array------\n");
    for(i32 i = 0; i < 10; ++i)
    {
        printf("%d\n", u32_array[i]);
    }
    printf("------u64-array------\n");
    for(i32 i = 0; i < 10; ++i)
    {
        printf("%lld\n", u64_array[i]);
    }

    u32 *u32_align = cmt_linear_alloc(&allocator, sizeof(u32), 4);
    u64 *u64_align = cmt_linear_alloc(&allocator, sizeof(u64), 8);
    printf("4 bytes align: %llx\n", (u64)u32_align);
    printf("8 bytes align: %llx\n", (u64)u64_align);

    cmt_print_memory_registry();
    
    global_running = true;
    while(global_running)
    {
        cmt_platform_pump_events(&platform);
        CmtEvent event;
        while(cmt_event_get(&event))
        {
            switch(event.type)
            {
                case CMT_QUIT_EVENT:
                {
                    printf("key quit event!\n");
                    global_running = false;
                }break;
                case CMT_KEYDOWN_EVENT:
                {
                    printf("'%c' key down event!\n", event.key.keycode);
                }break;
                case CMT_KEYUP_EVENT:
                {
                }break;
                case CMT_TEST_EVENT:
                {
                    printf("test event!\n");
                }break;
            }
        }
    }
    cmt_platform_destroy(&platform);
    
    return 0;
}
