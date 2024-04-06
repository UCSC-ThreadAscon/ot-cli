#include "workload.h"

#include <openthread/thread.h>
#include <openthread/platform/radio.h>

#include <assert.h>

#define UnhandledError()                                        \
    otLogCritPlat("Cannot Handle Error: %" PRIu8 ",", error)    \

void checkConnection(otInstance *aInstance) {
  otDeviceRole currentRole;
  do {
    currentRole = otThreadGetDeviceRole(aInstance);
    vTaskDelay(CONNECTION_WAIT_TIME_MS);
  }
  while(OT_DISCONNECTED(currentRole));

  otLogNotePlat("OpenThread Connection has been established.");
  return;
}

/**
 * Initializes the x509 certification and private key. The code for this function
 * comes from the OpenThread source code.
 * https://github.com/openthread/openthread/blob/main/src/cli/cli_coap_secure.cpp#L717
*/
void x509Init()
{
  otInstance *aInstance = esp_openthread_get_instance();
  
    otCoapSecureSetCertificate(aInstance, (const uint8_t *) OT_CLI_COAPS_X509_CERT,
                               sizeof(OT_CLI_COAPS_X509_CERT), (const uint8_t *) OT_CLI_COAPS_PRIV_KEY,
                               sizeof(OT_CLI_COAPS_PRIV_KEY));

    otCoapSecureSetCaCertificateChain(aInstance, (const uint8_t *) OT_CLI_COAPS_TRUSTED_ROOT_CERTIFICATE,
                                      sizeof(OT_CLI_COAPS_TRUSTED_ROOT_CERTIFICATE));
  return;
}