#pragma once

#include<interface.h>

// Portos
void initializeHardwarePorts();

// Bits
void setBitValue(uInt8* variable, int n_bit, int new_value_bit);
int getBitValue(uInt8 value, uInt8 n_bit);

// Cylinder Start
int cylinderStart_getPosition();
void cylinderStart_moveForward();
void cylinderStart_moveBackward();
void cylinderStart_stop();

// Cylinder 1
int cylinder1_getPosition();
void cylinder1_moveForward();
void cylinder1_moveBackward();
void cylinder1_stop();

// Cylinder 2
int cylinder2_getPosition();
void cylinder2_moveForward();
void cylinder2_moveBackward();
void cylinder2_stop();

// Conveyor
void conveyorMove();
void conveyorStop();

// Docks Sensors
bool switchDock1Pressed();
bool switchDock2Pressed();
bool switchDockEndPressed();

// Identification Sensors
int getIdentificationSensors();

// Cylinder Sensors
bool isBrickAtCylinder1();
bool isBrickAtCylinder2();

// LED
void turnLEDon();
void turnLEDoff();