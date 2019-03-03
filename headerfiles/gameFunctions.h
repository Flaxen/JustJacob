#include <math.h>

#include "LSM6DS3addresses.h"
#include "../settings.h"

/*
updateTiltPos
Written by Alexander Carlsson
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


int playerX = 0;
int playerY = 0;

/*
setPlayerStartPos
DESC:
  Sets the start coordinates for the player
PRE:
The coordinates most place the whole player on screen
POST:
  The start coordinates for the upper left corner of the player is set
*/

void setPlayerStartPos() {
    playerX = START_COORDINATE_X;
    playerY = START_COORDINATE_Y;
}


/*
killPlayer
DESC:
  takes the player of the board
PRE:
  The x and y coordinates for the left upper corner of the player
  needs to be in playerX respectively playerY and the player
  PLAYER_WIDTH, PLAYER_WIDTH needs to be bigger than 0 and smaller than the screen size
POST:
  Player is no longer on the screen
*/
void killPlayer() {

  int i,j;
  for(i = 0; i < PLAYER_WIDTH; i++){
    for(j = 0; j < PLAYER_HEIGHT; j++){
      killPixel(playerX + i, playerY + j);
    }
  }

}

/*
drawPlayer
DESC:
  Places the player on the board
PRE:
  The x and y coordinates for the left upper corner of the player
  needs to be in playerX respectively playerY and the player
  PLAYER_WIDTH, PLAYER_WIDTH needs to be bigger than 0 and smaller than the screen size
POST:
  Player is placed on the screen
*/
void drawPlayer(){

  int i, j;
  for(i = 0; i < PLAYER_WIDTH; i++){
    for(j = 0; j < PLAYER_HEIGHT; j++){
      drawPixel(playerX + i, playerY + j);
    }
  }

}


/*
moveRight
DESC:
  Returns 1 if the player can move right and 0 otherwise
PRE:
  The x and y coordinates for the left upper corner of the player
  needs to be in playerX respectively playerY and the player
  PLAYER_WIDTH, PLAYER_WIDTH needs to be bigger than 0 and Smaller than the screen size
POST:
  Returns true or false if the player is allowed to move or not
*/
int moveRight(){
  int res = 0;
  if (playerX + PLAYER_WIDTH < SCREEN_WIDTH){   //Keeps the player from moving of screen
    int i;
    int count = 0;
    for(i = 0; i < PLAYER_HEIGHT; i++){         //Keeps the player from moving through walls
      if (readPixel(playerX + PLAYER_WIDTH, playerY + i) == 0){
        count++;
      }
    }
    if (count == PLAYER_HEIGHT){
      res = 1;
    }
  }

  return res;
}

/*
moveLeft
DESC:
  Returns 1 if the player can move left and 0 otherwise
PRE:
  The x and y coordinates for the left upper corner of the player
  needs to be in playerX respectively playerY and the player
  PLAYER_WIDTH, PLAYER_WIDTH needs to be bigger than 0 and Smaller than the screen size
POST:
  Returns true or false if the player is allowed to move or not
*/
int moveLeft(){
  int res = 0;
  if(playerX > 1){                              //Keeps the player from moving of screen
    int i;
    int count = 0;
    for(i = 0; i < PLAYER_HEIGHT; i++){         //Keeps the player from moving through walls
      if(readPixel(playerX -1, playerY + i) == 0){
        count++;
      }
    }
    if (count == PLAYER_HEIGHT){
      res = 1;
    }
  }
  return res;
}

/*
moveUpp
DESC:
  Returns 1 if the player can move up and 0 otherwise
PRE:
  The x and y coordinates for the left upper corner of the player
  needs to be in playerX respectively playerY and the player
  PLAYER_WIDTH, PLAYER_WIDTH needs to be bigger than 0 and Smaller than the screen size
POST:
  Returns true or false if the player is allowed to move or not
*/
int moveUpp(){
  int res = 0;
  if(playerY > 0){                              //Keeps the player from moving of screen
    int i;
    int count = 0;
    for(i = 0; i < PLAYER_WIDTH; i++){          //Keeps the player from moving through walls
      if(readPixel(playerX + i, playerY -1) == 0){
        count++;
      }
    }
    if (count == PLAYER_WIDTH){
      res = 1;
    }
  }
  return res;
}


/*
moveDown
DESC:
  Returns 1 if the player can move down and 0 otherwise
PRE:
  The x and y coordinates for the left upper corner of the player
  needs to be in playerX respectively playerY and the player
  PLAYER_WIDTH, PLAYER_WIDTH needs to be bigger than 0 and Smaller than the screen size
POST:
  Returns true or false if the player is allowed to move or not
*/
int moveDown(){
  int res = 0;
  if( playerY + PLAYER_HEIGHT < SCREEN_HEIGHT){ //Keeps the player from moving of screen
    int i;
    int count = 0;
    for(i = 0; i < PLAYER_WIDTH; i++){          //Keeps the player from moving through walls
      if(readPixel(playerX + i, playerY + PLAYER_HEIGHT) == 0){
        count++;
      }
    }
    if (count == PLAYER_WIDTH){
      res = 1;
    }
  }
  return res;
}


/*
drawMove
DESC:
  Takes the player of the screen moves it to the next position and puts the player back on the screen
PRE:
  The x and y coordinates for the left upper corner of the player needs to be in playerX respectively playerY and the player  PLAYER_WIDTH, PLAYER_WIDTH needs to be bigger than 0 and Smaller than the screen size
POST:
  Moves the player on the screen if it’s allowed
*/
void drawMove(int xDirection, int yDirection ){

  killPlayer();

  if (xDirection == 1 && moveRight() == 1){ // moves player right
    playerX++;
  }

	else if((xDirection == -1) && moveLeft() == 1) { // moves player left
		playerX--;
	}

  if(yDirection == 1 && moveUpp() == 1){ // moves player upp
    playerY--;

  }

  else if(yDirection == -1 && moveDown() == 1){ // moves ball down
    playerY++;
  }

  drawPlayer();
}


/*
winGame
DESC:
  Determines if player has won the game
PRE:
  The x and y coordinates for the left upper corner of the player needs to be in playerX respectively playerY and the player  PLAYER_WIDTH, PLAYER_WIDTH needs to be bigger than 0 and Smaller than the screen size
POST:
  Returns 1 if player is won and 0 otherwise
*/

int winGame(){
  if(playerX == 1){
    return 1;
  }
  return 0;
}























// this comment is intentional
