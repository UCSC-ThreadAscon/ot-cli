#include "main.h"

void networkTimeSyncCallbback(void *aCallbackContext)
{
  otLogNotePlat("The Network Time has now been synchronized.");
  return;
}