#pragma once

#include "workload.h"

#define InitSocket(socketPtr)                            \
  EmptyMemory(socketPtr, sizeof(otSockAddr));            \
  *socketPtr = createSocket(SERVER_IP_ADDRESS);          \

#if DELAY_CLIENT
#define SERVER_IP_ADDRESS CONFIG_DELAY_SERVER_IP_ADDRESS
#else
#define SERVER_IP_ADDRESS CONFIG_SERVER_IP_ADDRESS
#endif