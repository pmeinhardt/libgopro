#include "common.h"
#include "gopro/camera.h"

camera *gopro_camera_create(char *ipaddr, char *password) {
  camera *cam = (camera *)malloc(sizeof(camera));

  if (cam == NULL) {
    perror("Error allocating camera object");
    return NULL;
  }

  cam->ipaddr = (char *)malloc(strlen(ipaddr) + 1);

  if (cam->ipaddr == NULL) {
    perror("Error allocating camera address");
    gopro_camera_free(cam);
    return NULL;
  }

  strcpy(cam->ipaddr, ipaddr);

  cam->password = (char *)malloc(strlen(ipaddr) + 1);

  if (cam->password == NULL) {
    perror("Error allocating camera password");
    gopro_camera_free(cam);
    return NULL;
  }

  strcpy(cam->password, password);

  return cam;
}

void gopro_camera_free(camera *cam) {
  assert(cam);

  if (cam->ipaddr   != NULL) free(cam->ipaddr);
  if (cam->password != NULL) free(cam->password);

  free(cam);
}
