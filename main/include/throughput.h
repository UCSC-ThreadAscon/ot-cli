#pragma once

#include "workload.h"

#define THROUGHPUT_URI "/throughput"
#define TP_PAYLOAD_BYTES 4

void tpConfirmable(otSockAddr *socket);
void tpPayload(uint8_t *buffer);