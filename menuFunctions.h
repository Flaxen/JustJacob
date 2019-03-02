


void  butensInti() {
	// initialization for buttens
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
    time--;
  }
}

void menue(int position) {
  // Displays the menu
	display_string(0, "");
	display_string(1, "Play");
	display_string(2, "Settings");
	display_string(3, "Exit");

	if (position == 0){
		display_string(1, ">Play");
	}

	else if(position == 1){
		display_string(2, ">Settings");
	}

	else if (position == 2){
		display_string(3, ">Exit");
	}

	display_update();
}

int staytMenue(int present){
  // Changes the state in the menu
	if(getbuten() == 4){
		present++;
    time = 1000000;
	}
	if (present > 2){
		present = 0;
	}
	return present;
}

int exitMenue(int position){
  // Exits menu
	if(position == 0 && getbuten() == 2){
		return 0;
	}
	return 1;
}
