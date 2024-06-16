#include "main.h"
#include "tight_loop.h"

void app_main(void)
{
  startMain();
  checkConnection(OT_INSTANCE);
  coapStart();

#if THROUGHPUT_CONFIRMABLE
  tpConfirmableMain();
#elif THROUGHPUT_NONCONFIRMABLE
  tpNonConfirmableMain();
#elif PACKET_LOSS_CONFIRMABLE
  plConfirmableMain();
#endif

  return;
}
