#include "workload.h"

#include <stdio.h>
#include <string.h>
#include "stdint.h"
#include "inttypes.h"

void getSockAddrString(const otMessageInfo *aMessageInfo, char *ipString) {
  otIp6AddressToString(&(aMessageInfo->mSockAddr), ipString,
                       OT_IP6_ADDRESS_STRING_SIZE);
  return;
}

void printCoapRequest(char *output, uint32_t payloadLen, char *ipString) {
  sprintf(output, "Received %" PRIu32 " bytes from %s.", payloadLen, ipString);
  otLogNotePlat(output);
  return;
}

static inline uint16_t getPayloadLength(const otMessage *aMessage) {
  return otMessageGetLength(aMessage) - otMessageGetOffset(aMessage);
}

void periodicRequestHandler(void *aContext,
                            otMessage *aMessage,
                            const otMessageInfo *aMessageInfo)
{
  uint32_t length = getPayloadLength(aMessage);

  char senderAddress[OT_IP6_ADDRESS_STRING_SIZE];
  getSockAddrString(aMessageInfo, senderAddress);

  char output[PRINT_STATEMENT_SIZE];
  printCoapRequest(output, length, senderAddress);
  return;
}

otError createPeriodicResource(otCoapResource *periodic) {
  periodic->mNext = NULL;
  periodic->mContext = NULL;

  periodic->mUriPath = "periodic";
  periodic->mHandler = periodicRequestHandler;
  return OT_ERROR_NONE;
}

otError createAPeriodicResource() {
  return OT_ERROR_NONE;
}