#include "circularbuffer.h"
#include "hoags_config.h"


circular_buffer cbObj;
circular_buffer* cb = &cbObj;
int audioReady = 0;
extern BOOL lifeSpanOver;

#if HOAGS_UART_DUMP
extern struct serial_s dumpUartObj;

static void ExtractAudio(void *param)
{
    circular_buffer *cb = (circular_buffer *) param;
    printf ("Extract Audio thread started %d\n", cb->sz);
    while (1) {
        cb_pop_front(cb);
    }
}

void dump_audio_buffers (circular_buffer *cb) {
    char *dump_buffer = hoagsMalloc(cb->sz);

    while (1) {
        if (cb_pop_front(cb) == NULL) {
            break;
        }
    }
    printf ("Dumping input buffer\n");
    uart_send_bytes(&dumpUartObj, "in", 2);
    while (1) {
        if (xQueueReceive(cb->audioInputQueue, dump_buffer, 0) == pdTRUE) {
            uart_send_bytes(&dumpUartObj, dump_buffer, cb->sz);
        } else {
            break;
        }
    }
    printf ("Dumping output buffer\n");
    uart_send_bytes(&dumpUartObj, "ot", 2);
    while (1) {
        if (xQueueReceive(cb->audioOutputQueue, dump_buffer, 0) == pdTRUE) {
            uart_send_bytes(&dumpUartObj, dump_buffer, cb->sz);
        } else {
            break;
        }
    }

}
#endif

short int cb_init(circular_buffer *cb, size_t capacity, size_t sz)
{
    cb->buffer = hoagsMalloc(capacity * sz);
    if(cb->buffer == NULL) {
        HOAGS_ERR(" Error!!!\n");
        return -1;
    }

    cb->freeBufQueue = xQueueCreate(capacity+1, sizeof (char *));
    for (int i = 0; i < capacity; i++) {
        char * buffer = cb->buffer + (i * sz);
        xQueueSend(cb->freeBufQueue, (void *)&buffer, 0);
    }
    cb->audioBufQueue = xQueueCreate( capacity+1, sizeof(char *));
    printf ("Created audio buffer queue\n");
    cb->capacity = capacity;
    cb->count = 0;
    cb->sz = sz;

#if HOAGS_UART_DUMP
    cb->audioInputQueue = xQueueCreate( capacity+1, sz);
    cb->audioOutputQueue = xQueueCreate( capacity+1, sz);
	//if (pdTRUE != xTaskCreate(ExtractAudio, ((const char *)"ExtractAudio"), 4096, cb, tskIDLE_PRIORITY + 1, NULL)) {
	//	printf("=> E/AudioRecordExample:%s xTaskCreate(ExtractAudio) failed \n", __FUNCTION__);
	//}
#endif
    #if CIRCULAR_BUF_LOGGING
    HOAGS_DBG("Start=%p end=%p\n", cb->buffer, cb->buffer_end);
    #endif
    return 0;
}

void cb_free(circular_buffer *cb)
{
    free(cb->buffer);
    // clear out other fields too, just to be safe
}

void * cb_pop_front_simple(circular_buffer *cb) {
    void *item;
    if (xQueueReceive(cb->audioBufQueue, &item, 0) != pdTRUE) {
        return NULL;
    }
    return item;
}

char * cb_get_buffer_rotate(circular_buffer *cb) {
    char *buffer;
    if (xQueueReceive(cb->freeBufQueue, &buffer, 0) != pdTRUE) {
        return cb_pop_front_simple(cb);
    }
    return buffer;
}

char * cb_get_buffer(circular_buffer *cb) {
    char *buffer;
    if (xQueueReceive(cb->freeBufQueue, &buffer, 0) != pdTRUE) {
        HOAGS_ERR("cb_get_buffer failed\n");
        return NULL;
    }
    return buffer;
}

short cb_push_back(circular_buffer *cb, const void *item)
{
    if (xQueueSend(cb->audioBufQueue, &item, 0) != pdTRUE) {
        HOAGS_ERR("cb_push_back failed\n");
        return 0;
    }
    return 1;
}

void cb_free_buffer (circular_buffer *cb, void *item)
{
    if (xQueueSend(cb->freeBufQueue, &item, 0) != pdTRUE) {
        HOAGS_ERR("cb_free_buffer failed\n");        
    }
}

static int noiseReductionEnable = 1;
void SetNoiseReduction(int enable) {
    HOAGS_INFO("Noise Reduction %s\n", (enable == 0) ? "disabled" : "enabled"); 
    noiseReductionEnable = enable;
}

void * cb_pop_front(circular_buffer *cb)
{
    if(lifeSpanOver)
        return NULL;

    void *item;
    
#if HOAGS_SPEEX_NR
    void *st =(void *) Get_Speex_Handle();
#endif

#if HOAGS_UART_DUMP
    if (xQueueReceive(cb->audioBufQueue, &item, 0) != pdTRUE) {
        HOAGS_ERR("cb_pop_front failed\n");
        return NULL;
    }
#else
    if (xQueueReceive(cb->audioBufQueue, &item, portMAX_DELAY) != pdTRUE) {
        HOAGS_ERR("cb_pop_front failed\n");
        return NULL;
    }
#endif
#if HOAGS_UART_DUMP
    if (xQueueSend(cb->audioInputQueue, item, 0) != pdTRUE) {
        HOAGS_ERR("cb_push_back to extract queue failed\n");
    }
#endif

#if HOAGS_SPEEX_NR
    if (noiseReductionEnable == 1) {
        speex_preprocess_run(st, item);
    }
#endif

#if HOAGS_UART_DUMP
    if (xQueueSend(cb->audioOutputQueue, item, 0) != pdTRUE) {
        HOAGS_ERR("cb_pop_front push to extract queue failed\n");
    }
#endif
    return item;
}
