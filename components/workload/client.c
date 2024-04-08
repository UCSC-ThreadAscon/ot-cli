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
#define PERIODIC_URI "periodic"

void handleResponse(void *aContext,
                    otMessage *aMessage,
                    const otMessageInfo *aMessageInfo,
                    otError aResult)
{
  otLogNotePlat("Recevied a response. Error: %s", otThreadErrorToString(aResult));
  return;
}

void sendPeriodicRequest() {
  otMessage *aRequest = otCoapNewMessage(OT_INSTANCE, NULL);
  if (aRequest == NULL) {
    otLogCritPlat("Failed to create CoAP request.");
    return;
  }

  otCoapMessageInit(aRequest, OT_COAP_TYPE_CONFIRMABLE, OT_COAP_CODE_POST);
  otCoapMessageGenerateToken(aRequest, OT_COAP_DEFAULT_TOKEN_LENGTH);

  otError error = otCoapMessageAppendUriPathOptions(aRequest, PERIODIC_URI);
    handleError(error, "append uri path options");

  error = otCoapSecureSendRequest(OT_INSTANCE, aRequest, handleResponse, NULL);
  handleError(error, "send request");
  return;
}

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