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

void sendCoapResponse(otMessage *aRequest, const otMessageInfo *aRequestInfo)
{
  otMessage *aResponse = otCoapNewMessage(OT_INSTANCE, NULL);
  if (aResponse == NULL) {
    otLogCritPlat("Failed to initialize a new message for CoAP response.");
  }

  otError error = otCoapMessageInitResponse(aResponse, aRequest,
                                            OT_COAP_TYPE_ACKNOWLEDGMENT,
                                            OT_COAP_CODE_VALID);
  HandleMessageError(aResponse, error);

  error = otCoapMessageSetPayloadMarker(aResponse);
  HandleMessageError(aResponse, error);

  char* response = "hello";
  error = otMessageAppend(aResponse, response, 20);
  HandleMessageError(aResponse, error);

  error = otCoapSendResponse(OT_INSTANCE, aResponse, aRequestInfo);
  HandleMessageError(aResponse, error);

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

  sendCoapResponse(aMessage, aMessageInfo);
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