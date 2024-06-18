#include "tight_loop.h"

static otSockAddr socket;

void plConfirmableSend(otSockAddr *socket)
{
  static uint32_t sequenceNum = 0;
  otLogNotePlat("Sending packet with sequence number %" PRIu32 ".\n", sequenceNum);

  request(socket, (void *) &sequenceNum, TIGHT_LOOP_PAYLOAD_BYTES,
          PACKET_LOSS_CONFIRMABLE_URI, plConfirmableResponseCallback,
          OT_COAP_TYPE_CONFIRMABLE);
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
  InitSocket(&socket);
  plConfirmableSend(&socket);
  KEEP_THREAD_ALIVE();
  return;
}