#include <pic32mx.h>
#include <stdint.h>

#include "headerfiles/displayFunctions.h"
#include "headerfiles/i2cFunctions.h"
#include "headerfiles/LSM6DS3addresses.h"
#include "headerfiles/gameFunctions.h"
#include "headerfiles/menuFunctions.h"
#include "animations/animationFunctions.h"

int main(void) {

	// initializations
	spiInit();
	i2cInit();
	butensInti();

	display_init();

	// set the map to logo for intro screen
	setMap(logo);

	// dog runs in and "eats" logo
	int dogX = 129;
	int dogY = 5;
	while(dogX > (-TILE_WIDTH)) {
		animateDog(dogX, dogY, 180000);
		dogX -= 4;
	}

	// initialize actually playable map
	setMap(map4);
	setPlayerStartPos();

	// enter menu
	int temp = 0;
	while(1){
		temp = staytMenue(temp);
		menue(temp);
		if(exitMenue(temp)){
			break;
		}
		delay(time);
	}

	// enter game
	while(1) {

		updateTiltPos();
		drawMove(yMoveDirection(), xMoveDirection());
		display_image(0, MAP_CHOICE);

		if(winGame()){
			break;
		}
		delay(150000);
	}

	// empty screen for last screen
	setMap(emptyMap);

	// dog runs in and stops in middle
	dogX = 129;
	dogY = 10;
	while(dogX > (75)) {
		animateDog(dogX, dogY, 180000);
		dogX -= 4;
	}

	// place speaking bubble
	drawTile(dogX-(3*TILE_WIDTH)+7, dogY-8, bubbleTile1);
	drawTile(dogX-(2*TILE_WIDTH)+7, dogY-8, bubbleTile2);
	drawTile(dogX-TILE_WIDTH+7, dogY-8, bubbleTile3);
	drawTile(dogX, dogY, dogIdleTile);
	display_image(0, MAP_CHOICE);

	while(1);

	return 0;
}
