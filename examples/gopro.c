#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "libgopro.h"

// build the library with `make`, then from the project root run:
// gcc -Iinclude -lcurl examples/gopro.c build/libgopro.a -o ./gopro

int main(int argc, char *argv[]) {
  char *pw = "password";
  int status;

  gopro_camera *cam = gopro_camera_create_default(pw);

  status = gopro_camera_start_capture(cam);

  if (status == 0) {
    sleep(4);
    status = gopro_camera_stop_capture(cam);
  }

  // status = gopro_camera_set_video_mode(cam);
  // status = gopro_camera_set_photo_mode(cam);

  // status = gopro_camera_set_video_mode(cam);
  // status = gopro_camera_set_photo_mode(cam);
  // status = gopro_camera_set_burst_mode(cam);
  // status = gopro_camera_set_timelapse_mode(cam);

  // status = gopro_camera_delete_all(cam);
  // status = gopro_camera_delete_last(cam);

  gopro_camera_free(cam);

  return status;
}
