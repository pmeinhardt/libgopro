#include "common.h"
#include "util.h"

#include "client.h"

gopro_client *gopro_client_create() {
  gopro_client *client = (gopro_client *)malloc(sizeof(gopro_client));

  if (client == NULL) {
    perror("Error allocating client object");
    return NULL;
  }

  client->curl = curl_easy_init();

  if (client->curl == NULL) {
    fprintf(stderr, "Error allocating curl handle\n");
    gopro_client_free(client);
    return NULL;
  }

  return client;
}

void gopro_client_free(gopro_client *client) {
  assert(client);

  if (client->curl != NULL) curl_easy_cleanup(client->curl);

  free(client);
}

int gopro_client_get(gopro_client *client, char *url) {
  CURL *curl = client->curl;
  CURLcode res;

  curl_easy_setopt(curl, CURLOPT_URL, url);

  res = curl_easy_perform(curl);
  curl_easy_reset(curl);

  if (res != CURLE_OK) {
    fprintf(stderr, "Client error: %s\n", curl_easy_strerror(res));
    return 1;
  }

  return 0;
}