#include "server.h"

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
      PrintDelayResults(index, DelaysUs[index]);
    }
    else {
      otLogCritPlat("Current delay test failed due to Time Sync Error.");
    }

    defaultRequestHandler(aContext, aMessage, aMessageInfo);
    index += 1;

    PrintDelimiter();

    if (index == DELAY_MAX_PACKETS) {
      /**
       * TODO:
       *  Print out the average delay. You can average it the traditional way, by summing
       *  everything first, but if you do that, you need to have a way to watch for overflow.
       *  Another approach is to use an iterative average.
       */
      uint64_t averageDelayUs = average(DelaysUs, DELAY_MAX_PACKETS);
      PrintAverageDelay(averageDelayUs);
    }
  }

  return;
}