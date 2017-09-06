/* Hasan Y Ahmed (hasahmed) && Mitch Thomas (mitthoma)
 * C335
 * Lab2
 */

#include <stdio.h>
#include <ctype.h>
//
// dump.c
//

void dump_memory(void *p, int len) {
  int i;
printf("address\t\tchar\thex\tshort\tinteger\t\tfloat\t\tdoubleFloat\n");
  for (i = 0; i < len; i++) {
    printf("%-16p %-6c 0x%02hhx %+8d %+12d %+17.6e %+16.6e\n",
            (int*)(p + i), //address
            ((int)(*(char*)(p + i)) > 33 && ((int)(*(char*)(p + i) < 126))) ? *(unsigned char*)(p + i) : '?', //char
            *(char*)(p + i), //hex char
            *(short*)(p + i), //short
            *(int*)(p + i), //int
            *(float*)(p + i), //float
            *(double*)(p + i) //double
            ); 
  }
}
