#include "main.h"
#include "throughput.c"

void app_main(void)
{
  startMain();
  checkConnection(OT_INSTANCE);
  coapStart();

#if THROUGHPUT_CONFIRMABLE
  tpMainConfirmable();
#elif THROUGHPUT_NONCONFIRMABLE
  tpMainNonConfirmable();
#endif

  return;
}
