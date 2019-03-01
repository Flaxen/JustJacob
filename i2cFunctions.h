#include <stdbool.h>
#include "LSM6DS3addresses.h"

void write(int subAddres, int data);

/* Convert 8.8 bit fixed point to string representation*/
char *fixed_to_string(uint16_t num, char *buf) {
	bool neg = false;
	uint32_t n;
	char *tmp;

	if(num & 0x8000) {
		num = ~num + 1;
		neg = true;
	}

	buf += 4;
	n = num >> 8;
	tmp = buf;
	do {
		*--tmp = (n  % 10) + '0';
		n /= 10;
	} while(n);
	if(neg)
		*--tmp = '-';

	n = num;
	if(!(n & 0xFF)) {
		*buf = 0;
		return tmp;
	}
	*buf++ = '.';
	while((n &= 0xFF)) {
		n *= 10;
		*buf++ = (n >> 8) + '0';
	}
	*buf = 0;

	return tmp;
}

i2cInit() {
	// initialization i2c for master
	I2C1CON = 0x0;              									// disable i2c1 to make changes
	I2C1BRG = 0xC2;             									// sets speed
	I2C1CONSET = 0x8000;        									// enable i2c for i2c1

	// initialization for the slave LSM6DS3
	write(CTRL10_C, 0x38);												// enable x, y, z axes for gyro
	write(CTRL2_G, 0x60);									  			// set gyro to 416Hz. only available in high performence mode
	write(CTRL3_C, 0x06);													// enable autoincrementing addressing as well as BIG endian

}


/*
awaitAknowledge
DESC:
  Checks the ACKSTAT bit (I2C1STAT<15>) and returns "1" or "0" according to the
  ACKSTAT value.
PRE:
  awaitAknowledge only checks the I2C1STAT register so for proper use I2C1
  should be used.
POST:
  Returns "0" if ACKSTAT is zero, and returns "1" if ACKSTAT holds any other
  value than zero.

*/
int awaitAknowledge(){
  if (I2C1STAT & 0x8000) {
    return 1;
  }
  return 0;
}

/*
awaitIdle
DESC:
  Checks bus idle state by checking if start bit S (I2C1STAT<3>) is high.
PRE:
  awaitIdle only checks the I2C1STAT register so for proper use I2C1 should be
  used. If the bus is not supposed to enter an idle state the function will get
  stuck as the while loop won't end.
POST:
  Leaves loop when the start bit S (I2C1STAT<3>) gets cleared to zero.
*/
void awaitIdle() {
  while((I2C1STAT & 0x8)) {
  }

}


/*
awaitStart
DESC:
  Waits for the start condition event to finish by checking the Start Enable bit
  SEN bit (I2C1CON<0>).
PRE:
  awaitStart only checks the I2C1CON register so for proper use, I2C1 should be
  used.
POST:
  Leaves loop as the Start Enable bit SEN (I2C1CON<0>) gets cleared to zero.
*/
void awaitStart() {
  while(I2C1CON & 0x1) {
  }
}


/*
awaitStop
DESC:
  Waits for the stop condition event to finish by checking the Stop Enable bit
  PEN bit (I2C1CON<2>).
PRE:
  awaitStop only checks the I2C1CON register so for proper use, I2C1 should be
  used.
POST:
  Leaves loop as the Stop Enable bit SEN (I2C1CON<2>) gets cleared to zero.
*/
void awaitStop(){
  while(I2C1CON & 0x4){
  }
}


/*
awaitRecieve
DESC:
  Waits for the recieve condition event to finish by checking the Recieve Enable
  bit RCEN bit (I2C1CON<3>).
PRE:
  awaitRecieve only checks the I2C1CON register so for proper use, I2C1 should be
  used.
POST:
  Leaves loop as the Recieve Enable bit RCEN (I2C1CON<3>) gets cleared to zero.
*/
void awaitRecieve() {
  while(I2C1CON & 0x8) {
  }
}


/*
awaitRestart
DESC:
  Waits for the restart condition event to finish by checking the Restart Enable
  bit RSEN bit (I2C1CON<1>).
PRE:
  awaitRestart only checks the I2C1CON register so for proper use, I2C1 should be
  used.
POST:
  Leaves loop as the Restart Enable bit RCEN (I2C1CON<1>) gets cleared to zero.
*/
void awaitRestart() {
  while(I2C1CON & 0x2) {
  }
}


/*
awaitTransmission
DESC:
  Checks that no transmission is currently in progress by checking the Transmit
  Buffer Full bit (I2C1STAT<0>).
PRE:
  awaitTransmission only checks the I2C1STAT register so for proper use, I2C1
  should be used.
POST:
  Leaves loop as I2C1TRN gets empties which drives the Transmit Buffer Full bit
  (I2C1STAT<0>) low.
*/
void awaitTransmission() {
  while(I2C1STAT & 0x1) {
  }
}

/*
awaitMasterLogicInactive
DESC:
  Checks that all master logic is inactive by checking the five least
  significant bits of I2C1CON (0-4). It also checks the Transmit Status bit
  TRSTAT (I2C1CON<14>) for a non zero value indicating master transmit is in
  progress.
PRE:
  awaitMasterLogicInactive only checks the I2C1CON register so for proper use, I2C1 should be
  used.
POST:
  Leaves loop if both the five least significant bits of I2C1CON (0-4) or the
  TRSTAT (I2C1CON<14>) are zero.
*/
void awaitMasterLogicInactive() {
  while((I2C1CON & 0x1f) || I2C1STAT & 0x4000){
  }
}


