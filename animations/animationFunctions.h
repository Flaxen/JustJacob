#include <stdint.h>
#include "customTiles.h"

/*
Contains tiles and functions for tile based animations.
All contents in this file are written by Alexander Carlsson
*/

/*
drawTile
Written by Alexander Carlsson
DESC:
  Draws the tile provided. The top left corner of the tileframe is considered the
  starting position of the draw. Functionality is achieved by drawing pixels at
  every coordinate where there is a "1" in the tilemap.
PRE:
  Tile binary map is binary.
POST:
  Draws pixels accordingly
*/
void drawTile(int xPos, int yPos, int tileMap[TILE_HEIGHT][TILE_WIDTH]) {

  int i;
  int j;
  for (i = 0; i < TILE_HEIGHT; i++) {
    for (j = 0; j < TILE_WIDTH; j++) {
      if (tileMap[i][j] == 1) {

        // does not allow pixels to be drawn out of bounds
        if((xPos + j) < SCREEN_WIDTH && (xPos + j) >= 0 && (yPos + i) < SCREEN_HEIGHT && (yPos + i) >= 0 ) {

          drawPixel((xPos + j), (yPos + i));
        }
      }
    }
  }
}

/*
killTile
Written by Alexander Carlsson
DESC:
  Removes the tile provided. The top left corner of the tileframe is considered the
  starting position of the remove. Functionality is achieved by killing pixels at
  every coordinate where there is a "1" in the tilemap.
PRE:
  Tile binary map is binary.
POST:
  Draws pixels accordingly
*/
void killTile(int xPos, int yPos, int tileMap[TILE_HEIGHT][TILE_WIDTH]) {
  int i;
  int j;
  for (i = 0; i < TILE_HEIGHT; i++) {
    for (j = 0; j < TILE_WIDTH; j++) {
      if (tileMap[i][j] == 1) {

        // does not allow pixels to be drawn out of bounds
        if((xPos + j) < SCREEN_WIDTH && (xPos + j) >= 0 && (yPos + i) < SCREEN_HEIGHT && (yPos + i) >= 0 ) {

          // kills pixels in a 3 wide column to allow intro dog to eat the logo
          killPixel((xPos + j), (yPos + i));
          killPixel((xPos + j+1), (yPos + i));
          killPixel((xPos + j+2), (yPos + i));

        }
      }
    }
  }
}


/*
animateDog
Written by Alexander Carlsson
DESC:
  The animation cycle of the running dog. draws and removes the various frames
  in order to represent a running motion.
PRE:
  The motion is moving forward so the provided coordinates have to be every fourth
  coordinate to match up with the motion.
POST:
  Draws and animates the dog on screen.
*/
void animateDog(int xPos, int yPos, int speed) {

  drawTile(xPos, yPos, dogIdleTile);
  display_image(0, MAP_CHOICE);
  delay(speed);
  killTile(xPos, yPos, dogIdleTile);
  display_image(0, MAP_CHOICE);

  drawTile(xPos-1, yPos, dogSmallJumpTile);
  display_image(0, MAP_CHOICE);
  delay(speed);
  killTile(xPos-1, yPos, dogSmallJumpTile);
  display_image(0, MAP_CHOICE);

  drawTile(xPos-2, yPos, dogBigJumpTile);
  display_image(0, MAP_CHOICE);
  delay(speed);
  killTile(xPos-2, yPos, dogBigJumpTile);
  display_image(0, MAP_CHOICE);

  drawTile(xPos-3, yPos, dogSmallJumpTile);
  display_image(0, MAP_CHOICE);
  delay(speed);
  killTile(xPos-3, yPos, dogSmallJumpTile);
  display_image(0, MAP_CHOICE);
}
