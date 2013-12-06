#include "clar.h"
#include "common.h"
#include "gopro/camera.h"

static gopro_camera *camera;

void test_camera__initialize(void) {
  // camera = gopro_camera_create();
}

void test_camera__cleanup(void) {
  if (camera != NULL) gopro_camera_free(camera);
}

void test_camera__create(void) {
  //
}
