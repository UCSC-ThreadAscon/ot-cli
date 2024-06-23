#include "server.h"

void delayRequestHandler(void* aContext,
                         otMessage *aMessage,
                         const otMessageInfo *aMessageInfo)
{
  defaultRequestHandler(aContext, aMessage, aMessageInfo); 
  return;
}