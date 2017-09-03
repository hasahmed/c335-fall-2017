#include <stdio.h>
//
// dump.c
//

void dump_memory(void *p, int len) {
  int i;
printf("address\tchar\thex\tshort\tinteger\tfloat\tdoubleFloat");
  for (i = 0; i < len; i++) {
    printf("%d: %02x\n", p + i, *(unsigned char *)(p + i));
  }
}
