#ifndef INCLUDE_GOPRO_CAMERA_H
#define INCLUDE_GOPRO_CAMERA_H

typedef struct gopro_camera {
  char *ipaddr;
  char *password;
  void *client;
} gopro_camera;

typedef struct gopro_status {
  int  photo_count;
  int  video_count;
} gopro_status;

extern gopro_camera *gopro_camera_create(char *ipaddr, char *password);
extern gopro_camera *gopro_camera_create_default(char *password);
extern void gopro_camera_free(gopro_camera *cam);

extern int gopro_camera_get_status(gopro_camera *cam, gopro_status *status);

extern int gopro_camera_start_capture(gopro_camera *cam);
extern int gopro_camera_stop_capture(gopro_camera *cam);

extern int gopro_camera_set_video_mode(gopro_camera *cam);
extern int gopro_camera_set_photo_mode(gopro_camera *cam);
extern int gopro_camera_set_burst_mode(gopro_camera *cam);
extern int gopro_camera_set_timelapse_mode(gopro_camera *cam);

extern int gopro_camera_set_head_up(gopro_camera *cam);
extern int gopro_camera_set_head_down(gopro_camera *cam);

extern int gopro_camera_delete_last(gopro_camera *cam);
extern int gopro_camera_delete_all(gopro_camera *cam);

#endif
