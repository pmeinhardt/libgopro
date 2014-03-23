#include "test-helper.h"

#include "buffer.h"

#include "gopro/camera.h"
#include "gopro/defaults.h"
#include "gopro/status.h"

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
  plan(6);

  setup();

  ok(cam != NULL);

  is(cam->ipaddr, "127.0.0.1", "create camera with ip address");
  is(cam->password, "passwd", "create camera with password");
  ok(cam->client != NULL, "create camera with client");

  ok(cam->ipaddr != ipaddr, "create camera copies ip address");
  ok(cam->password != passwd, "create camera copies password");

  cleanup();

  return exit_status();
}
