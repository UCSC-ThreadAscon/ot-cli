#include "tight_loop.h"

static otSockAddr socket;

#define InitSocket(socketPtr)                            \
  EmptyMemory(socketPtr, sizeof(otSockAddr));            \
  *socketPtr = createSocket(CONFIG_SERVER_IP_ADDRESS);   \

void createRandomPayload(uint8_t *buffer) {
  uint32_t random = esp_random();
  memcpy(buffer, &random, TIGHT_LOOP_PAYLOAD_BYTES);
  return;
}

void confirmableSend(otSockAddr *socket)
{
  uint32_t payload = 0;
  createRandomPayload((uint8_t *) &payload);
  request(socket, (void *) &payload, TIGHT_LOOP_PAYLOAD_BYTES, CONFIRMABLE_URI,
          confirmableResponseCallback, OT_COAP_TYPE_CONFIRMABLE);
  return;
}

void nonConfirmableSend(otSockAddr *socket)
{
  uint32_t payload = 0;
  createRandomPayload((uint8_t *) &payload);
  request(socket, (void *) &payload, TIGHT_LOOP_PAYLOAD_BYTES, NONCONFIRMABLE_URI,
          NULL, OT_COAP_TYPE_NON_CONFIRMABLE);
  return;
}

void confirmableResponseCallback(void *aContext,
                                   otMessage *aMessage,
                                   const otMessageInfo *aMessageInfo,
                                   otError aResult)
{
  defaultResponseCallback(aContext, aMessage, aMessageInfo, aResult);
  confirmableSend(&socket); // send a request after getting a response.
  return;
}

/**
 * Create the socket, and send the first CoAP Confirmable Request.
 * All subsequent requests will be sent by the response handler.
 */
void ConfirmableMain()
{
  InitSocket(&socket);
  confirmableSend(&socket);
  KEEP_THREAD_ALIVE();
  return;
}

void NonConfirmableMain()
{
  InitSocket(&socket);
  while (true) {
    nonConfirmableSend(&socket);
  }

  KEEP_THREAD_ALIVE();
  return;
}