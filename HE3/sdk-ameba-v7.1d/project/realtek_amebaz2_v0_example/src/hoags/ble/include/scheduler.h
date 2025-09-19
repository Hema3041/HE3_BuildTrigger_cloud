#ifndef SCHEDULER_INCLUDE_H
#define SCHEDULER_INCLUDE_H

#include "time.h"
#include "FreeRTOS.h"

#define SCHEDULER_MSG_SIZE 21

typedef enum ScheduleEventSource_ {
  SCHEDULED_BY_APP,
  SCHEDULED_BY_BOOTUP
}ScheduleEventSource;

typedef enum ScheduleEventType_ {
  EVENT_ADD,
  EVENT_REMOVE,
  EVENT_DISABLE,
  EVENT_ENABLE,
  TIME_UPDATE,
}ScheduleEventType;

typedef enum RecurringEventType_ {
  SCHEDULE_ONCE,
  SCHEDULE_CUSTOM
}RecurringEventType;

typedef enum ScheduleDay_ {
  SCHEDULE_SUNDAY = (1 << 0),
  SCHEDULE_MONDAY = (1 << 1),
  SCHEDULE_TUESDAY = (1 << 2),
  SCHEDULE_WEDNESDAY = (1 << 3),
  SCHEDULE_THURSDAY = (1 << 4),
  SCHEDULE_FRIDAY = (1 << 5),
  SCHEDULE_SATURDAY = (1 << 6),
  SCHEDULE_TODAY = (1 << 7)
}ScheduleDay;

typedef struct ScheduledEventItem_ {
    RecurringEventType recurringType;
    ScheduleDay day;
    time_t time;
    int event;
    unsigned int uniqueId;
    struct ScheduledEvent_ *next;
} ScheduledEventItem;

typedef struct ScheduleEventMsg_ {
    ScheduleEventSource source;
    unsigned char *pMsg;
    time_t currentTime; 
    ScheduleEventType type;
    RecurringEventType recurringType;
    ScheduleDay day;
    time_t time;
    unsigned int uniqueId;
    int event;
} ScheduleEventMsg;

extern QueueHandle_t getSchedulerQueueHandle();
void printEvents();
void addEventScheduleMessage(char *blePayload);
#endif
