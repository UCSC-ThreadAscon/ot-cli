#include "throughput.h"

static otSockAddr socket;

void createRandomPayload(uint8_t *buffer) {
  uint32_t random = esp_random();
  memcpy(buffer, &random, TP_PAYLOAD_BYTES);
  return;
}

void tpConfirmableSend(otSockAddr *socket)
{
  uint32_t payload = 0;
  createRandomPayload((uint8_t *) &payload);
  request(socket, (void *) &payload, TP_PAYLOAD_BYTES, THROUGHPUT_URI,
          tpConfirmableResponseCallback, OT_COAP_TYPE_CONFIRMABLE);
  return;
}

void tpConfirmableResponseCallback(void *aContext,
                                   otMessage *aMessage,
                                   const otMessageInfo *aMessageInfo,
                                   otError aResult)
{
  defaultResponseCallback(aContext, aMessage, aMessageInfo, aResult);
  tpConfirmableSend(&socket); // send a request after getting a response.
  return;
}

void tpConfirmableInit(otSockAddr *socket)
{
  *socket = createSocket(CONFIG_SERVER_IP_ADDRESS);
  tpConfirmableSend(socket); // send the first request.
  return;
}

void tpMainConfirmable()
{
  EmptyMemory(&socket, sizeof(otSockAddr));
  tpConfirmableInit(&socket);
  KEEP_THREAD_ALIVE();
  return;
}