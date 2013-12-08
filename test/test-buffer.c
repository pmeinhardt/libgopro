#include "test-helper.h"

#include "buffer.h"

static vbuffer *buf;

void setup() {
  buf = vbuffer_create(8);
}

void cleanup() {
  vbuffer_free(buf);
}

int main() {
  plan(16);

  setup();

  ok(buf->capacity == 8, "create buffer with capacity");
  ok(buf->length == 0, "create buffer with length 0");
  ok(buf->data != NULL, "create buffer with memory pool");

  void *backup = buf->data;
  void *data = (void *)"abcdef";

  vbuffer_append(buf, data, 6);

  ok(buf->capacity == 8, "don't resize buffer on append if data fits");
  ok(buf->length == 6, "update buffer length on append");
  ok(memcmp(buf->data, data, 6) == 0, "append data correctly");
  ok(buf->data == backup, "don't re-allocate memory pool on append (fits)");

  vbuffer_append(buf, data, 6);

  ok(buf->capacity == 12, "update buffer capacity on append (grow)");
  ok(buf->length == 12, "update buffer length on append (grow)");
  ok(memcmp(buf->data, data, 6) == 0, "copy previous data on append (grow)");
  ok(memcmp((char *)buf->data + 6, data, 6) == 0, "correct new data appended");
  ok(buf->data != backup, "re-allocate memory pool on append (grow)");

  backup = buf->data;
  vbuffer_resize(buf, 4);

  ok(buf->capacity == 4, "update buffer capacity on resize (shrink)");
  ok(buf->length == 4, "update buffer length on resize (shrink)");
  ok(memcmp(buf->data, data, 4) == 0, "keep data on resize (shrink)");
  ok(buf->data != backup, "re-allocate memory pool on resize (shrink)");

  cleanup();

  return exit_status();
}
