#ifndef EVENT_H
#define EVENT_H

#include "base/base.h"

typedef enum CmtEventType
{
    CMT_QUIT_EVENT,
    CMT_KEYDOWN_EVENT,
    CMT_KEYUP_EVENT,
} CmtEventType;

#define CMT_CREATE_EVENT(name, ...) typedef struct name { CmtEventType type; __VA_ARGS__ } name;
CMT_CREATE_EVENT(CmtQuitEvent,
    b8 quit;
)
CMT_CREATE_EVENT(CmtKeyEvent,
    u8 key;
    b8 state;
)

typedef union CmtEvent
{
    CmtEventType type;
    CmtQuitEvent quit;
    CmtKeyEvent key;
} CmtEvent;

#define CMT_MAX_NUM_EVENTS 1024
typedef struct CmtEventState
{
    CmtEvent events[CMT_MAX_NUM_EVENTS];
    u32 count;
} CmtEventState;

void cmt_event_state_init(void);
void cmt_event_state_clear(void);

void cmt_event_push(CmtEvent event);
CmtEventState *cmt_event_get(CmtEvent event);

#endif // EVENT_H
