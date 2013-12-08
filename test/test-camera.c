#include "test-helper.h"

#include "buffer.h"
#include "client.h"

#include "gopro/camera.h"
#include "gopro/defaults.h"
#include "gopro/errors.h"

static char *ipaddr = "127.0.0.1";
static char *passwd = "passwd";

static gopro_camera *cam;

void setup() {
  cam = gopro_camera_create(ipaddr, passwd);
}

void cleanup() {
  gopro_camera_free(cam);
}

int main() {
  plan(4);

  setup();

  ok(strcmp(cam->ipaddr, "127.0.0.1") == 0, "create camera with ip address");
  ok(strcmp(cam->password, "passwd") == 0, "create camera with password");

  ok(cam->ipaddr != ipaddr, "create camera copies ip address");
  ok(cam->password != passwd, "create camera copies password");

  cleanup();

  return exit_status();
}
