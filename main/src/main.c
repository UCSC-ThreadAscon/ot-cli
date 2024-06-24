#include "main.h"
#include "tight_loop.h"

void app_main(void)
{
  startMain();
  checkConnection(OT_INSTANCE);

#if !DELAY_SERVER
  coapStart();
#endif

#if THROUGHPUT_CONFIRMABLE
  tpConfirmableMain();
#elif THROUGHPUT_NONCONFIRMABLE
  tpNonConfirmableMain();
#elif PACKET_LOSS_CONFIRMABLE
  plConfirmableMain();
#elif PACKET_LOSS_NONCONFIRMABLE
  plNonConfirmableMain();
#elif DELAY_CLIENT
  delayConfirmableSend();
#endif

  return;
}
