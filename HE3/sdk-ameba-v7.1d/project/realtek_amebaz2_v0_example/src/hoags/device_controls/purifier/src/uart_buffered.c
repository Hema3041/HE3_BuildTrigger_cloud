#include "uart_buffered.h"
#include "FreeRTOS.h"
#include "task.h"
#include <stdio.h>
#include <string.h>

extern struct serial_s superFanObj;
#define UART_RX_BUFFER_SIZE 51

typedef struct {
    uint8_t buffer[UART_RX_BUFFER_SIZE];
    volatile uint16_t head;
    volatile uint16_t tail;
} CircularBuffer;

static CircularBuffer rxBuf;
volatile uint32_t uart_overflow_count = 0;

int __wrap_putchar(int ch)
{
    // Example: send character to UART1
    serial_putc(&superFanObj, (char)ch); // Assuming superFanObj is initialized
    return ch;
}

void resetUartCount(){
    uart_overflow_count = 0;
}


static int buffer_get(CircularBuffer *cb, uint8_t *data) {
    if (cb->head == cb->tail) return 0;
    *data = cb->buffer[cb->tail];
    cb->tail = (cb->tail + 1) % UART_RX_BUFFER_SIZE;
    return 1;
}

static void uart_rx_irq_handler(uint32_t id, SerialIrq event) {
    serial_t *obj = (serial_t *)id;

    if (event == RxIrq) {
        while (serial_readable(obj)) {
            uint8_t byte = serial_getc(obj);
            uint16_t next = (rxBuf.head + 1) % UART_RX_BUFFER_SIZE;

            if (next != rxBuf.tail) {
                rxBuf.buffer[rxBuf.head] = byte;
                rxBuf.head = next;
            } else {
                uart_overflow_count++;
            }
        }
    }
}

void uart_buffered_enable(serial_t *obj) {
    rxBuf.head = rxBuf.tail = 0;

    serial_irq_handler(obj, uart_rx_irq_handler, (uint32_t)obj);
    serial_irq_set(obj, RxIrq, 1);
}

int serial_recv_buffered(serial_t *obj, char *prxbuf, uint32_t len, uint32_t timeout_ms) {
    TickType_t startTick = xTaskGetTickCount();
    uint32_t count = 0;

    while (count < len) {
        if (buffer_get(&rxBuf, (uint8_t *)&prxbuf[count])) {
            count++;
        } else {
            if ((xTaskGetTickCount() - startTick) * portTICK_PERIOD_MS >= timeout_ms) {
                break;
            }
            vTaskDelay(pdMS_TO_TICKS(1));
        }
    }

    if (count > 0) {
        //printf("serial_recv_buffered(): Received %d/%d bytes\n", count, len);
        //printf("  ");
        // for (uint32_t i = 0; i < count; i++) {
        //     printf("%02X ", (uint8_t)prxbuf[i]);
        // }
        // printf("\n");
    } else {
        printf("serial_recv_buffered(): Timeout, received 0 bytes\n");
    }

    if ((uart_overflow_count != 0)) {
        if(uart_overflow_count >= 10000){
            printf("REBOOTING AT COUNT: %d\n",uart_overflow_count);
            rebootRenesas();
            uart_overflow_count = 0;
            //printf("UART RX BUFFER OVERFLOW occurred %lu times during receive\n", uart_overflow_count);
        }
    }

    return count;
}
