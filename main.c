#include <pic32mx.h>
#include <stdint.h>

#include "displayFunctions.h"
#include "i2cFunctions.h"
#include "LSM6DS3addresses.h"

int main(void) {

		// cheaty things we "borrowed"
		uint16_t temp;
		char buf[32], *s, *t;

	spiInit();
	i2cInit();

	display_init();

	// display_string(0, "Gronsaker");
	// display_string(1, "");
	// display_string(2, "");
	// display_string(3, "");
	// display_update();

	while(1) {

		displayTest();
		display_image(0, icon);

		// temp = read(0x24);
		//
		// s = fixed_to_string(temp, buf);
		//
		// display_string(1, s);
		// display_update();
		delay(1000000);


		delay(8000);
	}



	return 0;
}
