#include "pch.h"

#include"carwash.h"

HANDLE mutex_kit;

uInt8 savedBits;

void initializeCarWash() { 
	if (mutex_kit == NULL)
		mutex_kit = CreateSemaphore(NULL, 1, 10, NULL);
	createDigitalInput(0);
	createDigitalInput(1);
	createDigitalOutput(2);

}


void setBitValue(uInt8* variable, int n_bit, int new_value_bit)
// given a byte value, set the n bit to value
{
	uInt8  mask_on = (uInt8)(1 << n_bit);
	uInt8  mask_off = ~mask_on;
	if (new_value_bit)* variable |= mask_on;
	else                *variable &= mask_off;
}


int getBitValue(uInt8 value, uInt8 bit_n)
// given a byte value, returns the value of its bit n
{
	return(value & (1 << bit_n));
}
void emergencyStop() {
	uInt8 p2 = readDigitalU8(2);
	savedBits = p2;
	setBitValue(&p2, 0, 0);
	setBitValue(&p2, 1, 0);
	setBitValue(&p2, 2, 0);
	setBitValue(&p2, 3, 0);
	setBitValue(&p2, 4, 0);
	setBitValue(&p2, 5, 0);
	setBitValue(&p2, 6, 0);
	setBitValue(&p2, 7, 0);
	writeDigitalU8(2, p2);
}

void emergencyResume() {
	uInt8 p2 = readDigitalU8(2);
	p2 = savedBits;
	writeDigitalU8(2, p2);
}

void moveBrushRight() {
	WaitForSingleObject(mutex_kit, INFINITE);
	uInt8 vp2 = readDigitalU8(2);
	setBitValue(&vp2, 0, 1);
	setBitValue(&vp2, 1, 0);
	writeDigitalU8(2, vp2);
	ReleaseSemaphore(mutex_kit, 1, NULL);

}


void moveBrushLeft() {
	WaitForSingleObject(mutex_kit, INFINITE);
	uInt8 vp2 = readDigitalU8(2);
	setBitValue(&vp2, 0, 0);
	setBitValue(&vp2, 1, 1);
	writeDigitalU8(2, vp2);
	ReleaseSemaphore(mutex_kit, 1, NULL);
}



void stopHorizMovement() {
	WaitForSingleObject(mutex_kit, INFINITE);
	uInt8 vp2 = readDigitalU8(2);
	setBitValue(&vp2, 0, 0);
	setBitValue(&vp2, 1, 0);
	writeDigitalU8(2, vp2);
	ReleaseSemaphore(mutex_kit, 1, NULL);
}




void moveBrushUp() {
	WaitForSingleObject(mutex_kit, INFINITE);
	uInt8 vp2 = readDigitalU8(2);
	setBitValue(&vp2, 2, 1);
	setBitValue(&vp2, 3, 0);
	writeDigitalU8(2, vp2);
	ReleaseSemaphore(mutex_kit, 1, NULL);
}


void moveBrushDown() {
	WaitForSingleObject(mutex_kit, INFINITE);
	uInt8 vp2 = readDigitalU8(2);
	setBitValue(&vp2, 2, 0);
	setBitValue(&vp2, 3, 1);
	writeDigitalU8(2, vp2);
	ReleaseSemaphore(mutex_kit, 1, NULL);
}


void stopVerticalMovement() {
	WaitForSingleObject(mutex_kit, INFINITE);
	uInt8 vp2 = readDigitalU8(2);
	setBitValue(&vp2, 2, 0);
	setBitValue(&vp2, 3, 0);
	writeDigitalU8(2, vp2);
	ReleaseSemaphore(mutex_kit, 1, NULL);
}


void lateralBrushRotate() {
	WaitForSingleObject(mutex_kit, INFINITE);
	uInt8 vp2 = readDigitalU8(2);
	setBitValue(&vp2, 4, 1);	
	writeDigitalU8(2, vp2);
	ReleaseSemaphore(mutex_kit, 1, NULL);
}

void lateralBrushStop() {
	WaitForSingleObject(mutex_kit, INFINITE);
	uInt8 vp2 = readDigitalU8(2);
	setBitValue(&vp2, 4, 0);
	writeDigitalU8(2, vp2);
	ReleaseSemaphore(mutex_kit, 1, NULL);
}


void ceilingBrushRotate() {
	WaitForSingleObject(mutex_kit, INFINITE);
	uInt8 vp2 = readDigitalU8(2);
	setBitValue(&vp2, 5, 1);
	writeDigitalU8(2, vp2);
	ReleaseSemaphore(mutex_kit, 1, NULL);
}

void ceilingBrushStop() {
	WaitForSingleObject(mutex_kit, INFINITE);
	uInt8 vp2 = readDigitalU8(2);
	setBitValue(&vp2, 5, 0);
	writeDigitalU8(2, vp2);
	ReleaseSemaphore(mutex_kit, 1, NULL);
}


bool isBrushUp() {
	
	uInt8 p = readDigitalU8(0);
	if (!getBitValue(p, 4))
		return true;
	return false;
}



bool isBrushDown() {
	uInt8 p = readDigitalU8(0);	
	if (!getBitValue(p, 3))
		return true;
	return false;
}


bool isBrushLeft() {
	uInt8 p = readDigitalU8(0);

	if (!getBitValue(p, 5))
		return true;
	return false;
}



bool istBrushRight() {
	uInt8 p = readDigitalU8(0);

	if (!getBitValue(p, 6))
		return true;
	return false;
}


bool isRightInfraRedOn() {
	uInt8 p = readDigitalU8(0);

	if (getBitValue(p, 2))
		return true;
	return false;
}

bool isLeftInfraRedOn() {
	uInt8 p = readDigitalU8(0);

	if (getBitValue(p, 1))
		return true;
	return false;
}


