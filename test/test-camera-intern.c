#include "test-helper.h"

#include "buffer.h"

#include "gopro/camera.h"
#include "gopro/defaults.h"
#include "gopro/status.h"

// expose internal camera methods for testing

extern void gopro_camera_free_url(char *url);
extern char *gopro_camera_build_url(gopro_camera *cam, char *action);
extern char *gopro_camera_build_param_url(
  gopro_camera *cam,
  char *action,
  char par
);
extern void gopro_status_parse(gopro_status *status, char *bytes);

//

static char *ipaddr = "127.0.0.1";
static char *passwd = "passwd";

static gopro_camera *cam;
static gopro_status status;

void setup() {
  cam = gopro_camera_create(ipaddr, passwd);
}

void cleanup() {
  gopro_camera_free(cam);
}

int main() {
  plan(5);

  setup();

  ok(cam != NULL);

  // build URL

  char *url = gopro_camera_build_url(cam, "XY");
  is(url, "http://127.0.0.1/camera/XY?t=passwd", "build action URL");
  gopro_camera_free_url(url);

  // build URL with param

  url = gopro_camera_build_param_url(cam, "XY", 4);
  is(
    url,
    "http://127.0.0.1/camera/XY?t=passwd&p=%04",
    "build parameterized action URL"
  );
  gopro_camera_free_url(url);

  // parse camera status response

  char bytes[] = {
    0x00,
    0x00, // current mode
    0x00,
    0x00, // start up mode
    0x00, // spot meter
    0x00, // current timelapse interval
    0x00, // automatic power off
    0x00, // current view angle
    0x00, // current photo mode
    0x00, // current video mode
    0x00,
    0x00,
    0x00,
    0x00, // recording minutes
    0x00, // recording seconds
    0x00,
    0x00, // current beep volume
    0x00, // led setting
    0x00, // bit-map: preview, ?, up/down, one button, OSD, NTSC/PAL, beep, ?
    0x00, // battery %
    0x00,
    0x00, // photos available (hi)
    0x00, // photos available (lo)
    0x02, // photo count (hi)
    0x02, // photo count (lo)
    0x00, // video time, minutes remaining (hi)
    0x00, // video time, minutes remaining (lo)
    0x01, // video count (hi)
    0x01, // video count (lo)
    0x00, // recording
    0x00
  };

  gopro_status_parse(&status, bytes);

  cmp_ok(status.photo_count, "==", 514, "parse photo count");
  cmp_ok(status.video_count, "==", 257, "parse video count");

  cleanup();

  return exit_status();
}
