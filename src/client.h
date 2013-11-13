#ifndef INCLUDE_CLIENT_H
#define INCLUDE_CLIENT_H

#include <curl/curl.h>

#include "buffer.h"

typedef struct gopro_client {
  CURL *curl;
} gopro_client;

gopro_client *gopro_client_create();
void gopro_client_free(gopro_client *client);

int gopro_client_get(gopro_client *client, char *url, vbuffer *buffer);

#endif
