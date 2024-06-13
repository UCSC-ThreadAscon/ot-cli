#include "throughput.h"

void tpPayload(uint8_t *buffer) {
  uint32_t random = esp_random();
  memcpy(buffer, &random, TP_PAYLOAD_BYTES);
  return;
}

void tpConfirmable(otSockAddr *socket)
{
  *socket = createSocket(CONFIG_SERVER_IP_ADDRESS);
  uint32_t payload = 0;
  tpPayload((uint8_t *) &payload);
  request(socket, (void *) &payload, TP_PAYLOAD_BYTES, THROUGHPUT_URI);
  return;
}

void tpMain() {
  otSockAddr socket;
  EmptyMemory(&socket, sizeof(otSockAddr));

  tpConfirmable(&socket);
  KEEP_THREAD_ALIVE();
  return;
}