#include "workload.h"

#include <stdio.h>
#include <string.h>
#include "stdint.h"
#include "inttypes.h"

static inline uint16_t getPayloadLength(const otMessage *aMessage) {
  return otMessageGetLength(aMessage) - otMessageGetOffset(aMessage);
}

void periodicRequestHandler(void *aContext, otMessage *aMessage, const otMessageInfo *aMessageInfo) {
  uint32_t length = getPayloadLength(aMessage);

  otIp6Address sender = aMessageInfo->mSockAddr;
  char senderAddressString[OT_IP6_ADDRESS_STRING_SIZE];
  otIp6AddressToString(&sender, senderAddressString, OT_IP6_ADDRESS_STRING_SIZE);

  char output[PRINT_STATEMENT_SIZE];
  sprintf(output, "Received %" PRIu32 " bytes from %s", length, (char *) &senderAddressString);
  otLogNotePlat(output);
  return;
}

otError periodicResource(otCoapResource *periodic) {
  periodic->mNext = NULL;
  periodic->mContext = NULL;

  periodic->mUriPath = "periodic";

  // TO-DO: Create Handler
  periodic->mHandler = periodicRequestHandler;
  return OT_ERROR_NONE;
}

otError aPeriodicResource() {
  return OT_ERROR_NONE;
}