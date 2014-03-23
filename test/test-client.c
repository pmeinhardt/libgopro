#include "test-helper.h"

#include "client.h"

static gopro_client *client;

void setup() {
  client = gopro_client_create();
}

void cleanup() {
  gopro_client_free(client);
}

int main() {
  plan(1);

  setup();

  ok(client != NULL);

  // test assertions

  cleanup();

  return exit_status();
}
