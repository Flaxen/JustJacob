#include <pic32mx.h>
#include <stdint.h>

#include "headerfiles/displayFunctions.h"
#include "headerfiles/i2cFunctions.h"
#include "headerfiles/LSM6DS3addresses.h"
#include "headerfiles/gameFunctions.h"

int main(void) {

	// cheaty things we "borrowed"
	char buf[32], *s, *t;

	spiInit();
	i2cInit();

	display_init();



	setPlayerStartPos();

	while(1) {

		updateTiltPos();
		drawMove(yMoveDirection(), xMoveDirection());
		display_image(0, MAP_CHOICE);




		// display_string(1, s);
		// display_update();
		delay(150000);

	}

	return 0;
}
