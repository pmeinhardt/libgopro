#ifndef INCLUDE_GOPRO_CLIENT_H
#define INCLUDE_GOPRO_CLIENT_H

#include <curl/curl.h>

struct gopro_client {
  CURL *curl;
};

typedef struct gopro_client gopro_client;

gopro_client *gopro_client_create();
void gopro_client_free(gopro_client *client);

int gopro_client_get(gopro_client *client, char *url);

#endif
