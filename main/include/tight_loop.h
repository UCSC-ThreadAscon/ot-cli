#pragma once

#include "workload.h"

#define CONFIRMABLE_URI "confirmable"
#define NONCONFIRMABLE_URI "nonconfirmable"

#define TIGHT_LOOP_PAYLOAD_BYTES 4

void createRandomPayload(uint8_t *buffer);
void ConfirmableMain(void);
void NonConfirmableMain(void);