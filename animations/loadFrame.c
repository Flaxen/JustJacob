#include <stdio.h>
#include <stdint.h>

#include "../settings.h"

/*
main
DESC:
  Loads bit array from .txt file into frameArr, removing any characters that are
  not '0' or '1', effectively removing "new line" characters and the like.
  This function should be commented out or renamed during runtime of the full
  program and has to be used separetly using the command line for proper use.
PRE:
  FILENAME variable is changed to the corresponding file you wish to load.
POST:
  Prints the array frameArr. This has to be copied and pasted as the process as
  of now is semi manual. Se README for more instructions.
*/
void main() {
  char FILENAME[] = "tileBinary.txt";

  char frameArr[TILE_HEIGHT][TILE_WIDTH];
  char ch;
  FILE *fp;

  fp = fopen(FILENAME, "r");

  char c;
  for(int i = 0; i < TILE_HEIGHT; i++) {
    for (int j = 0; j < TILE_WIDTH; j++) {
      c = fgetc(fp);
      if(c != '0' && c != '1') {
        c = fgetc(fp);
      }

      frameArr[i][j] = (c-'0');
    }
    fgetc(fp);
  }
  fclose(fp);

  // prints formated data. copy paste into array for use.
  printf("{");
  for (int i = 0; i < TILE_HEIGHT; i++) {
    for (int j = 0; j < TILE_WIDTH; j++) {
      printf("%d, ", frameArr[i][j]);
    }
    printf("},\n{");
  }





}
