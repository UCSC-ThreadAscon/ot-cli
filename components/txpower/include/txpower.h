#ifndef OT_TXPOWER_
#define OT_TXPOWER_

#include <openthread/logging.h>

#include "esp_openthread.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "openthread/cli.h"
#include "openthread/instance.h"
#include "openthread/logging.h"

void setTxPower(void);

#endif // OT_TXPOWER_