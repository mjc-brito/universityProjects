#include <stdio.h>
#include <conio.h>
#include <stdio.h>

#include <interface.h>

// Portos
void initializeHardwarePorts() {
	// Input
	createDigitalInput(0);
	createDigitalInput(1);
	// Output
	createDigitalOutput(2);
}


// Bits
void setBitValue(uInt8* variable, int n_bit, int new_value_bit)
// given a byte value, set the n bit to value
{
	uInt8 mask_on = (uInt8)(1 << n_bit);
	uInt8 mask_off = ~mask_on;
	if (new_value_bit)  *variable |= mask_on;
	else*variable &= mask_off;
}
int getBitValue(uInt8 value, uInt8 n_bit)
// given a byte value, returns the value of bit n
{
	return(value & (1 << n_bit));
}


// Cylinder Start
int cylinderStart_getPosition()
{
	int v = readDigitalU8(0);
	if (getBitValue(v, 6))
		return 0;
	else if (getBitValue(v, 5))
		return 1;
	return(-1);
}

void cylinderStart_moveForward()
{
	uInt8 p = readDigitalU8(2);
	setBitValue(&p, 1, 1);
	setBitValue(&p, 0, 0);
	writeDigitalU8(2, p);
}

void cylinderStart_moveBackward()
{
	uInt8 p = readDigitalU8(2);
	setBitValue(&p, 1, 0);
	setBitValue(&p, 0, 1);
	writeDigitalU8(2, p);
}

void cylinderStart_stop()
{
	uInt8 p = readDigitalU8(2);
	setBitValue(&p, 1, 0);
	setBitValue(&p, 0, 0);
	writeDigitalU8(2, p);
}


// Cylinder 1
int cylinder1_getPosition()
{
	int v = readDigitalU8(0);
	if (!getBitValue(v, 4))
		return 0;
	else if (!getBitValue(v, 3))
		return 1;
	return(-1);
}

void cylinder1_moveForward()
{
	uInt8 p = readDigitalU8(2);
	setBitValue(&p, 4, 1);
	setBitValue(&p, 3, 0);
	writeDigitalU8(2, p);
}

void cylinder1_moveBackward()
{
	uInt8 p = readDigitalU8(2);
	setBitValue(&p, 4, 0);
	setBitValue(&p, 3, 1);
	writeDigitalU8(2, p);
}

void cylinder1_stop()
{
	uInt8 p = readDigitalU8(2);
	setBitValue(&p, 4, 0);
	setBitValue(&p, 3, 0);
	writeDigitalU8(2, p);
}


// Cylinder 2
int cylinder2_getPosition()
{
	int v = readDigitalU8(0);
	if (!getBitValue(v, 2))
		return 0;
	else if (!getBitValue(v, 1))
		return 1;
	return(-1);
}

void cylinder2_moveForward()
{
	uInt8 p = readDigitalU8(2);
	setBitValue(&p, 6, 1);
	setBitValue(&p, 5, 0);
	writeDigitalU8(2, p);
}

void cylinder2_moveBackward()
{
	uInt8 p = readDigitalU8(2);
	setBitValue(&p, 6, 0);
	setBitValue(&p, 5, 1);
	writeDigitalU8(2, p);
}

void cylinder2_stop()
{
	uInt8 p = readDigitalU8(2);
	setBitValue(&p, 6, 0);
	setBitValue(&p, 5, 0);
	writeDigitalU8(2, p);
}


// Conveyor
void conveyorMove()
{
	uInt8 p = readDigitalU8(2);
	setBitValue(&p, 2, 1);
	writeDigitalU8(2, p);
}

void conveyorStop()
{
	uInt8 p = readDigitalU8(2);
	setBitValue(&p, 2, 0);
	writeDigitalU8(2, p);
}


// Docks Switches
bool switchDock1Pressed()
{
	int v = readDigitalU8(1);
	if (getBitValue(v, 4))
		return TRUE;
	return FALSE;
}

bool switchDock2Pressed()
{
	int v = readDigitalU8(1);
	if (getBitValue(v, 3))
		return TRUE;
	return FALSE;
}

bool switchDockEndPressed()
{
	int v = readDigitalU8(1);
	if (getBitValue(v, 2))
		return TRUE;
	return FALSE;
}


// Identification Sensors
int getIdentificationSensors()
{
	int v = readDigitalU8(1);
	if (getBitValue(v, 5))
		return 1;
	else if (getBitValue(v, 6))
		return 2;
	return 0;
}


// Cylinder Sensors
bool isBrickAtCylinder1()
{
	int v = readDigitalU8(0);
	if (getBitValue(v, 0))
		return TRUE;
	return FALSE;
}

bool isBrickAtCylinder2()
{
	int v = readDigitalU8(0);
	if (getBitValue(v, 0))
		return TRUE;
	return FALSE;
}

// LED
void turnLEDon()
{
	uInt8 p = readDigitalU8(2);
	setBitValue(&p, 7, 1);
	writeDigitalU8(2, p);
}

void turnLEDoff()
{
	uInt8 p = readDigitalU8(2);
	setBitValue(&p, 7, 0);
	writeDigitalU8(2, p);
}
