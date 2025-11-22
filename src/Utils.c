#include "Utils.h"


#include <stdio.h>
#include <stdlib.h>

void * safe_malloc(size_t size)
{
  void * p = malloc(size);
  if (p == NULL) {
    fprintf(stderr, "Fatal: failed to allocate %zu bytes.\n", size);
    abort();
  } else {
    return p;
  }
}
