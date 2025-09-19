#pragma once

#include "serial_api.h"
#include "main.h"

void uart_buffered_enable(serial_t *obj);
int serial_recv_buffered(serial_t *obj, char *prxbuf, uint32_t len, uint32_t timeout_ms);
