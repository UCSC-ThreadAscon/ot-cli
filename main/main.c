#include "main.h"
#include "tight_loop.h"

void app_main(void)
{
  startMain();
  checkConnection(OT_INSTANCE);
  coapStart();

#if CONFIRMABLE
  tpConfirmableMain();
#elif NONCONFIRMABLE
  tpNonConfirmableMain();
#endif

  return;
}
