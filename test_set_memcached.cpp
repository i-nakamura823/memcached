#include <stdio.h>
#include <libmemcached/memcached.h>

#define EXPIRE_TIME 600

int memc_error(struct memcached_st *memc, memcached_return rc) {
  if (rc != MEMCACHED_SUCCESS) {
      fprintf(stderr, "%s\n", memcached_strerror(memc, rc));
      return -1;
  }
  return 0;
}

int memc_get(struct memcached_st *memc, char *key,
             size_t *value_length, uint32_t *flags, char *value) {
  memcached_return rc;
  char *received;
  received = memcached_get(memc, key, strlen(key),
                           value_length, flags, &rc);
  if (received != NULL) {
      strcpy(value, received);
  }

  return memc_error(memc, rc);
}

int memc_set(struct memcached_st *memc, char *key, char *value) {
  memcached_return rc;
  rc = memcached_set(memc,
                     key, strlen(key),
                     value, strlen(value),
                     (time_t)EXPIRE_TIME, (uint32_t)0);

  if (rc != MEMCACHED_BUFFERED) {
      return memc_error(memc, rc);
  }
  return 0;
}

int main(int argc, char *argv[]) {
  struct memcached_st *memc;
  struct memcached_server_st *servers;
  memcached_return rc;

  memc = memcached_create(NULL);

  servers = memcached_server_list_append(NULL, "localhost", 11211, &rc);
  memc_error(memc, rc);
  rc = memcached_server_push(memc, servers);
  memc_error(memc, rc);

  memcached_server_list_free(servers);
  printf("done!\n");

  char *key = "a";
  char *value = "yulli";

  memc_set(memc, key, value);

  key = "cam1";
  char *get_data;
  get_data = (char *)malloc(1024 * sizeof(char));
  size_t value_length;
  uint32_t flags;
  // char *received = memcached_get(memc, key, strlen(key), value_length, flags, &rc);
  memc_get(memc, key, &value_length, &flags, get_data);
  printf(get_data);
  printf("\n");
}
