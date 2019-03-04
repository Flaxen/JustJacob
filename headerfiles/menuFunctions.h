/*
All contents in this file are written by Johanna Jansson
Written by Johanna Jansson
*/

void  buttonsInit() {
	// initialization for buttons
	TRISDSET = 0xd0;

}

int getButton(){
  // gets data from button 2-4 and shifts it to bit 0-2
	return((PORTD >> 5) & 0x7);
}

/*
menu
Written by Johanna Jansson
DESC:
	Displays and cycles cursor for the menu and settings. Updates display
	according to provided page and position argument
PRE:
	n/a
POST:
	Displays a variation of strings on screen based on input.
*/
int currentMap = 4;
void menu(int page, int position) {
  if(page == 0){
		// Displays the menu
		display_string(0, "");
		display_string(1, " Play");
		display_string(2, " Settings");
		display_string(3, "");

		if (position == 0){
			display_string(1, ">Play");
		}

		else if(position == 1){
			display_string(2, ">Settings");
		}
	}


	if(page == 1)	{
			// Displays the settings
			char rowZero[] = " Player speed: -";
			rowZero[15] = PLAYER_SPEED + '0';
			// rowZero[15] = PLAYER_WIDTH + '0';

			char rowOne[] = " Map: map-";
			rowOne[9] = currentMap + '0';

			display_string(0, "");
			display_string(1, rowZero);
			display_string(2, rowOne);
			display_string(3, "");

			if (position == 0){
				rowZero[0] = '>';
				display_string(1, rowZero);
			}

			else if(position == 1){
				rowOne[0] = '>';
				display_string(2, rowOne);
			}
		}


	display_update();
}

/*
state
Written by Johanna Jansson
DESC:
	Keeps track of and returns the position.
PRE:
	Buttons initialized?
POST:
	Returnes an updated position.
*/
int state(int position){
  // Changes the state in the menu
	if(getButton() == 4){
		position++;
	}
	if (position > 1){
		position = 0;
	}
	return position;
}


/*
play
Written by Johanna Jansson
DESC:
	Returns 1 if the player has chosen to play game.
PRE:
	Buttons initialized?
POST:
	Returns "1" or "0".
*/
int play(int page, int position){
  // Exits menu
	if(position == 0 && getButton() == 2 && page == 0){
		return 1;
	}
	return 0;
}

/*
enterSettings
Written by Johanna Jansson
DESC:
	Returns 1 if the player has chosen to enter settings.
PRE:
	Buttons initialized?
POST:
	Returns "1" or "0".
*/
int enterSettings1(int page, int position){
  // Enter settings
	if(position == 1 && getButton() == 2 && page == 0){
		return 1;
	}
	return 0;
}

/*
changSpeed
Written by Johanna Jansson
DESC:
	Change speed of player if the cursor poynts to speed and butten is pusht.
PRE:
	Buttons initialized?
POST:
	Change speed of player.
*/
void changSpeed(int page ,int position){
	if(position == 0 && getButton() == 2 && page == 1){
		PLAYER_SPEED++;
	}
	if(PLAYER_SPEED > 5){
		PLAYER_SPEED = 1;
	}
}

/*
changMap
Written by Johanna Jansson
DESC:
	Change map if the cursor poynts to map and butten is pushed.
PRE:
	Buttons initialized?
POST:
	Change map.
*/
void changMap(int page, int position){
	if(position == 1 && getButton() == 2 && page == 1){
		currentMap++;
	}
	if(currentMap > 5){
		currentMap = 0;
	}
}

/*
exit
Written by Johanna Jansson
DESC:
	Returns 1 if the player has chosen to push button.
PRE:
	Buttons initialized?
POST:
	Returns "1" or "0".
*/
int exit(){
	if(getButton() == 1){
		return 1;
	}
	return 0;
}
