#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "../settings.h"

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

/*
following variables specify the amount of rows to be compacted into one row.
For instance the I/O shield makes 4 ROWS out of the provided 32 by merging COLLUMNS of size 8
*/
int ROWS_WHEN_DONE = 4;
int COLLUMN_TO_MERGE_SIZE = 8;


int main(int argc, char *args[]) {

  uint8_t tempArr[SCREEN_WIDTH*ROWS_WHEN_DONE];
  int len = SCREEN_WIDTH*COLLUMN_TO_MERGE_SIZE*ROWS_WHEN_DONE;
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

  for (int i = 0; i < SCREEN_WIDTH*ROWS_WHEN_DONE; i++) {
    *(tempArr+i) = 0;                                         // Fills tempArr with zeroes required for future adding
  }

  // makes string into compact string for display
  for (int k = 0; k < ROWS_WHEN_DONE; k++) {
    for (int i = 0; i < SCREEN_WIDTH; i++) {
      for (int j = 0; j < COLLUMN_TO_MERGE_SIZE; j++) {

        tempArr[i+(k*SCREEN_WIDTH)] +=
            ((stringIn[SCREEN_WIDTH*COLLUMN_TO_MERGE_SIZE*k+(i+SCREEN_WIDTH*j)])*(1<<j));

      }
    }
  }
  free(stringIn);

  // prints compacted string as ready input array.
  int printedValues = 0;
  for (int i = 0; i < SCREEN_WIDTH*ROWS_WHEN_DONE; i++) {
    printf("%d, ", tempArr[i]);
    printedValues++;
  }
  printf("\n\nPrinted values(new array size): %d\n", printedValues);

  return 0;
}
