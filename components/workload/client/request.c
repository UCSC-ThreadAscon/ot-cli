/**
 * All of the code in this file is based upon the both CoAP and CoAP secure
 * source code used as a part of the OpenThread codebase. The CoAP and
 * CoAP secure source files can be found at:
 * https://github.com/UCSC-ThreadAscon/openthread/tree/main/src/cli
*/
#include "workload.h"

otMessage* createCoapMessage()
{
  otMessage *newMessage = otCoapNewMessage(OT_INSTANCE, NULL);
  if (newMessage == NULL) {
    otLogCritPlat("Failed to create CoAP request.");
    return NULL;
  }
  return newMessage;
}

void createMessageInfo(otSockAddr *aSocket, otMessageInfo *aMessageInfo)
{
  aMessageInfo->mHopLimit = 0;  // default

  aMessageInfo->mPeerAddr = aSocket->mAddress;
  aMessageInfo->mPeerPort = aSocket->mPort;

  aMessageInfo->mSockAddr = *otThreadGetMeshLocalEid(OT_INSTANCE);
  aMessageInfo->mSockPort = COAP_SOCK_PORT;
  return;
}

void createHeaders(otMessage *aRequest,
                   otMessageInfo *aMessageInfo,
                   const char *uri)
{
  otError error = OT_ERROR_NONE;

  otCoapMessageInit(aRequest, OT_COAP_TYPE_CONFIRMABLE, OT_COAP_CODE_POST);
  otCoapMessageGenerateToken(aRequest, OT_COAP_DEFAULT_TOKEN_LENGTH);

  error = otCoapMessageAppendUriPathOptions(aRequest, uri);
  HandleMessageError("append uri options", aRequest, error);

  return;
}

void addPayload(otMessage *aRequest,
                void *payload,
                size_t payloadSize)
{
  otError error = OT_ERROR_NONE;

  error = otCoapMessageSetPayloadMarker(aRequest);
  HandleMessageError("set payload marker", aRequest, error);

  error = otMessageAppend(aRequest, payload, payloadSize);
  HandleMessageError("message append", aRequest, error);

  return;
}

void send(otMessage *aRequest, otMessageInfo *aMessageInfo)
{
  otError error = otCoapSendRequest(OT_INSTANCE, aRequest, aMessageInfo,
                                    defaultResponseCallback, NULL);
  HandleMessageError("send request", aRequest, error);
  return;
}

void printMessageSent(otSockAddr *socket, size_t payloadSize)
{
  char destString[OT_IP6_ADDRESS_STRING_SIZE];

  otIp6AddressToString(&(socket->mAddress),
                       destString,
                       OT_IP6_ADDRESS_STRING_SIZE);

  otLogNotePlat("Sent a message of %d bytes to %s.", 
                payloadSize, destString);
  return;
}

void request(otSockAddr *socket,
             void *payload,
             size_t payloadSize,
             const char *uri)
{
  otMessageInfo aMessageInfo;
  otMessage *aRequest;

  EmptyMemory(&aMessageInfo, sizeof(otMessageInfo));
  createMessageInfo(socket, &aMessageInfo);

  aRequest = createCoapMessage();

  createHeaders(aRequest, &aMessageInfo, uri);
  addPayload(aRequest, payload, payloadSize);
  send(aRequest, &aMessageInfo);

#if COAP_DEBUG
  printMessageSent(socket, payloadSize);
#endif
  return;
}