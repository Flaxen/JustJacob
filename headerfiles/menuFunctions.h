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
	Displays and cycles cursor for the main(and only) menu. Updates display
	according to provided position argument
PRE:
	n/a
POST:
	Displays a variation of strings on screen based on input.
*/
void menu(int position) {
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

	display_update();
}

/*
stateMenu
Written by Johanna Jansson
DESC:
	Keeps track of and returns the menu position.
PRE:
	Buttons initialized?
POST:
	Returnes an updated menu position.
*/
int stateMenu(int position){
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
exitMenu
Written by Johanna Jansson
DESC:
	Returns 1 if the player has chosen to leave the menu.
PRE:
	Buttons initialized?
POST:
	Returns "1" or "0".
*/
int exitMenu(int position){
  // Exits menu
	if(position == 0 && getButton() == 2){
		return 1;
	}
	return 0;
}

int currentMap = 4;
/*
settings
Written by Johanna Jansson
DESC:
	Displays and cycles cursor for the settings. Updates display
	according to provided position argument
PRE:
	n/a
POST:
	Displays a variation of strings on screen based on input.
*/
void settings(int position) {
  // Displays the settings
	char rowZero[] = " Player speed: -";
	rowZero[15] = PLAYER_SPEED + '0';
	// rowZero[15] = PLAYER_WIDTH + '0';

	char rowOne[] = " Map: map-";
	rowOne[9] = currentMap + '0';

	display_string(0, "");
	display_string(1, rowZero);
	display_string(2, rowOne);
	display_string(3, " Exit");

	if (position == 0){
		rowZero[0] = '>';
		display_string(1, rowZero);
	}

	else if(position == 1){
		rowOne[0] = '>';
		display_string(2, rowOne);
	}
	else if(position == 2){
		display_string(3, ">Exit");
	}


	display_update();
}

/*
stateSettings
Written by Johanna Jansson
DESC:
	Keeps track of and returns the settings position.
PRE:
	Buttons initialized?
POST:
	Returnes an updated settings position.
*/
int stateSettings(int position){
  // Changes the state in the menu
	if(getButton() == 4){
		position++;
	}
	if (position > 2){
		position = 0;
	}
	return position;
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
int enterSettings(int position){
  // Enter settings
	if(position == 1 && getButton() == 2){
		return 1;
	}
	return 0;
}

/*
exitSettings
Written by Johanna Jansson
DESC:
	Returns 1 if the player has chosen to leave the settings.
PRE:
	Buttons initialized?
POST:
	Returns "1" or "0".
*/
int exitSettings(int position){
  // Exits menu
	if(position == 2 && getButton() == 2){
		return 1;
	}
	return 0;
}

/*
map
Written by Johanna Jansson
DESC:
	Displays and cycles cursor for the map. Updates display
	according to provided position argument
PRE:
	n/a
POST:
	Displays a variation of strings on screen based on input.
*/
void map(int position) {
  // Displays the map

	char row[] = " Map: map-";
	row[9] = currentMap + '0';

	display_string(0, "");
	display_string(1, row);
	display_string(2, " Exit");
	display_string(3, "");

	if (position == 0){
		row[0] = '>';
		display_string(1, row);
	}

	else if(position == 1){
		display_string(2, ">Exit");
	}


	display_update();
}

/*
stateMap
Written by Johanna Jansson
DESC:
	Keeps track of and returns the settings position.
PRE:
	Buttons initialized?
POST:
	Returnes an updated settings position.
*/
int stateMap(int position){
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
enterMap
Written by Johanna Jansson
DESC:
	Chang map.
PRE:
	Buttons initialized?
POST:
	Chang map.
*/
int enterMap(int position){
  // Enter map
	if(position == 1 && getButton() == 2){
		return 1;
	}
	return 0;
}

/*
changMap
Written by Johanna Jansson
DESC:
	Chang map.
PRE:
	Buttons initialized?
POST:
	Chang map.
*/
void changMap(int position){
	if(position == 0 && getButton() == 2){
		currentMap++;
	}
	if(currentMap > 5){
		currentMap = 0;
	}
}

/*
exitMap
Written by Johanna Jansson
DESC:
	Returns 1 if the player has chosen to leave the map.
PRE:
	Buttons initialized?
POST:
	Returns "1" or "0".
*/
int exitMap(int position){
  // Exits menu
	if(position == 1 && getButton() == 2){
		return 1;
	}
	return 0;
}

/*
speed
Written by Johanna Jansson
DESC:
	Displays and cycles cursor for the speed. Updates display
	according to provided position argument
PRE:
	n/a
POST:
	Displays a variation of strings on screen based on input.
*/
void speed(int position) {
  // Displays the map

	char row[] = " Speed: -";
	row[8] = PLAYER_SPEED + '0';

	display_string(0, "");
	display_string(1, row);
	display_string(2, " Exit");
	display_string(3, "");

	if (position == 0){
		row[0] = '>';
		display_string(1, row);
	}

	else if(position == 1){
		display_string(2, ">Exit");
	}


	display_update();
}

/*
stateSpeed
Written by Johanna Jansson
DESC:
	Keeps track of and returns the speed position.
PRE:
	Buttons initialized?
POST:
	Returnes an updated speed position.
*/
int stateSpeed(int position){
  // Changes the state in the speed
	if(getButton() == 4){
		position++;
	}
	if (position > 1){
		position = 0;
	}
	return position;
}

/*
enterSpeed
Written by Johanna Jansson
DESC:
	Chang speed.
PRE:
	Buttons initialized?
POST:
	Chang speed.
*/
int enterSpeed(int position){
  // Enter map
	if(position == 0 && getButton() == 2){
		return 1;
	}
	return 0;
}

/*
changSpeed
Written by Johanna Jansson
DESC:
	Chang speed.
PRE:
	Buttons initialized?
POST:
	Chang speed.
*/
void changSpeed(int position){
	if(position == 0 && getButton() == 2){
		PLAYER_SPEED++;
	}
	if(PLAYER_SPEED > 5){
		PLAYER_SPEED = 1;
	}
}

/*
exitSpeed
Written by Johanna Jansson
DESC:
	Returns 1 if the player has chosen to leave the speed.
PRE:
	Buttons initialized?
POST:
	Returns "1" or "0".
*/
int exitSpeed(int position){
  // Exits speed
	if(position == 1 && getButton() == 2){
		return 1;
	}
	return 0;
}
