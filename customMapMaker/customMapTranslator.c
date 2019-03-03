#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define FILENAME "customMap.txt"

int main(int argc, char *args[]) {

  uint8_t tempArr[128*4];
  int len = 128*8*4;
  short *stringIn = malloc(len * sizeof(short));

  char ch;
  char file_name[] = FILENAME;
  FILE *fp;

  fp = fopen(file_name, "r");

  for(int i = 0; i < len; i++) {
    stringIn[i] = (fgetc(fp)-'0');
  }
  fclose(fp);

  for (int i = 0; i < 128*4; i++) {
    *(tempArr+i) = 0;
  }

  // makes string compact
  for (int k = 0; k < 4; k++) {
    for (int i = 0; i < 128; i++) {
      for (int j = 0; j < 8; j++) {

        tempArr[i+(k*128)] += ((stringIn[128*8*k+(i+128*j)])*(1<<j));

      }
    }
  }
  free(stringIn);


  // prints compacted string as ready input array.
  int printedValues = 0;
  for (int i = 0; i < 128*4; i++) {
    printf("%d, ", tempArr[i]);
    printedValues++;
  }
  printf("\n\nPrinted values: %d\n", printedValues);

  return 0;
}
