/**
 * All of the code in this file is based upon the CoAP source code used
 * as a part of the OpenThread protocol.
 *
 * https://github.com/openthread/openthread/blob/main/src/cli/cli_coap_secure.cpp
 * https://github.com/openthread/openthread/blob/main/include/openthread/coap_secure.h
 * https://github.com/openthread/openthread/blob/main/include/openthread/coap.h
 * https://github.com/openthread/openthread/blob/main/src/cli/README_COAPS.md
*/
#include "workload.h"

#include <stdio.h>
#include <string.h>
#include "stdint.h"
#include "inttypes.h"

void getPeerAddrString(const otMessageInfo *aMessageInfo, char *ipString) {
  otIp6AddressToString(&(aMessageInfo->mPeerAddr), ipString,
                       OT_IP6_ADDRESS_STRING_SIZE);
  return;
}

void printCoapRequest(char *output, uint32_t payloadLen, char *ipString) {
  sprintf(output, "Received %" PRIu32 " bytes from %s.", payloadLen, ipString);
  otLogNotePlat(output);
  return;
}

static inline uint16_t getPayloadLength(const otMessage *aMessage) {
  return otMessageGetLength(aMessage) - otMessageGetOffset(aMessage);
}

static inline void handleCoapResponseError(otError error) {
  switch (error) {
    case OT_ERROR_NONE:
      otLogNotePlat("Sent CoAP Response.");
      break;

    default:
      otLogCritPlat("Error code: %s", otThreadErrorToString(error));
  }
  return;
}

void sendCoapResponse(otInstance *aInstance,
                      otMessage *aRequest,
                      const otMessageInfo *aMessageInfo)
{
  otMessage *aResponse = otCoapNewMessage(aInstance, NULL);
  if (aResponse == NULL) {
    otLogCritPlat("Failed to initialize a new message for CoAP response.");
  }

  otError error = otCoapMessageInitResponse(aResponse, aRequest,
                                            OT_COAP_TYPE_ACKNOWLEDGMENT,
                                            OT_COAP_CODE_VALID);
  handleCoapResponseError(error);

  error = otCoapMessageSetPayloadMarker(aResponse);
  handleCoapResponseError(error);

  error = otCoapSendResponse(aInstance, aResponse, aMessageInfo);
  handleCoapResponseError(error);

  return;
}

void periodicRequestHandler(void *aContext,
                            otMessage *aMessage,
                            const otMessageInfo *aMessageInfo)
{
  uint32_t length = getPayloadLength(aMessage);

  char senderAddress[OT_IP6_ADDRESS_STRING_SIZE];
  char output[PRINT_STATEMENT_SIZE];

  getPeerAddrString(aMessageInfo, senderAddress);
  printCoapRequest(output, length, senderAddress);

  sendCoapResponse(esp_openthread_get_instance(), aMessage, aMessageInfo);
  return;
}

otError createPeriodicResource(otCoapResource *periodic) {
  periodic->mNext = NULL;
  periodic->mContext = NULL;
  periodic->mUriPath = "periodic";
  periodic->mHandler = periodicRequestHandler;
  return OT_ERROR_NONE;
}

otError createAPeriodicResource() {
  return OT_ERROR_NONE;
}