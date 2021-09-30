#include "base/event.h"

static CmtEventState cmt_global_event_queue;

void cmt_event_state_init(void)
{
    cmt_global_event_queue.count = 0;
    // TODO: memset the event state to zero
}
void cmt_event_state_clear(void)
{
    cmt_global_event_queue.count = 0;
}

void cmt_event_push(CmtEvent event)
{
    ASSERT(cmt_global_event_queue.count < CMT_MAX_NUM_EVENTS);
    cmt_global_event_queue.events[cmt_global_event_queue.count++] = event;
}

CmtEventState *cmt_event_get(CmtEvent event)
{
    return &cmt_global_event_queue;
}
