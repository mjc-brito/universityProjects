#include "my_interaction_functions.h"
#include <FreeRTOS.h>
#include <task.h>
#include <timers.h>
#include <semphr.h>
#include <interface.h>	
#include <interrupts.h>

int getBitValue(uInt8 value, uInt8 bit_n)
// given a byte value, returns the value of its bit n
{
    return(value & (1 << bit_n));
}
void setBitValue(uInt8* variable, int n_bit, int new_value_bit)
// given a byte value, set the n bit to value
{
    uInt8 mask_on = (uInt8)(1 << n_bit);
    uInt8 mask_off = ~mask_on;
    if (new_value_bit) *variable |= mask_on;
    else *variable &= mask_off;
}
void moveXLeft() 
{
    uInt8 p;
    taskENTER_CRITICAL();
    p = readDigitalU8(2); // read port 2
    setBitValue(&p, 6, 1); // set bit 6 to high level
    setBitValue(&p, 7, 0); // set bit 7 to low level
    writeDigitalU8(2, p); // update port 2
    taskEXIT_CRITICAL();
}
void moveXRight()
{
    uInt8 p;
    taskENTER_CRITICAL();
    p = readDigitalU8(2); // read port 2
    setBitValue(&p, 7, 1); //set bit 7 to high level
    setBitValue(&p, 6, 0); //set bit 6 to low level
    writeDigitalU8(2, p); //update port 2
    taskEXIT_CRITICAL();
}
void stopX()
{
    uInt8 p;
    taskENTER_CRITICAL();
    p = readDigitalU8(2);
    setBitValue(&p, 7, 0);
    setBitValue(&p, 6, 0);
    writeDigitalU8(2, p);
    taskEXIT_CRITICAL();
}
int  getXPos()
{
    uInt8 p = readDigitalU8(0);
    if (!getBitValue(p, 2))
        return 1;
    if (!getBitValue(p, 1))
        return 2;
    if (!getBitValue(p, 0))
        return 3;
    return -1;
}
void gotoX(int x)
{
    int aux = 1;
    int posX = getXPos();
    if (posX == -1) {
        moveXRight();
        while (getXPos() == -1){}
        stopX();
    }
    if (x > posX){
        moveXRight();
        while (aux) {
            if (getXPos() == x) {
                stopX();
                aux = 0;
            }
        }
    }
    if (x < posX) {
        moveXLeft();
        while (aux) {
            if (getXPos() == x) {
                stopX();
                aux = 0;
            }
        }
    }
}

void moveYInside() {
    uInt8 p = readDigitalU8(2); // read port 2
    taskENTER_CRITICAL();
    setBitValue(&p, 5, 1); // set bit 5 to high level
    setBitValue(&p, 4, 0); // set bit 4 to low level
    writeDigitalU8(2, p); // update port 2
    taskEXIT_CRITICAL();
}
void moveYOutside() {
    uInt8 p = readDigitalU8(2); // read port 2
    taskENTER_CRITICAL();
    setBitValue(&p, 4, 1); // set bit 4 to high level
    setBitValue(&p, 5, 0); // set bit 5 to low level
    writeDigitalU8(2, p); // update port 2
    taskEXIT_CRITICAL();
}
void stopY() {
    uInt8 p = readDigitalU8(2); // read port 2
    taskENTER_CRITICAL();
    setBitValue(&p, 4, 0); // set bit 4 to low level
    setBitValue(&p, 5, 0); // set bit 5 to low level
    writeDigitalU8(2, p); // update port 2
    taskEXIT_CRITICAL();
}
int  getYPos() {
    uInt8 p = readDigitalU8(0);
    if (!getBitValue(p, 5))
        return 1;
    if (!getBitValue(p, 4))
        return 2;
    if (!getBitValue(p, 3))
        return 3;
    return -1;
}
void gotoY(int y) {
    int auxY = 1;
    int posY = getYPos();
    if (y > posY) {
        moveYInside();
        while (auxY) {
            if (getYPos() == y) {
                stopY();
                auxY = 0;
            }
        }
    }
    if (y < posY) {
        moveYOutside();
        while (auxY) {
            if (getYPos() == y) {
                stopY();
                auxY = 0;
            }
        }
    }
}


