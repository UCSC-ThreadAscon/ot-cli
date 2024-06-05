#include "utilities.h"

#define OT_INSTANCE esp_openthread_get_instance()

void setPollPeriod(uint32_t pollPeriod) {
  otLogNotePlat("Poll period is currently at %" PRIu32 ".",
                otLinkGetPollPeriod(OT_INSTANCE));

  otError error = otLinkSetPollPeriod(OT_INSTANCE, pollPeriod);
  if (error == OT_ERROR_INVALID_ARGS) {
    otLogCritPlat("Failed to set poll period with value %" PRIu32 ".", pollPeriod);
    return;
  }

  uint32_t newPollPeriod = otLinkGetPollPeriod(OT_INSTANCE);
  assert(newPollPeriod == pollPeriod);
  otLogNotePlat("Poll period has now been set to %" PRIu32 ".", newPollPeriod);

  return;
}