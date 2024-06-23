#include "tight_loop.h"

static otSockAddr *socket;

void delayConfirmableSend(otSockAddr *socket)
{
  return;
}

void delayConfirmableResponseCallback(void *aContext,
                                      otMessage *aMessage,
                                      const otMessageInfo *aMessageInfo,
                                      otError aResult)
{
  defaultResponseCallback(aContext, aMessage, aMessageInfo, aResult);
  delayConfirmableSend(socket);   // send another request after getting response
  return;
}