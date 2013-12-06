#include "clar.h"
#include "common.h"
#include "buffer.h"

#ifdef __APPLE__
# include <malloc/malloc.h>
#elif __linux
# include <malloc.h>
#endif

static vbuffer *buffer;

static void assert_allocated_size(void *ptr, size_t n) {
#ifdef __APPLE__
  cl_assert(malloc_size(ptr) >= n);
#elif __linux
  cl_assert(malloc_usable_size(ptr) >= n);
#endif
}

void test_buffer__initialize(void) {
  buffer = vbuffer_create(8);
  cl_assert_(buffer, "Buffer could not be created");
}

void test_buffer__cleanup(void) {
  if (buffer != NULL) vbuffer_free(buffer);
}

void test_buffer__initial_state(void) {
  cl_assert(buffer->capacity == 8);
  cl_assert(buffer->length == 0);
  cl_assert(buffer->data != NULL);
  assert_allocated_size(buffer->data, 8);
}

void test_buffer__resize_grow_empty(void) {
  int res = vbuffer_resize(buffer, 16);

  cl_assert(res == 0);
  cl_assert(buffer->capacity == 16);
  cl_assert(buffer->length == 0);
  assert_allocated_size(buffer->data, 16);
}

void test_buffer__resize_grow_with_data(void) {
  void *data = "abcdefghijkl";
  size_t len = strlen(data);
  int res = vbuffer_append(buffer, (void *)data, len);

  cl_assert(res == 0);

  res = vbuffer_resize(buffer, len * 2);

  cl_assert(res == 0);
  cl_assert(buffer->capacity == len * 2);
  cl_assert(buffer->length == len * 2);
  assert_allocated_size(buffer->data, len * 2);
  cl_assert(memcmp(buffer->data, data, len) == 0);
}

void test_buffer__resize_shrink(void) {
  int res = vbuffer_resize(buffer, 4);

  cl_assert(res == 0);
  cl_assert(buffer->capacity == 4);
  cl_assert(buffer->length == 0);
  assert_allocated_size(buffer->data, 4);
}

void test_buffer__append(void) {
  void *data = "abcdefghijkl";
  size_t len = strlen(data);
  int res = vbuffer_append(buffer, data, len);

  // buffer should contain "abcdefghijkl\0"

  cl_assert(res == 0);
  cl_assert(buffer->capacity == len);
  cl_assert(buffer->length == len);
  cl_assert(buffer->data != data); // copied data
  cl_assert(memcmp(buffer->data, data, len) == 0);

  void *data2 = "mno";
  size_t len2 = strlen(data);
  res = vbuffer_append(buffer, data2, len2);

  // buffer should contain "abcdefghijkl\0mno\0"

  cl_assert(res == 0);
  cl_assert(buffer->capacity == len + len2);
  cl_assert(buffer->length == len + len2);
  cl_assert(memcmp(buffer->data, data, len) == 0);
  cl_assert(memcmp(((char *)buffer->data) + len, data2, len2) == 0);
}
