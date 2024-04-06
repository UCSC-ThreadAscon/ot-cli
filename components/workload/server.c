#include <stdio.h>
#include "workload.h"

otError periodicResource(otCoapResource *periodic) {
  periodic->mNext = NULL;
  periodic->mContext = NULL;

  periodic->mUriPath = "periodic";

  // TO-DO: Create Handler
  periodic->mHandler = NULL;
  return OT_ERROR_NONE;
}

otError aPeriodicResource() {
  return OT_ERROR_NONE;
}