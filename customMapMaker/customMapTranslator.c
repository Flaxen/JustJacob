#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define FILENAME "customMap.txt"

/*
customMapTranslator.c
Written by Alexander Carlsson

DESC:
  Takes a string argument of binary values and prints them as array contents for
  the I/O shield display to use.
PRE:
  String in the file is 128*32 characters long containing only ones('1') and
  zeroes('0')
POST:
  Prints copy-ready array contents of imported map
*/
int main(int argc, char *args[]) {

  uint8_t tempArr[128*4];
  int len = 128*8*4;
  short *stringIn = malloc(len * sizeof(short));              // Allocates string to heap due to big input data

  char file_name[] = FILENAME;
  FILE *filePointer;

  filePointer = fopen(file_name, "r");                        // Opens file to read from in Read Mode


  char c;
  for(int i = 0; i < len; i++) {
    c = (fgetc(filePointer));
    while(c != '1' && c != '0') {                             // Skips '\n' characters when loading content into stringIn
      c = (fgetc(filePointer));
    }
    stringIn[i] = (c-'0');                                    // Gets the actual integer value instead of the ASCII one
  }
  fclose(filePointer);                                        // Closes file as we're done reading from it

  for (int i = 0; i < 128*4; i++) {
    *(tempArr+i) = 0;                                         // Fills tempArr with zeroes required for future adding
  }

  // makes string into compact
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