void moveZUp() {
    uInt8 p;
    taskENTER_CRITICAL();
    p = readDigitalU8(2); // read port 2
    setBitValue(&p, 3, 1); // set bit 3 to high level
    setBitValue(&p, 2, 0); // set bit 2 to low level
    writeDigitalU8(2, p); // update port 2
    taskEXIT_CRITICAL();
}
void moveZDown() {
    uInt8 p;
    taskENTER_CRITICAL();
    p = readDigitalU8(2); // read port 2
    setBitValue(&p, 2, 1); // set bit 2 to high level
    setBitValue(&p, 3, 0); // set bit 3 to low level
    writeDigitalU8(2, p); // update port 2
    taskEXIT_CRITICAL();
}
void stopZ() {
    uInt8 p;
    taskENTER_CRITICAL();
    p = readDigitalU8(2); // read port 2
    setBitValue(&p, 3, 0); // set bit 3 to low level
    setBitValue(&p, 2, 0); // set bit 2 to low level
    writeDigitalU8(2, p); // update port 2
    taskEXIT_CRITICAL();
}
int  getZPos() {
    uInt8 p1 = readDigitalU8(1);
    uInt8 p2 = readDigitalU8(0);
    if (!getBitValue(p1, 3))
        return 1;
    if (!getBitValue(p1, 1))
        return 2;
    if (!getBitValue(p2, 7))
        return 3;
    return -1;
}
int getZPosUp() {
    uInt8 p1 = readDigitalU8(1);
    uInt8 p2 = readDigitalU8(0);
    if (!getBitValue(p1, 2))
        return 1;
    if (!getBitValue(p1, 0))
        return 2;
    if (!getBitValue(p2, 6))
        return 3;
    return -1;
}
void gotoZ(int z) {
    //int auxZ = 1;
    int posZ = getZPos();
    if (z > posZ) {
        moveZUp();
        while (getZPos() != z) {
        }
        stopZ();
    }
    if (z < posZ) {
        moveZDown();
        while (getZPos() != z) {
        }
        stopZ();
    }
}
void PutPartInCell() {
    int aux_ppic = 1;
    int z_pos = getZPos();
    moveZUp();
    while (aux_ppic) {
        if (getZPosUp() == z_pos) {
            stopZ();
            aux_ppic = 0;
        }
    }
    aux_ppic = 1;
    moveYInside();
    while (aux_ppic) {
        if (getYPos() == 3) {
            stopY();
            aux_ppic = 0;
        }
    }
    aux_ppic = 1;
    moveZDown();
    while (aux_ppic) {
        if (getZPos() == z_pos) {
            stopZ();
            aux_ppic = 0;
        }
    }
    aux_ppic = 1;
    moveYOutside();
    while (aux_ppic) {
        if (getYPos() == 2) {
            stopY();
            aux_ppic = 0;
        }
    }
}
void TakePartFromCell(){
    int aux_tpfc = 1;
    int z_pos = getZPos();
    moveYInside();
    while (aux_tpfc) {
        if (getYPos() == 3) {
            stopY();
            aux_tpfc = 0;
        }
    }
    aux_tpfc = 1;
    moveZUp();
    while (aux_tpfc) {
        if (getZPosUp() == z_pos) {
            stopZ();
            aux_tpfc = 0;
        }
    }
    aux_tpfc = 1;
    moveYOutside();
    while (aux_tpfc) {
        if (getYPos() == 2) {
            stopY();
            aux_tpfc = 0;
        }
    }
    aux_tpfc = 1;
    moveZDown();
    while (aux_tpfc) {
        if (getZPos() == z_pos) {
            stopZ();
            aux_tpfc = 0;
        }
    }
}

// put here all function's implementations