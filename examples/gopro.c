#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "gopro.h"

// build the library with `make`, then from the project root run:
// gcc -Iinclude -lcurl examples/gopro.c build/libgopro.a -o ./gopro

int main(int argc, char *argv[]) {
  char *pw = "password";
  int res;

  gopro_status status;
  gopro_camera *cam = gopro_camera_create_default(pw);

  res = gopro_camera_get_status(cam, &status);

  if (res == 0) {
    printf("Video count: %d\n", status.video_count);
    printf("Photo count: %d\n", status.photo_count);
  }

  // res = gopro_camera_start_capture(cam);

  // if (res == 0) {
  //   sleep(4);
  //   res = gopro_camera_stop_capture(cam);
  // }

  // res = gopro_camera_set_video_mode(cam);
  // res = gopro_camera_set_photo_mode(cam);
  // res = gopro_camera_set_burst_mode(cam);
  // res = gopro_camera_set_timelapse_mode(cam);

  // res = gopro_camera_delete_all(cam);
  // res = gopro_camera_delete_last(cam);

  gopro_camera_free(cam);

  return res;
}
