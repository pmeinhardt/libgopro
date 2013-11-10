#ifndef INCLUDE_GOPRO_CAMERA_H
#define INCLUDE_GOPRO_CAMERA_H

struct camera {
  char *ipaddr;
  char *password;
};

typedef struct camera camera;

extern camera *gopro_camera_create(char *ipaddr, char *password);

extern void gopro_camera_free(camera *cam);

#endif
