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
 * TODO: Client finds a device in the network, establishes a CoAP connection,
 * sends a packet, gets a response, then closes the connection.
*/

void handleConnected(bool isConnected, void* context) {
  if (isConnected) {
    otLogNotePlat("DTLS conection has been created.");
  }
  else {
    otLogNotePlat("DTLS connection has been disconnected.");
  }
  return;
}

void clientConnect(const otSockAddr *socket) {
  char addrString[OT_IP6_ADDRESS_STRING_SIZE];
  otIp6AddressToString(&(socket->mAddress), addrString, OT_IP6_ADDRESS_STRING_SIZE);
  otLogNotePlat("Attempt CoAPS connection with %s.", (char *) addrString);

  otError error = otCoapSecureConnect(OT_INSTANCE, socket, handleConnected, NULL);
  handleError(error);
  return;
}

void clientDisconect() {
  otCoapSecureDisconnect(OT_INSTANCE);
  return;
}