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



























// this comment is intentional
