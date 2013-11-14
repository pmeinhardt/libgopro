#ifndef INCLUDE_CLIENT_H
#define INCLUDE_CLIENT_H

#include <stdlib.h>
#include <curl/curl.h>

typedef struct gopro_client {
  CURL *curl;
} gopro_client;

typedef size_t (*gopro_client_cb)(char *, size_t, size_t, void *);

gopro_client *gopro_client_create();
void gopro_client_free(gopro_client *client);

int gopro_client_get(
  gopro_client *client,
  char *url,
  void *context,
  gopro_client_cb *cb
);

#endif
