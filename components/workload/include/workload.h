#pragma once

#include "dependencies.h"
#include "inline.h"
#include "print_macro.h"
#include "macro.h"

/* ---- Common API ---- */
void checkConnection(otInstance *aInstance);
void handleError(otError error, char* desc);
void printMeshLocalEid(otInstance *aInstance);

/** ---- CoAP Common API ---- */
uint16_t getPayloadLength(const otMessage *aMessage);
void getPayload(const otMessage *aMessage, void* buffer);
otSockAddr createSocket(const char *recvAddrString);
void coapStart(void);

/* ---- CoAP Client API ---- */
void request(otSockAddr *socket,
             void *payload,
             size_t payloadSize,
             const char *uri);

/* ---- CoAP Response Handler ---- */
void responseCallback(void *aContext,
                      otMessage *aMessage,
                      const otMessageInfo *aMessageInfo,
                      otError aResult);