/**
 * This file contains the worker thread that will do periodic sending
 * of CoAP requests.
*/
#include "workload.h"

void periodicWorker(void* context) {
  otSockAddr *socket = (otSockAddr *) context;

  while (true) {
    if (otCoapSecureIsConnected(OT_INSTANCE)) {
      sendRequest(Periodic, &(socket->mAddress));

        otLogNotePlat(
          "Will wait %d ms before sending next the periodic CoAP request.",
          PERIODIC_WAIT_TIME_MS
        );

        otCoapSecureDisconnect(OT_INSTANCE);

        TickType_t lastWakeupTime = xTaskGetTickCount();
        vTaskDelayUntil(&lastWakeupTime, MS_TO_TICKS(PERIODIC_WAIT_TIME_MS));
    } else {
      clientConnect(socket);
      vTaskDelay(MAIN_WAIT_TIME);
    }
  }
  return;
}