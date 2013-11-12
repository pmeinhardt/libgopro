#include "common.h"
#include "util.h"

#include "client.h"

#include "gopro/camera.h"
#include "gopro/defaults.h"

gopro_camera *gopro_camera_create(char *ipaddr, char *password) {
  gopro_camera *cam = (gopro_camera *)malloc(sizeof(gopro_camera));

  if (cam == NULL) {
    perror("Error allocating camera object");
    return NULL;
  }

  cam->client = gopro_client_create();

  if (cam->client == NULL) {
    fprintf(stderr, "Error allocating camera client\n");
    gopro_camera_free(cam);
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

gopro_camera *gopro_camera_create_default(char *password) {
  return gopro_camera_create(GOPRO_DEFAULT_IPADDR, password);
}

void gopro_camera_free(gopro_camera *cam) {
  assert(cam);

  if (cam->client   != NULL) gopro_client_free(cam->client);
  if (cam->ipaddr   != NULL) free(cam->ipaddr);
  if (cam->password != NULL) free(cam->password);

  free(cam);
}

void gopro_camera_free_url(char *url) {
  free(url);
}

char *gopro_camera_build_url(gopro_camera *cam, char *action) {
  char *host = cam->ipaddr;
  char *pass = cam->password;

  int buflen = strlen(host) + strlen(action) + strlen(pass) + 19;

  char *url = (char *)malloc(buflen);
  url[0] = '\0';

  strcat(url, "http://");
  strcat(url, host);
  strcat(url, "/camera/");
  strcat(url, action);
  strcat(url, "?t=");
  strcat(url, pass);

  return url;
}

char *gopro_camera_build_param_url(gopro_camera *cam, char *action, char par) {
  char *base = gopro_camera_build_url(cam, action);

  int buflen = strlen(base) + 6;

  char *url = (char *)malloc(buflen);
  url[0] = '\0';

  strcat(url, base);
  gopro_camera_free_url(base);

  char pstr[2];
  pstr[0] = par;
  pstr[1] = '\0';

  char *penc = curl_easy_escape(NULL, pstr, 0);

  strcat(url, "&p=");
  strcat(url, penc);
  curl_free(penc);

  return url;
}

int gopro_camera_send(gopro_camera *cam, char *action) {
  assert(action);
  assert(cam);

  char *url = gopro_camera_build_url(cam, action);
  int code = gopro_client_get((gopro_client *)(cam->client), url);
  gopro_camera_free_url(url);

  return code;
}

int gopro_camera_send_param(gopro_camera *cam, char *action, int param) {
  assert(action);
  assert(cam);

  char *url = gopro_camera_build_param_url(cam, action, param);
  int code = gopro_client_get((gopro_client *)(cam->client), url);
  gopro_camera_free_url(url);

  return code;
}

int gopro_camera_start_capture(gopro_camera *cam) {
  return gopro_camera_send_param(cam, "SH", 1);
}

int gopro_camera_stop_capture(gopro_camera *cam) {
  return gopro_camera_send_param(cam, "SH", 0);
}
