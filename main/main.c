#include "main.h"
#include "throughput.c"

void app_main(void)
{
  startMain();
  checkConnection(OT_INSTANCE);
  coapStart();

  otSockAddr socket;
  EmptyMemory(&socket, sizeof(otSockAddr));

  tpConfirmable(&socket);
  return;
}
