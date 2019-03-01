#include <pic32mx.h>
#include <stdint.h>

#include "displayFunctions.h"
#include "i2cFunctions.h"
#include "LSM6DS3addresses.h"
#include "gameFunctions.h"

int main(void) {

	// cheaty things we "borrowed"
	char buf[32], *s, *t;

	spiInit();
	i2cInit();

	display_init();

	while(1) {
		updateTiltPos();

		displayTest();
		display_image(0, icon);

		if(xMoveDirection() > 0) {
			TRISFCLR = 0x1; //lampor
			PORTFSET = 0x1;
		} else {
			TRISFCLR = 0x1; //lampor
			PORTFCLR = 0x1;
		}

		// display_string(1, s);
		// display_update();
		delay(10000);

	}

	return 0;
}
