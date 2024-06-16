#pragma once

#include "workload.h"

#define THROUGHPUT_CONFIRMABLE_URI "throughput-confirmable"
#define THROUGHPUT_NONCONFIRMABLE_URI "throughput-nonconfirmable"
#define PACKET_LOSS_CONFIRMABLE_URI "packet-loss-confirmable"
#define PACKET_LOSS_NONCONFIRMABLE_URI "packet-loss-nonconfirmable"

#define TIGHT_LOOP_PAYLOAD_BYTES 4

void createRandomPayload(uint8_t *buffer);
void tpConfirmableMain(void);
void tpNonConfirmableMain(void);