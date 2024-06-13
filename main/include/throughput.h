#pragma once

#include "workload.h"

#define THROUGHPUT_URI "throughput"
#define TP_PAYLOAD_BYTES 4

void createRandomPayload(uint8_t *buffer);
void tpMain(void);