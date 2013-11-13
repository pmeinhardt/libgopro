#ifndef INCLUDE_BUFFER_H
#define INCLUDE_BUFFER_H

typedef struct vbuffer {
  void *data;
  size_t capacity;
  size_t length;
} vbuffer;

vbuffer *vbuffer_create(size_t capacity);
void vbuffer_free(vbuffer *buffer);

int vbuffer_resize(vbuffer *buffer, size_t new_capacity);
int vbuffer_append(vbuffer *buffer, void *data, size_t n);

#endif
