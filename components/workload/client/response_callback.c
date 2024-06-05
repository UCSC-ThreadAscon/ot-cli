/**
 * All of the code in this file is based upon the both CoAP and CoAP secure
 * source code used as a part of the OpenThread codebase. The CoAP and
 * CoAP secure source files can be found at:
 * https://github.com/UCSC-ThreadAscon/openthread/tree/main/src/cli
*/
#include "workload.h"
#include "sleep.h"

void responseCallback(void *aContext,
                     otMessage *aMessage,
                     const otMessageInfo *aMessageInfo,
                     otError aResult)
{
  if (aResult != OT_ERROR_NONE)
  {
    otLogWarnPlat("Response error: %s", otThreadErrorToString(aResult));
  }
  else 
  {
    uint16_t payloadLen = getPayloadLength(aMessage);
    char payload[payloadLen];
    EmptyMemory(payload, payloadLen);
    getPayload(aMessage, payload);

    char senderAddr[OT_IP6_ADDRESS_STRING_SIZE];
    otIp6AddressToString(&(aMessageInfo->mPeerAddr), senderAddr,
                         OT_IP6_ADDRESS_STRING_SIZE);

#if COAP_DEBUG
    otLogNotePlat("Response from %s of size %" PRIu16 " bytes.",
                  senderAddr, payloadLen);
#endif
  }
  return;
}