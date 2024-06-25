#include "server.h"
#include "time_api.h"

#include <assert.h>

static uint64_t DelaysUs[DELAY_MAX_PACKETS];

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
  static uint32_t index = 0;

  if (index < DELAY_MAX_PACKETS) {
    PrintDelimiter();

    uint64_t sent = getTimeSent(aMessage);
    uint64_t received = 0;
    otNetworkTimeStatus status = otNetworkTimeGet(OT_INSTANCE, &received);

    if (status == OT_NETWORK_TIME_SYNCHRONIZED) {
      DelaysUs[index] = received - sent;
      double delayMs = US_TO_MS((double) DelaysUs[index]);
      double delaySecs = US_TO_SECONDS((double) DelaysUs[index]);
      PrintDelayResults(index, DelaysUs[index], delayMs, delaySecs);
    }
    else {
      otLogCritPlat("Current delay test failed due to Time Sync Error.");
    }

    defaultRequestHandler(aContext, aMessage, aMessageInfo);
    index += 1;

    PrintDelimiter();
  }

  return;
}