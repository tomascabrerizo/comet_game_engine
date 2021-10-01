#include "base/event.h"

static CmtEventState cmt_global_event_queue;

void cmt_event_push(CmtEvent event)
{
    ASSERT(cmt_global_event_queue.tail < CMT_MAX_NUM_EVENTS);
    if(cmt_global_event_queue.tail < CMT_MAX_NUM_EVENTS)
    {
        cmt_global_event_queue.events[cmt_global_event_queue.tail++] = event;
    }
}

b8 cmt_event_get(CmtEvent *event)
{
    if(cmt_global_event_queue.head < cmt_global_event_queue.tail)
    {
        *event = cmt_global_event_queue.events[cmt_global_event_queue.head];
        cmt_global_event_queue.head++;
        return true;
    }
    else
    {
        cmt_global_event_queue.head = 0;
        cmt_global_event_queue.tail = 0;
        return false;
    }
}
