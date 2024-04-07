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
    otLogNotePlat("DTLS conection established.");
  }
  else {
    otLogNotePlat("DTLS connection has been disconnected.");
  }
  return;
}

void clientConnect(const otSockAddr *socket) {
  char addressString[OT_IP6_ADDRESS_STRING_SIZE];
  EmptyMemory(addressString, OT_IP6_ADDRESS_STRING_SIZE);

  otIp6AddressToString(&(socket->mAddress), addressString,
                       OT_IP6_ADDRESS_STRING_SIZE);
  otLogNotePlat("Attempting DTLS connection with %s.", addressString);

  otCoapSecureConnect(OT_INSTANCE, socket, handleConnected, NULL);
  return;
}

void clientDisconect() {
  otCoapSecureDisconnect(OT_INSTANCE);
  return;
}