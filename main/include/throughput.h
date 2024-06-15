#pragma once

#include "workload.h"

#define THROUGHPUT_CONFIRMABLE_URI "confirmable"
#define THROUGHPUT_NONCONFIRMABLE_URI "nonconfirmable"

#define TP_PAYLOAD_BYTES 4

void createRandomPayload(uint8_t *buffer);
void tpMainConfirmable(void);
void tpMainNonconfirmable(void);