/*
sendAndVerifyTransmit
DESC:
  Transmits data provided in the argument "data" onto the bus and retries in
  case acknowledge isn't recieved.
PRE:
  All functions used in sendAndVerifyTransmit are as previously mentioned only
  checking the I2C1 register. For proper use I2C1 should be used or the code
  should be changed accordingly.
POST:
  Puts the data provided in the argument "data" onto the transmit bus I2C1TRN,
  waits for an acknowledge and retires in case an acknowledge is never revieved.
*/
void sendAndVerifyTransmit(int data) {

  awaitMasterLogicInactive();
  I2C1TRN = data;
  awaitMasterLogicInactive();

  while(awaitAknowledge()) {
    awaitMasterLogicInactive();
    I2C1TRN = data;
    awaitMasterLogicInactive();

  }
}


/*
outDataToInt
DESC:
	Converts data from the write function to a readable int. Removes decimals.
	The value that gets saved and returned is in the most significant byte. An
	inValue of 0xFFyy, where y can be any hexadecimal digit, would return the
	integer -1.
PRE:
	Argument inValue must not be larger than 2 byte.
POST:
	Returns the value of the most significant byte of the inValue as a signed int.
*/
int outDataToInt(int inValue) {

	inValue >>= 8;

	if ((inValue & 0x80) == 0x80) {
		inValue = 0xFFFFFF00 + inValue;
		inValue = (~inValue+1)*(-1);
	}

	return inValue;
}

/*
write
DESC:
  Writes the data provided in the argument "data" is written to the LSM6DS3
  register with the address provided in the argument "subAddres".
PRE:
  LSM6DS3 has to be initialized properly. Observe that the LSM6DS3 can have one
  of two different addresses chosen by the LSM6DS3 CS pin.
  This function uses the I2C1 ports SDA1 and SCL1. Hardware should be hoocked
  up properly.
  All functions used in sendAndVerifyTransmit are as previously mentioned only
  checking the I2C1 register. For proper use I2C1 should be used or the code
  should be changed accordingly.
POST:
  Writes data to LSM6DS3 register with the provided address.
*/
void write(int subAddres, int data) {

  awaitIdle();                                  // waits for the bus to enter idle
  I2C1CONSET = 0x1;                             // asserts start conditon
  awaitStart();                                 // waits for the Start Event to finish

  sendAndVerifyTransmit(SLAVEADDRESSWRITE);     // sends the address of the LSM6DS3, effectively opening comms for write
  sendAndVerifyTransmit(subAddres);             // sends the subAddres of the LSM6DS3 register to be written to
  sendAndVerifyTransmit(data);                  // sends and writes the data to the chosen LSM6DS3 register

  awaitMasterLogicInactive();                   // waits for all master logic to be deactivated to allow stop condition
  I2C1CONSET = 0x4;                             // asserts stop conditon
  awaitStop();                                  // waits for the Stop Event to finish

}

/*
read
DESC:
  Reads and returns the data from the register of the LSM6DS3 register with the
  matching address provided in the "subAddres" argument.
PRE:
  LSM6DS3 has to be initialized properly. Observe that the LSM6DS3 can have one
  of two different addresses chosen by the LSM6DS3 CS pin.
  This function uses the I2C1 ports SDA1 and SCL1. Hardware should be hoocked
  up properly.
  All functions used in sendAndVerifyTransmit are as previously mentioned only
  checking the I2C1 register. For proper use I2C1 should be used or the code
  should be changed accordingly.
POST:
  Returns the data from the LSM6DS3 register with the matching address of the
  one provided in the subAddres argument.
*/
int read(int subAddres) {

  awaitIdle();                                  // waits for the bus to enter idle
  I2C1CONSET = 0x1;                             // asserts start conditon
  awaitStart();                                 // waits for the Start Event to finish

  sendAndVerifyTransmit(SLAVEADDRESSWRITE);     // sends the address of the LSM6DS3, effectively opening comms for write
  sendAndVerifyTransmit(subAddres);             // sends the subAddres of the LSM6DS3 register to be read

  awaitTransmission();                          // waits for any earlier transmissions to finish to allow restart
  I2C1CONSET = 0x2;                             // asserts restart condition
  awaitRestart();                               // waits for the Restart Event to finish

  sendAndVerifyTransmit(SLAVEADDRESSREAD);      // sends the address of the LSM6DS3, effectively opening comms for read

  awaitMasterLogicInactive();                   // waits for all master logic to be deactivated to allow restart condition
  I2C1CONSET = 0x8;                             // asserts recieve conditon
  awaitRecieve();                               // waits for the Recieve Event to finish

  int outData = I2C1RCV;                        // saves the higher bits of the read data to variable for future return

  I2C1CONCLR = 0x20;                            // clears ACKDT to allow generation of an acknowledge
  I2C1CONSET = 0x10;                            // sets ACKEN to in combination with row above generate and acknowledge

  outData = outData << 8;                       // shifts the return variable by eight to make room for lower

  awaitMasterLogicInactive();                   // waits for all master logic to be deactivated to allow recieve condition
  I2C1CONSET = 0x8;                             // assert recieve condition
  awaitRecieve();                               // waits for Recieve Enable Event to finish

  outData |= I2C1RCV;                           // loads the lower half of the read data into the lower half of the return variable

  I2C1CONSET = 0x30;                            // generates a NACK

  awaitMasterLogicInactive();                   // waits for all master logic to be deactivated to allow stop condition
  I2C1CONSET = 0x4;                             // asserts stop condition
  awaitStop();                                  // waits for Stop Enable Event to finish

  return outDataToInt(outData);                 // returns return variable as readable int.
}
