


void  butensInti() {
	// initialization for butten 2-4
	TRISDSET = 0xd0;

}

int getbuten(){
  // gets data from butten 2-4 and shifts it to bit 0-2
	return((PORTD >> 5) & 0x7);
}

int time = 0;
void uppdatMenue() {
  // Decreases the delay time
  if(time > 0){
    time == 0;
  }
}

void menue(int position) {
  // Displays the menu
	display_string(0, "");
	display_string(1, "Play");
	display_string(2, "Settings");
	display_string(3, "");

	if (position == 0){
		display_string(1, ">Play");
	}

	else if(position == 1){
		display_string(2, ">Settings");
	}

	display_update();
}

int staytMenue(int present){
  // Changes the state in the menu
	if(getbuten() == 4){
		present++;
    time = 1000000;
	}
	if (present > 1){
		present = 0;
	}
	return present;
}

int exitMenue(int position){
  // Exits menu
	if(position == 0 && getbuten() == 2){
		return 1;
	}
	return 0;
}


void settings(int position) {
  // Displays the settings
	char rowZero[] = "Player size axb";
	rowZero[12] = PLAYER_WIDTH + '0';
	rowZero[14] = PLAYER_WIDTH + '0';
	display_string(0, rowZero);
	display_string(1, "Play");
	display_string(2, "Settings");
	display_string(3, "");

	if (position == 0){
		display_string(1, ">Play");
	}

	else if(position == 1){
		display_string(2, ">Settings");
	}

	display_update();
}


int enterSettings(int position){
  // Enter settings
	if(position == 1 && getbuten() == 2){
		return 1;
	}
	return 0;
}
