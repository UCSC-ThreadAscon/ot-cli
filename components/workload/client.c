/**
 * All of the code in this file is based upon the CoAP source code used
 * as a part of the OpenThread codebase.
 *
 * https://github.com/openthread/openthread/blob/main/src/cli/cli_coap_secure.cpp
 * https://github.com/openthread/openthread/blob/main/include/openthread/coap_secure.h
 * https://github.com/openthread/openthread/blob/main/include/openthread/coap.h
 * https://github.com/openthread/openthread/blob/main/src/cli/README_COAPS.md
*/
#include "workload.h"

/**
 * TODO: Search for all other devices in the network, and establish
 * a CoAP connection to them.
*/

void handleConnected(bool isConnected, void* context) {
  if (isConnected) {
    otLogNotePlat("DTLS conection has been created.");
  }
  else {
    otLogNotePlat("DTLS Connection has been stopped.");
  }
  return;
}

void clientConnect(const otSockAddr *socket) {
  otError error = otCoapSecureConnect(OT_INSTANCE, socket, handleConnected, NULL);
  handleError(error);
  return;
}