#include "tap.h"
#include "buffer.h"

static vbuffer *buf;

void setup() {
  buf = vbuffer_create(8);
}

void cleanup() {
  vbuffer_free(buf);
}

int main() {
  plan(2);

  setup();

  ok(buf->capacity == 8, "buffer initialized with capacity %d", buf->capacity);
  ok(buf->length == 0, "buffer initialized with length %d", buf->length);

  cleanup();

  return exit_status();
}
