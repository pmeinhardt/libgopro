#include <cstdlib>
#include <iostream>
#include <string>

#include "gopro.h"

class GoProCamera {

public:
  GoProCamera(std::string ipaddr, std::string password) {
    init(ipaddr, password);
  }

  GoProCamera(std::string password) {
    init(std::string(GOPRO_DEFAULT_IPADDR), password);
  }

  ~GoProCamera() {
    gopro_camera_free(camera);
  }

  int startCapture() {
    return gopro_camera_start_capture(camera);
  }

  int stopCapture() {
    return gopro_camera_stop_capture(camera);
  }

  int syncStatus() {
    return gopro_camera_get_status(camera, &status);
  }

  gopro_status *currentStatus() {
    return &status;
  }

protected:
  gopro_camera *camera;
  gopro_status status;

  void init(std::string ipaddr, std::string password) {
    char *ip = (char *)ipaddr.c_str();
    char *pw = (char *)password.c_str();
    camera = gopro_camera_create(ip, pw);
  }

};

// build the library with `make`, then from the project root run:
// g++ -Iinclude -lcurl examples/gopro.cpp build/libgopro.a -o ./gopro

int main(int argc, char *argv[]) {
  std::string password = "password";
  int res;

  GoProCamera cam(password);
  gopro_status *status;

  res = cam.syncStatus();

  if (res == 0) {
    status = cam.currentStatus();
    std::cout << "Video count: " << status->video_count << std::endl;
    std::cout << "Photo count: " << status->photo_count << std::endl;
  }

  // res = cam.startCapture();

  // if (res == 0) {
  //   sleep(4);
  //   res = cam.stopCapture();
  // }

  // res = cam.setVideoMode();
  // res = cam.setPhotoMode();
  // res = cam.setBurstMode();
  // res = cam.setTimelapseMode();

  // res = cam.deleteAll();
  // res = cam.deleteLast();

  return res;
}
