#include "tight_loop.h"

static otSockAddr socket;

void plConfirmableSend(otSockAddr *socket)
{
  static uint32_t sequenceNum = 0;
  request(socket, (void *) &sequenceNum, TIGHT_LOOP_PAYLOAD_BYTES,
          PACKET_LOSS_CONFIRMABLE_URI, plConfirmableResponseCallback,
          OT_COAP_TYPE_CONFIRMABLE);
  sequenceNum += 1;
  return;
}

void plNonConfirmableSend(otSockAddr *socket) 
{
  static uint32_t sequenceNum = 0;
  request(socket, (void *) &sequenceNum, TIGHT_LOOP_PAYLOAD_BYTES,
          PACKET_LOSS_NONCONFIRMABLE_URI, NULL,
          OT_COAP_TYPE_NON_CONFIRMABLE);
  sequenceNum += 1;
  return;
}

void plConfirmableResponseCallback(void *aContext,
                                   otMessage *aMessage,
                                   const otMessageInfo *aMessageInfo,
                                   otError aResult)
{
  defaultResponseCallback(aContext, aMessage, aMessageInfo, aResult);
  plConfirmableSend(&socket);   // send another request after getting a response.
}

void plConfirmableMain()
{
  InitSocket(&socket, SERVER_IP);
  plConfirmableSend(&socket);
  KEEP_THREAD_ALIVE();
  return;
}

void plNonConfirmableMain()
{
  InitSocket(&socket, SERVER_IP);
  while (true) {
    plNonConfirmableSend(&socket);
  }
  KEEP_THREAD_ALIVE();
  return;
}