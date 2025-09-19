#ifndef __HOAGS_CIRCULAR_BUFFER__H__
#define __HOAGS_CIRCULAR_BUFFER__H__

#include "stddef.h"
#include "hoags_config.h"
#include "FreeRTOS.h"
#include "semphr.h"

#define CIRCULAR_BUF_LOGGING 0

//extern char acb[HOAGS_AUDIO_BUFF_SIZE];

typedef struct circular_buffer
{
    void *buffer;     // data buffer
    void *buffer_end; // end of data buffer
    size_t capacity;  // maximum number of items in the buffer
    size_t count;     // number of items in the buffer
    size_t sz;        // size of each item in the buffer
    QueueHandle_t freeBufQueue;
    QueueHandle_t audioBufQueue;
#if HOAGS_UART_DUMP
    QueueHandle_t audioInputQueue;
    QueueHandle_t audioOutputQueue;
#endif
} circular_buffer;

short int cb_init(circular_buffer *cb, size_t capacity, size_t sz);
void cb_free(circular_buffer *cb);
short cb_push_back(circular_buffer *cb, const void *item);
void * cb_pop_front(circular_buffer *cb);
short cb_is_empty(circular_buffer* cb);

#endif