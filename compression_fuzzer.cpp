#undef NDEBUG
#include <string.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

#include "lzo.h"

char wrkmem[LZO1X_MEM_COMPRESS];

#define RLE 1

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  size_t outSize = lzo1x_worst_compress(size);
  uint8_t* const out = (uint8_t*)malloc(outSize);
  assert(out);
#if RLE
  assert(LZO_E_OK == lzorle1x_1_compress(data, size, out, &outSize, wrkmem));
#else
  assert(LZO_E_OK == lzo1x_1_compress(data, size, out, &outSize, wrkmem));
#endif
  uint8_t* const rt = (uint8_t*)malloc(size);
  assert(rt);
  size_t rtsize = size;
  int const ret = lzo1x_decompress_safe(out, outSize, rt, &rtsize);
  if (ret != LZO_E_OK) {
    assert(size < 4);
    fprintf(stderr, "INPUT: ");
    for (size_t i = 0; i < size; ++i)
      fprintf(stderr, "%u ", (unsigned)data[i]);
    fprintf(stderr, "\nOUTPUT: ");
    for (size_t i = 0; i < outSize; ++i)
      fprintf(stderr, "%u ", (unsigned)out[i]);
    fprintf(stderr, "\nret = %d\n", ret);
  }
  assert(ret == LZO_E_OK);
  assert(rtsize == size);
  assert(memcmp(data, rt, size) == 0);
  free(out);
  free(rt);
  return 0;
}
