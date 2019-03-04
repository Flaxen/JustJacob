#include <pic32mx.h>
#include <stdint.h>

#include "headerfiles/i2cFunctions.h"
#include "headerfiles/LSM6DS3addresses.h"

#include "headerfiles/displayFunctions.h"
#include "headerfiles/gameFunctions.h"
#include "headerfiles/menuFunctions.h"
#include "animations/animationFunctions.h"
#include "customMapMaker/customMaps.c"

// #include "settings.h"


int main(void) {

	// initializations
	spiInit();
	i2cInit();
	buttonsInit();

	display_init();

	START:
	// set the map to logo for intro screen
	setMap(logo);

	// dog runs in and "eats" logo
	int dogX = 129;
	int dogY = 5;
	while(dogX > (-TILE_WIDTH)) {
		animateDog(dogX, dogY, 180000);
		dogX -= 4;
		if(exit()){
			goto MENU;
		}
	}

	MENU:
	delay(1000000);
	// enter menu
	int menuRow = 0;
	int statesettingsRow = 0;
	int page = 0;
	while(1){
		if(page == 0){
			menuRow = state(menuRow);
			menu(page, menuRow);
			if(play(page, menuRow)){
				goto GAME;
			}
			if(enterSettings1(page, menuRow)){
				page = 1;
			}
		}
		else{
			statesettingsRow = state(statesettingsRow);
			menu(page, statesettingsRow);
			changMap(page, statesettingsRow);
			changSpeed(page, statesettingsRow);
			if(exit()){
				page = 0;
			}
		}
		delay(1000000);
	}

	GAME:
	// initialize actually playable map
	setMap(maps[currentMap]);
	setPlayerStartPos();


	// enter game
	while(1) {
		updateTiltPos();
		drawMove(xMoveDirection(), yMoveDirection());
		display_image(0, MAP_CHOICE);

		if(winGame()){
			break;
		}
		// goes to menu
		if(exit()){
			goto MENU;
		}
		delay((150000*3)/PLAYER_SPEED);
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

	// restarts the game
	while (1) {
		if(awaitAndRestart()){
			goto START;
		}
	}



	return 0;
}
