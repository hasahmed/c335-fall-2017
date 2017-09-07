/* Hasan Y Ahmed (hasahmed) && Mitch Thomas (mitthoma)
 * C335
 * Lab2
 * dump.c
 */

#include <stdio.h>
#include <ctype.h>

void dump_memory(void *p, int len) {
  int i;
printf("address\t\tchar\thex\tshort\tinteger\t\tfloat\t\tdoubleFloat\n");
  for (i = 0; i < len; i++) {
      printf("%-16p ", ((int*)p) + i); //address;
      printf("%-6c ", ((int)(*(char*)(p + i)) > 33 && ((int)(*(char*)(p + i) < 126))) ? *(unsigned char*)(p + i) : '?'); //char;
      printf("0x%02hhx ", *(((char*)p) + i)); //hex char);
      if(i % sizeof(short) == 0)
        printf("%+9d ", *(((short*)p) + i)); //short
      else
          printf("%*c", 8, ' ');
      if(i % sizeof(int) == 0)
            printf("%+12d", *(((int*)p) + i)); //int
      else
          printf("%*c", 12, ' ');
      if(i % sizeof(float) == 0)
        printf("%+17.6e ", *(((float*)p) + i)); //float);
      else
          printf("%*c", 17, ' ');
      if(i % sizeof(double) == 0)
        printf("%16.6e ", *(((double*)p) + i)); //double);
      puts("");
  }
}
