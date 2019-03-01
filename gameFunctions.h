#include <math.h>

#include "LSM6DS3addresses.h"
#include "settings.h"

/*
updateTiltPos
DESC:
  Keeps track of the angle of the board.
  NOTE: yTiltPos gets +1 as the sensor data for that axes for some reason is
  off by 1.
PRE:
  Board has to lay flat on a surface during bootup as it caibrates 0 degrees to
  the position it has at startup.
POST:
  Adds or subtracts the current angle/second value.
*/
int xTiltPos = 0;
int yTiltPos = 0;

void updateTiltPos() {
  xTiltPos += (read(OUTX_L_G));
  yTiltPos += (read(OUTY_L_G)+1);

  if(xTiltPos > (-3) && xTiltPos < 3) {
    xTiltPos == 0;
  }
  if(yTiltPos > (-3) && yTiltPos < 3) {
    yTiltPos == 0;
  }
}

int xMoveDirection() {
  if (xTiltPos > 0) {
    return -1;
  } else if(xTiltPos < 0) {
    return 1;
  } else {
    return 0;
  }
}

int yMoveDirection() {
  if (yTiltPos > 0) {
    return 1;
  } else if(yTiltPos < 0) {
    return -1;
  } else {
    return 0;
  }
}


int playerX = 1;
int playerY = 1;

void drawPlayer(int xDirection, int yDirection ){

  // TODO: Gör klump till loop och egen funktion
	killPixel(playerX, playerY);
	killPixel(playerX+1, playerY);
	killPixel(playerX, playerY+1);
	killPixel(playerX+1, playerY+1);

	if ((xDirection == 1) && (playerX < SCREEN_WIDTH - PLAYER_WIDTH - 1) &&
          (readPixel(playerX + PLAYER_WIDTH, playerY) == 0) &&
                (readPixel(playerX + PLAYER_WIDTH, playerY + PLAYER_HEIGHT - 1) == 0)) { // moves ball to the right
		playerX++;

	} else if((xDirection == -1) && (playerX > 1) &&
          (readPixel(playerX - 1, playerY) == 0) &&
                (readPixel(playerX - 1, playerY + PLAYER_HEIGHT - 1) == 0)) { // moves ball to the left
		playerX--;
	}

	if ((yDirection == 1) && (playerY > 1) &&
          (readPixel(playerX, playerY - 1) == 0) &&
                (readPixel(playerX + PLAYER_WIDTH - 1, playerY - 1) == 0)) { // moves ball upwards
		playerY--;
	}

	else if ((yDirection == - 1) && (playerY < SCREEN_HEIGHT - PLAYER_HEIGHT - 1) &&
          (readPixel(playerX, playerY + 2) == 0) &&
                (readPixel(playerX + 1, playerY + 2) == 0)) { // moves ball downwards
		playerY++;
	}

  // TODO: Gör klump till loop och egen funktion
	drawPixel(playerX, playerY);
	drawPixel(playerX+1, playerY);
	drawPixel(playerX, playerY+1);
	drawPixel(playerX+1, playerY+1);

}

























// this comment is intentional
