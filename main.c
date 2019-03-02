#include <pic32mx.h>
#include <stdint.h>

#include "headerfiles/displayFunctions.h"
#include "headerfiles/i2cFunctions.h"
#include "headerfiles/LSM6DS3addresses.h"
#include "headerfiles/gameFunctions.h"
#include "headerfiles/menuFunctions.h"

int main(void) {

	spiInit();
	i2cInit();
	butensInti();

	display_init();



	setPlayerStartPos();


	int temp1 = 1;
	int temp2 = 0;
	while(temp1){
		temp2 = staytMenue(temp2);
		menue(temp2);
		temp1 = exitMenue(temp2);
		delay(time);
	}
	int temp3 = 1;
	while(1) {

		updateTiltPos();
		drawMove(yMoveDirection(), xMoveDirection());
		display_image(0, MAP_CHOICE);

		if(winGame()){
			break;
		}
		delay(150000);

	}

	display_string(0, "");
	display_string(1, "YOU WON!!!!!");
	display_string(2, "");
	display_string(3, "");
	display_update();

	return 0;
}
