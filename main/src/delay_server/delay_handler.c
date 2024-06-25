#include "server.h"
#include "time_api.h"

#include <assert.h>

static uint32_t Delays[DELAY_MAX_PACKETS];

uint64_t getTimeSent(otMessage *aMessage)
{
  uint64_t sent = 0;
  getPayload(aMessage, (void *) &sent);
  return sent;
}

void delayRequestHandler(void* aContext,
                         otMessage *aMessage,
                         const otMessageInfo *aMessageInfo)
{
  PrintDelimiter();

  uint64_t sent = getTimeSent(aMessage);
  uint64_t received = 0;
  otNetworkTimeStatus status = otNetworkTimeGet(OT_INSTANCE, &received);

  if (status == OT_NETWORK_TIME_SYNCHRONIZED) {
    uint64_t delayUs = received - sent;
    double delayMs = US_TO_MS((double) delayUs);
    double delaySecs = US_TO_SECONDS((double) delayUs);
    PrintDelayResults(delayUs, delayMs, delaySecs);
  }
  else {
    otLogCritPlat("Current delay test failed due to Time Sync Error.");
  }

  defaultRequestHandler(aContext, aMessage, aMessageInfo);
  PrintDelimiter();
  return;
}