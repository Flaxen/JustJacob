#include <math.h>
// #include "i2cFunctions.h"
#include "LSM6DS3addresses.h"

/*
updateTiltPos
DESC:
  Keeps track of the angle of the board.
PRE:
  Board has to lay flat on a surface during bootup as it caibrates 0 degrees to
  the position it has at startup.
POST:
  Adds or subtracts the current angle/second value.
*/
int xTiltPos = 0;
int yTiltPos = 0;

void updateTiltPos() {
  xTiltPos += (read(OUTX_L_G)+1);
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
    return 1;
  } else if(xTiltPos < 0) {
    return -1;
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


void ritaBol(int xAxel, int yAxel ){

	killPixel(x,y);
	killPixel(x+1, y);
	killPixel(x,y+1);
	killPixel(x+1,y+1);

	if ((xAxel == 1) && (x < 126) && (readPixel(x+2,y) == 0) && (readPixel(x+2,y+1) == 0)){ // flytar boll åt höger
		x++;
	}

	else if((xAxel == -1) && (x > 1) && (readPixel(x-1,y) == 0) && (readPixel(x-1,y+1) == 0)){ // flytar bol åt vänster
		x--;
	}

	if ((yAxel == 1) && (y > 1) && (readPixel(x,y-1) == 0) && (readPixel(x+1,y-1) == 0)){ // flytar bol uppåt
		y--;
	}

	else if ((yAxel == -1) && (y < 29) && (readPixel(x,y+2) == 0) && (readPixel(x+1,y+2) == 0)){ // flytar bol nedåt
		y++;
	}

	drawPixel(x,y);
	drawPixel(x+1, y);
	drawPixel(x,y+1);
	drawPixel(x+1,y+1);

}

























// this comment is intentional
