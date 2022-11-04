#include <inttypes.h>
#include <string.h>

int siphash(const void *in, const size_t inlen, const void *k, uint8_t *out);