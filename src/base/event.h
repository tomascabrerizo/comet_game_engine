#ifndef EVENT_H
#define EVENT_H

#include "base/base.h"

typedef enum CmtEventType
{
    CMT_TEST_EVENT,
    CMT_QUIT_EVENT,
    CMT_KEYDOWN_EVENT,
    CMT_KEYUP_EVENT,
} CmtEventType;

#define CMT_CREATE_EVENT(name, ...) typedef struct name { CmtEventType type; __VA_ARGS__ } name
CMT_CREATE_EVENT(CmtTestEvent,
    u8 state0;
    u8 state1;
    u8 state2;
);
CMT_CREATE_EVENT(CmtQuitEvent,
    b8 state;
);
CMT_CREATE_EVENT(CmtKeyEvent,
    u8 keycode;
    b8 state;
);

typedef union CmtEvent
{
    CmtEventType type;
    CmtQuitEvent quit;
    CmtKeyEvent key;
    CmtTestEvent test;
} CmtEvent;

#define CMT_MAX_NUM_EVENTS 256
typedef struct CmtEventState
{
    CmtEvent events[CMT_MAX_NUM_EVENTS];
    u32 head;
    u32 tail;
} CmtEventState;

void cmt_event_push(CmtEvent event);
b8 cmt_event_get(CmtEvent *event);

#endif // EVENT_H
