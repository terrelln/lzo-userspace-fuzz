#undef NDEBUG
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <assert.h>

#include "lzo.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  size_t outSize = size * 10;
  uint8_t* const out = (uint8_t*)malloc(outSize);
  assert(out);
  lzo1x_decompress_safe(data, size, out, &outSize);
  free(out);
  return 0;
}
