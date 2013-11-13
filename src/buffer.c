#include "common.h"

#include "buffer.h"

vbuffer *vbuffer_create(size_t capacity) {
  vbuffer *buffer = (vbuffer *)malloc(sizeof(vbuffer));

  if (buffer == NULL) {
    perror("Error allocating vbuffer");
    return NULL;
  };

  buffer->data = malloc(capacity);

  if (buffer->data == NULL) {
    perror("Error allocating vbuffer memory pool");
    vbuffer_free(buffer);
    return NULL;
  }

  buffer->capacity = capacity;
  buffer->length = 0;

  return buffer;
}

void vbuffer_free(vbuffer *buffer) {
  if (buffer->data != NULL) free(buffer->data);
  free(buffer);
}

int vbuffer_resize(vbuffer *buffer, size_t new_capacity) {
  size_t copylen;
  void *backup;

  if (new_capacity == buffer->capacity) return 0;

  backup = buffer->data;

  buffer->data = malloc(new_capacity);

  if (buffer->data == NULL) {
    perror("Error allocating memory for buffer resize");
    buffer->data = backup;
    return 1;
  }

  buffer->capacity = new_capacity;

  copylen = (new_capacity < (buffer->length)) ? new_capacity : buffer->length;

  if (backup != NULL) {
    memcpy(buffer->data, backup, copylen);
    free(backup);
  }

  return 0;
}

int vbuffer_append(vbuffer *buffer, void *data, size_t n) {
  size_t new_capacity;
  int err;

  if (buffer->capacity < buffer->length + n) {
    new_capacity = buffer->length + n; // grow exactly as needed
    err = vbuffer_resize(buffer, new_capacity);
    if (err != 0) return 1;
  }

  void *end = ((char *)buffer->data) + buffer->length;

  memcpy(end, data, n);
  buffer->length += n;

  return 0;
}
